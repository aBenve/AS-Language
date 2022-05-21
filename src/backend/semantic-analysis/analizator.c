#include "analizator.h"

#define JS_OPEN_AND_CLOSE 3
#define CSS_OPEN_AND_CLOSE 4

void repareJsCode(tScript *code)
{
    code->content += JS_OPEN_AND_CLOSE;
    code->content[strlen(code->content) - JS_OPEN_AND_CLOSE] = '\0';
}

void repareCssCode(tStyle *code)
{
    code->content += CSS_OPEN_AND_CLOSE;
    code->content[strlen(code->content) - CSS_OPEN_AND_CLOSE] = '\0';
}

int hasScriptDef(tDefinition *def)
{
    return def->script != NULL;
}
int hasStyleDef(tDefinition *def)
{
    return def->style != NULL;
}

// Repare unsolved issues like js{js} and css{css}
void firstGenRepare(tModule *root)
{
    // Reparo canvas
    printf("Reparando canvas\n");
    if (hasScriptDef(root->canvas->definition) == 1)
        repareJsCode(root->canvas->definition->script);
    if (hasStyleDef(root->canvas->definition) == 1)
        repareCssCode(root->canvas->definition->style);

    // Reparo componentes
    printf("Reparando componentes\n");
    tComponent *aux = root->components != NULL ? root->components->first : NULL;
    while (aux != NULL)
    {
        if (hasScriptDef(aux->definition) == 1)
            repareJsCode(aux->definition->script);
        if (hasStyleDef(aux->definition) == 1)
            repareCssCode(aux->definition->style);
        aux = aux->next;
    }
}

void Analice(tModule *root)
{
    firstGenRepare(root);
}