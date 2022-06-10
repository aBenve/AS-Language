#include "analizator.h"
#include <string.h>

int hasScriptDef(tDefinition *def)
{
    return def->script != NULL;
}
int hasStyleDef(tDefinition *def)
{
    return def->style != NULL;
}

typedef struct tJsVariable
{
    char *name;
} tJsVariable;

typedef tJsVariable **varTable;

#define INITIAL_CONCATENATED_STRING_SIZE 50

int findByName(char **table, char *name, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (strcmp(table[i], name) == 0)
        {
            return i;
        }
    }
    return -1;
}

char *getUpdateFunction(char *varName, char *value)
{
    char *function = malloc(strlen(varName) + strlen(value) + 25);
    sprintf(function, "updateView('%s', %s)\n", varName, value);
    return function;
}

void addUpdateFuntcionToString(char *string, int start, int end, char *function)
{
    int length = end - start;
    char *newString = malloc(strlen(string) + strlen(function) + 1);
    strncpy(newString, string, start);
    strncpy(newString + start, function, strlen(function));
    strncpy(newString + start + strlen(function), string + end, strlen(string) - end);
    newString[strlen(string) + strlen(function)] = '\0';
    free(string);
    string = newString;
}

// node struct for storing string tokens of script->content
typedef struct tScriptNode
{
    char *string;
    int isVariable;
    int isValue;
    char *value; // si es un valor, quiero guardarme el dato limpio, sin \n o ; pero sigo queriendo mantener el string para cuando debo volver a juntar todos los strings
    char *variable;
    struct tScriptNode *next;
    struct tScriptNode *prev;
} tScriptNode;

// tScriptNode head
typedef struct tScriptNodeHead
{
    tScriptNode *head;
} tScriptNodeHead;

// void normalizeString(tScriptNode *node, char *token)
// {
//     if (strlen(token) > 1 && (token[strlen(token) - 1] == '\n' || token[strlen(token) - 1] == ';'))
//     {
//         if (token[strlen(token) - 2] == ';')
//         {
//             strncpy(node->string, token, strlen(token) - 2);
//             node->string[strlen(token) - 2] = '\0';
//         }
//     }
// }

tScriptNode *createTokensListRec(char *token, tScriptNode *prev)
{
    if (token == NULL)
    {
        return NULL;
    }
    tScriptNode *node = malloc(sizeof(tScriptNode));
    node->string = malloc(strlen(token) + 1);
    node->prev = prev;
    node->value = NULL;
    node->variable = NULL;
    // printf("token: %s\n", token);
    if (strlen(token) > 2 && token[0] == '_' && token[1] == '_') // es variable
    {
        node->isVariable = 1;
        node->isValue = 0;
        node->variable = malloc(strlen(token) + 1);
        if (strlen(token) > 1 && (token[strlen(token) - 1] == '\n' || token[strlen(token) - 1] == ';'))
        {
            if (token[strlen(token) - 2] == ';')
                strncpy(node->variable, token, strlen(token) - 2);
            else
                strncpy(node->variable, token, strlen(token) - 1);
            node->variable[strlen(token) - 1] = '\0';
        }
        else
            strcpy(node->variable, token);

        // printf("variable: %s\n", node->variable);
    }
    else if (prev != NULL && strcmp(prev->string, "=") == 0) // es valor
    {
        node->isVariable = 0;
        node->isValue = 1;
        // reviso si tiene un \n al final o un  ;
        node->value = malloc(strlen(token) + 1);
        if (strlen(token) > 1 && (token[strlen(token) - 1] == '\n' || token[strlen(token) - 1] == ';'))
        {

            if (token[strlen(token) - 2] == ';') // puedo tener algo como count = 0;\n
                strncpy(node->value, token, strlen(token) - 2);
            else
                strncpy(node->value, token, strlen(token) - 1);

            node->value[strlen(token) - 1] = '\0';
        }
        else
            strcpy(node->value, token);

        // printf("val: %s\n", node->value);
    }
    else // es string
    {
        node->isVariable = 0;
        node->isValue = 0;
    }
    // Siempre guardo el string
    strcpy(node->string, token);
    node->next = createTokensListRec(strtok(NULL, " "), node);
    return node;
}

tScriptNode *createTokensList(char *jsCode)
{
    char *token = strtok(jsCode, " ");
    tScriptNode *toReturn = NULL;
    if (token != NULL)
    {
        toReturn = malloc(sizeof(tScriptNode));
        toReturn->string = malloc(strlen(token) + 1);
        strcpy(toReturn->string, token);
        toReturn->value = NULL;
        toReturn->variable = NULL;
        toReturn->next = createTokensListRec(strtok(NULL, " "), toReturn);
        toReturn->prev = NULL;
    }
    return toReturn;
}

void freeTokensList(tScriptNode *node)
{
    if (node == NULL)
    {
        return;
    }
    freeTokensList(node->next);
    free(node->string);
    free(node->value);
    free(node->variable);
}
void freeTokenHead(tScriptNodeHead *head)
{
    if (head == NULL)
    {
        return;
    }
    freeTokensList(head->head);
    free(head);
}

tScriptNodeHead *updateScriptCode(tScript *script)
{
    char *aux = calloc(strlen(script->content) + 1, sizeof(char));
    strcpy(aux, script->content);

    tScriptNodeHead *tokensList = malloc(sizeof(tScriptNodeHead));
    tokensList->head = createTokensList(aux);
    // print all tokens

    char *concatenatedString = calloc(INITIAL_CONCATENATED_STRING_SIZE, sizeof(char));
    int concatenatedStringSize = INITIAL_CONCATENATED_STRING_SIZE;
    int concatenatedStringUsed = 0;
    if (tokensList->head != NULL)
    {

        tScriptNode *node = tokensList->head;
        while (node != NULL)
        {
            if (node->isVariable == 1)
            {
                tScriptNode *equalNode = node->next;
                if (equalNode != NULL && equalNode->next && equalNode->next->isValue == 1)
                {
                    // printf("%s = %s\n", node->variable, equalNode->next->value);
                    tScriptNode *updateViewNode = malloc(sizeof(tScriptNode));
                    updateViewNode->string = getUpdateFunction(node->variable, equalNode->next->value);
                    updateViewNode->isVariable = 0;
                    updateViewNode->isValue = 0;
                    updateViewNode->value = NULL;
                    updateViewNode->variable = NULL;
                    updateViewNode->next = equalNode->next->next;
                    updateViewNode->prev = equalNode->next;
                    equalNode->next->next = updateViewNode;
                }
            }

            // printf("node: %s\n", node->string);
            if (concatenatedStringUsed + strlen(node->string) >= concatenatedStringSize)
            {
                concatenatedStringSize *= 2;
                concatenatedString = realloc(concatenatedString, concatenatedStringSize);
            }
            concatenatedStringUsed += strlen(node->string);
            strcat(strcat(concatenatedString, " "), node->string);
            node = node->next;
        }
    }
    // printf("concatenatedString: %s\n", concatenatedString);

    script->content = calloc(strlen(concatenatedString) + 1, sizeof(char));
    strcpy(script->content, concatenatedString);
    free(concatenatedString);
    free(aux);
    return tokensList;
}

void addVarToTable(varTable *varTable, char *varName, char *value)
{
}

#define INITIAL_VAR_TABLE_SIZE 5

// create complete linked list of tScriptNode storing every token and if the token its a variable, it will be stored in varTable
char **createVarTable(tScript *script, tScriptNodeHead *tokensList)
{
    char **toReturn = malloc(sizeof(char *) * INITIAL_VAR_TABLE_SIZE);
    int toReturnSize = INITIAL_VAR_TABLE_SIZE;
    int toReturnUsed = 0;

    tScriptNode *node = tokensList->head;
    while (node != NULL)
    {
        if (node->isVariable == 1)
        {
            if (findByName(toReturn, node->variable, toReturnUsed) == -1)
            {
                toReturn[toReturnUsed] = calloc(strlen(node->variable) + 1, sizeof(char));
                strcpy(toReturn[toReturnUsed], node->variable);
                toReturnUsed++;
            }
        }
        node = node->next;
    }

    toReturn[toReturnUsed] = NULL;

    return toReturn;
}

/*
// look for string started with __ and store them in a table
varTable createVarList(tScript *script)
{
    tJsVariable **list = malloc(sizeof(tJsVariable *) * INITIAL_VAR_TABLE_SIZE);
    printf("Creando lista de variables\n");

    char *aux = calloc(strlen(script->content) + 1, sizeof(char));
    char *aux2 = calloc(strlen(script->content) + 1, sizeof(char));
    strcpy(aux, script->content);
    strcpy(aux2, script->content);

    int size = INITIAL_VAR_TABLE_SIZE;
    int varAmount = 0;
    int valueIndex = 0;
    int valuesAdded = 0;
    char *token = strtok(aux, " ");

    while (token != NULL)
    {
        printf("Token: %s\n", token);
        if (strlen(token) > 2 && token[0] == '_' && token[1] == '_')
        {

            if ((valueIndex = findByName(list, token, varAmount)) == -1)
            {
                // Guardo el nombre si no esta en la lista
                list[varAmount] = malloc(sizeof(tJsVariable));
                list[varAmount]->name = malloc(sizeof(char) * strlen(token) + 1);
                strcpy(list[varAmount]->name, token + 2);
                // list[varAmount]->value = NULL;
                printf("Variable: %s\n", list[varAmount]->name);
                valueIndex = varAmount++;
            }

            if (varAmount >= size)
            {
                list = realloc(list, sizeof(tJsVariable *) * size * 2);
                size *= 2;
            }
            // Guardo el valor si es que esta definido en esta posicion
            if (strcmp(token = strtok(NULL, " "), "=") == 0)
            {
                token = strtok(NULL, " "); // token apunta al valor
                char *toAdd = getUpdateFunction(list[valueIndex]->name, token);

                int pos = (token + strlen(token) - aux) + strlen(toAdd) * valuesAdded;
                printf("pos: %d\n", pos);
                // agrego el string a aux2 toAdd en la posicion pos
                // aux2 = realloc(aux2, sizeof(char) * (strlen(aux2) + strlen(toAdd) + 1));

                addUpdateFuntcionToString(aux2, pos, pos + strlen(toAdd), toAdd);
                // strcpy(aux2 + pos, toAdd);
                printf("aux: %s\n", aux2);

                valuesAdded++;
                free(toAdd);
                // Debo agregar al string updateView(list[varAmount]->name, token)

                // list[valueIndex]->value = calloc(strlen(token) + 1, sizeof(char));
                // strcpy(list[valueIndex]->value, token);
                // printf("Valor: %s\n", list[valueIndex]->value);
            }
        }
        token = strtok(NULL, " ");
    }

    free(aux);
    free(aux2);
    free(token);
    return list;
}
*/
// Check if the script code has all the variables used in the template code and check if the variables used in template are defined in other components or in the script code
void thirdGenRepare(tModule *root)
{
    // 1) Save all the variables define in script code
    char **varTable = NULL;
    tScriptNodeHead *tokenList = NULL;

    if (hasScriptDef(root->canvas->definition) == 1)
    {
        // update the script code
        tokenList = updateScriptCode(root->canvas->definition->script);
        varTable = createVarTable(root->canvas->definition->script, tokenList);
    }

    // Una vez formada la tabla de variables, busco en el componente donde estoy si se usan en el HTML y las reemplazo.

    return;
}

void Analice(tModule *root)
{
    // Saco los js{ js } y los css{ css } -> * YA NO ES NECESARIO
    // firstGenRepare(root);

    // Analizo si los nombres se guardaron bien y los tamanios
    // secondGenRepare(root);

    // Aseguro que todas las variables usadas esten definidas
    thirdGenRepare(root);
}