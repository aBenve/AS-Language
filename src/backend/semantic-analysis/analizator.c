#include "analizator.h"

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

tJsVariable **createVarList(tScript *script)
{
    tJsVariable **list = NULL;
    printf("Creando lista de variables\n");
    char *aux = calloc(strlen(script->content) + 1, sizeof(char));
    strcpy(aux, script->content);
    int i = 0;
    int varAmount = 0;
    while (aux[i] != '\0')
    {
        // printf("aca: %c\n", aux[i]);
        if (aux[i] == '_')
        {
            if (aux[i + 1] != '\0' && aux[i + 1] != '_')
            {
                varAmount++;
                // recorro hasta el final del string y lo hguardo como nombre de variable
                int j = i + 1;
                while (aux[j] != '\0' && aux[j] != '=' && aux[j] != ';')
                {
                    // TODO me sirve esto?
                    j++;
                }
            }
        }

        i++;
    }
    free(aux);
    return list;
}

// Check if the script code has all the variables used in the template code and check if the variables used in template are defined in other components or in the script code
void thirdGenRepare(tModule *root)
{
    // 1) Save all the variables define in script code
    tJsVariable **varList = NULL;
    if (hasScriptDef(root->canvas->definition) == 1)
        varList = createVarList(root->canvas->definition->script);
    return;
}

void Analice(tModule *root)
{
    // Saco los js{ js } y los css{ css } -> * YA NO ES NECESARIO
    // firstGenRepare(root);

    // Analizo si los nombres se guardaron bien y los tamanios
    // secondGenRepare(root);

    // Aseguro que todas las variables usadas esten definidas
    // thirdGenRepare(root);
}