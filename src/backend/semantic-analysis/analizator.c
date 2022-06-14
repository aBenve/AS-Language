#include "analizator.h"

int hasScriptDef(tDefinition *def)
{
    return def->script != NULL;
}
int hasStyleDef(tDefinition *def)
{
    return def->style != NULL;
}

int findByName(varTable *table, char *name, int size)
{
    for (int i = 0; i < size; i++)
    {
        // printf("%s = %s\n", table->elements[i], name);
        if (strcmp(table->elements[i], name) == 0)
        {
            return i;
        }
    }
    return -1;
}

int findByVarInHTML(varTable *table, char *name, int size)
{
    for (int i = 0; i < size; i++)
    {
        // printf("%s = %s\n", table->elements[i], name);
        if (strcmp(table->elements[i] + 2, name) == 0)
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
    free(node);
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
                concatenatedStringSize += strlen(node->string) + INITIAL_CONCATENATED_STRING_SIZE;
                concatenatedString = realloc(concatenatedString, concatenatedStringSize * sizeof(char));
            }

            concatenatedStringUsed += strlen(node->string) + 1;
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

// create complete linked list of tScriptNode storing every token and if the token its a variable, it will be stored in varTable
varTable *createVarTable(tScript *script, tScriptNodeHead *tokensList)
{
    varTable *toReturn = malloc(sizeof(varTable));
    toReturn->elements = calloc(INITIAL_VAR_TABLE_SIZE, sizeof(char *));
    toReturn->size = INITIAL_VAR_TABLE_SIZE;
    toReturn->used = 0;
    int toReturnSize = INITIAL_VAR_TABLE_SIZE;
    int toReturnUsed = 0;

    tScriptNode *node = tokensList->head;
    while (node != NULL)
    {
        if (node->isVariable == 1)
        {
            if (findByName(toReturn, node->variable, toReturnUsed) == -1)
            {
                if (toReturnUsed + 1 >= toReturnSize)
                {
                    toReturnSize *= 2;
                    toReturn->elements = realloc(toReturn->elements, toReturnSize * sizeof(char *));
                }
                toReturn->elements[toReturnUsed] = calloc(strlen(node->variable) + 1, sizeof(char));
                strcpy(toReturn->elements[toReturnUsed], node->variable);
                toReturnUsed++;
            }
        }
        node = node->next;
    }

    // toReturn[toReturnUsed] = NULL;
    toReturn->elements[toReturnUsed] = NULL;
    toReturn->used = toReturnUsed;
    toReturn->size = toReturnSize;

    return toReturn;
}

int analiceTemplate(tTemplate *template, varTable *varTable)
{
    // recorro las posisicones del template buscnaod variables, si encuentro busco en la tabla
    // si esta, todo bien, sigo
    // si no esta, cambio el estado a error

    tPositionHeader *auxHeader = template->positions;

    if (auxHeader != NULL)
    {
        tPositionItem *auxPosition = auxHeader->first;
        while (auxPosition != NULL)
        {
            if (auxPosition->variable != NULL)
            {
                if (varTable == NULL)
                    return -1;
                // printf("VAR: %s\n", auxPosition->variable->name);
                if (findByVarInHTML(varTable, auxPosition->variable->name, varTable->used) == -1)
                    return -1;
            }
            auxPosition = auxPosition->next;
        }
    }
    return 0;
}

void freeVarTable(varTable *varTable)
{
    if (varTable == NULL)
    {
        return;
    }
    for (int i = 0; i < varTable->used; i++)
    {
        free(varTable->elements[i]);
    }
    free(varTable->elements);
    free(varTable);
}

// Check if the script code has all the variables used in the template code and check if the variables used in template are defined in other components or in the script code
void RepareCanvas(tModule *root)
{
    // 1) Save all the variables define in script code
    varTable *varTable = NULL;
    tScriptNodeHead *tokenList = NULL;

    if (hasScriptDef(root->canvas->definition) == 1)
    {
        // update the script code
        tokenList = updateScriptCode(root->canvas->definition->script);
        varTable = createVarTable(root->canvas->definition->script, tokenList);
    }
    // Una vez formada la tabla de variables, busco en el componente donde estoy si se usan en el HTML y las reemplazo.
    if (analiceTemplate(root->canvas->definition->template, varTable) == -1)
    {
        LogError("Variable usada en HTML no definida.");
        exit(1);
    }
    freeTokenHead(tokenList);
    freeVarTable(varTable);

    return;
}

void RepareComponents(tModule *root)
{
    // 1) Save all the variables define in script code
    varTable *varTable;
    tScriptNodeHead *tokenList;

    if (root->components == NULL)
        return;

    tComponent *aux = root->components->first;
    while (aux != NULL)
    {
        varTable = NULL;
        tokenList = NULL;

        if (hasScriptDef(aux->definition) == 1)
        {
            // update the script code
            tokenList = updateScriptCode(aux->definition->script);
            varTable = createVarTable(aux->definition->script, tokenList);
        }
        // Una vez formada la tabla de variables, busco en el componente donde estoy si se usan en el HTML y las reemplazo.
        if (analiceTemplate(aux->definition->template, varTable) == -1)
        {
            LogError("Variable usada en HTML no definida.");
            exit(1);
        }

        freeTokenHead(tokenList);
        freeVarTable(varTable);
        aux = aux->next;
    }

    return;
}

void Analice(tModule *root)
{
    // Aseguro que todas las variables usadas esten definidas
    LogInfo("\tAnalizando variables de canvas..");
    RepareCanvas(root);
    LogInfo("\tAnalizando variables de componentes...\n");
    RepareComponents(root);
}