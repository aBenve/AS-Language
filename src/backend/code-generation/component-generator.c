#include <string.h>
#include <stdlib.h>
#include "component-generator.h"
#define HTML_INITIAL_SIZE 100

char *generateStyleCode(tStyle *style)
{
    if (style == NULL)
    {
        return NULL;
    }
    char *styleCode = malloc(sizeof(char) * strlen(style->content) + 1);
    strcpy(styleCode, style->content);
    return styleCode;
}
char *generateScriptCode(tScript *script)
{
    if (script == NULL)
    {
        return NULL;
    }
    char *scriptCode = malloc(sizeof(char) * strlen(script->content) + 1);
    strcpy(scriptCode, script->content);
    return scriptCode;
}
char *generateHTMLCode(tTemplate *template)
{
    if (template == NULL)
    {
        return NULL;
    }
    char *htmlCode = malloc(sizeof(char) * HTML_INITIAL_SIZE);

    return htmlCode;
}

tComponentCode *generateComponentCode(tDefinition *definition)
{
    if (definition == NULL)
    {
        return NULL;
    }
    tComponentCode *componentCode = malloc(sizeof(tComponentCode));
    componentCode->script = NULL;
    componentCode->style = NULL;
    componentCode->html = NULL;

    if (definition->script != NULL)
        componentCode->script = generateScriptCode(definition->script);
    if (definition->style != NULL)
        componentCode->style = generateStyleCode(definition->style);
    if (definition->template != NULL)
        componentCode->html = generateHTMLCode(definition->template);
    return componentCode;
}

// Retorna 1 si tengo style y 0 sino
int hasStyle(tComponentCode *code)
{
    if (code == NULL)
    {
        return 0;
    }
    return code->style != NULL ? 1 : 0;
}
// Retorna 1 si tengo script y 0 sino
int hasScript(tComponentCode *code)
{
    if (code == NULL)
    {
        return 0;
    }
    return code->script != NULL ? 1 : 0;
}

tComponentCode **generateComponents(tComponent *component, int componentAmount)
{
    if (component == NULL)
    {
        return NULL;
    }

    tComponent *aux = component;
    tComponentCode **components = malloc(sizeof(tComponentCode *) * componentAmount);
    int i = 0;
    while (aux != NULL)
    {
        components[i] = generateComponentCode(aux->definition);
        aux = aux->next;
        i++;
    }
    return components;
}

void printCss(tComponentCode **code, int count)
{
    if (code == NULL)
        return;

    for (int i = 0; i < count; ++i)
    {
        if (hasStyle(code[i]))
            printf("%s\n", code[i]->style);
    }
}

void printJs(tComponentCode **code, int count)
{
    if (code == NULL)
        return;
    for (int i = 0; i < count; ++i)
    {
        if (hasScript(code[i]))
            printf("%s\n", code[i]->script);
    }
}

void printCanvasCss(tComponentCode *code)
{
    if (code == NULL)
        return;
    if (hasStyle(code) == 1)
        printf("%s\n", code->style);
}

void printCanvasJs(tComponentCode *code)
{
    if (code == NULL)
        return;
    if (hasScript(code) == 1)
        printf("%s\n", code->script);
}

tComponentCode *generateCanvas(tComponentAsCanvas *canvas)
{
    tComponentCode *canvasCode = generateComponentCode(canvas->definition);

    return canvasCode;
}