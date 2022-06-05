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
    char *value;
} tJsVariable;

typedef tJsVariable **varTable;

#define INITIAL_VAR_TABLE_SIZE 10

int findByName(varTable table, char *name, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (strcmp(table[i]->name, name) == 0)
        {
            return i;
        }
    }
    return -1;
}

// look for string started with __ and store them in a table
varTable createVarList(tScript *script)
{
    tJsVariable **list = malloc(sizeof(tJsVariable *) * INITIAL_VAR_TABLE_SIZE);
    printf("Creando lista de variables\n");

    char *aux = calloc(strlen(script->content) + 1, sizeof(char));
    strcpy(aux, script->content);

    int size = INITIAL_VAR_TABLE_SIZE;
    int varAmount = 0;
    int valueIndex = 0;

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
                list[varAmount]->value = NULL;
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
                token = strtok(NULL, " ");
                list[valueIndex]->value = calloc(strlen(token) + 1, sizeof(char));
                strcpy(list[valueIndex]->value, token);
                printf("Valor: %s\n", list[valueIndex]->value);
            }
        }
        token = strtok(NULL, " ");
    }

    free(aux);
    free(token);
    return list;
}

// Check if the script code has all the variables used in the template code and check if the variables used in template are defined in other components or in the script code
void thirdGenRepare(tModule *root)
{
    // 1) Save all the variables define in script code
    varTable varList = NULL;
    if (hasScriptDef(root->canvas->definition) == 1)
        varList = createVarList(root->canvas->definition->script);

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