#include <string.h>
#include <stdlib.h>
#include "component-generator.h"
#define HTML_INITIAL_SIZE 100
#define CSS_ID_ADITION 20

char *generateStyleCode(tStyle *style, char *id)
{
    if (style == NULL)
    {
        return NULL;
    }
    // char *styleCode = malloc(sizeof(char) * strlen(style->content) + strlen(id) + CSS_ID_ADITION);
    //  snprintf(styleCode, strlen(id) + CSS_ID_ADITION, "#%s {", id);
    //  strcat(styleCode, style->content);
    //  strcat(styleCode, "}");
    char *styleCode = malloc(sizeof(char) * strlen(style->content));
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

void checkHTMLSize(HTMLCode *code)
{
    if (code->used >= code->size)
    {
        code->size = 2 * code->used;
        code->html = realloc(code->html, sizeof(char) * code->size);
    }
}

char *getPositionToken(tPosToken *token)
{
    switch (token->token)
    {
    case 274:
        return "style=\"position:absolute;right:0px;\"";
    case 275:
        return "style=\"position:absolute;left:0px;\"";
    case 276:
        return "style=\"position:absolute;bottom:0px;\"";
    case 277:
        return "style=\"position:absolute;top:0px;\"";
    case 278:
        return "style=\"position:absolute;top: 50%; right: 50%; transform : translate(50%, -50%);\""; // center
    case 279:
        return "style=\"position:absolute;top:0px;right:0px;\"";
    case 280:
        return "style=\"position:absolute;top:0px;left:0px;\"";
    case 281:
        return "style=\"position:absolute;bottom:0px;right:0px;\"";
    case 282:
        return "style=\"position:absolute;bottom:0px;left:0px;\"";
    case 283:
        return "style=\"position:absolute;top:0px;left:50%;transform:translate(-50%,0);\"";
    case 284:
        return "style=\"position:absolute;bottom:0px;left:50%;transform:translate(-50%,0);\"";
    case 285:
        return "style=\"position:absolute;top:50%; left:0px;transform:translate(0,-50%);\"";
    case 286:
        return "style=\"position:absolute;top:50%; right:0px;transform:translate(0,-50%);\"";
    case 287:
        return "";
    default:
        return "";
        break;
    }
}

tComponent *findComponentByName(tComponentHeader *components, char *name)
{
    if (components == NULL)
    {
        return NULL;
    }
    tComponent *component = components->first;
    while (component != NULL)
    {
        if (strcmp(component->name, name) == 0)
            return component;
        component = component->next;
    }
    return NULL;
}

void copyAndCheck(HTMLCode *myHTML, char *newHTML)
{
    if (newHTML == NULL)
    {
        return;
    }
    myHTML->used += strlen(newHTML);
    checkHTMLSize(myHTML);
    strcat(myHTML->html, newHTML);
}

HTMLCode *generateHTMLCode(tComponent *component, tModule *root)
{
    if (component == NULL | root == NULL)
    {
        return NULL;
    }
    // preparo el return
    HTMLCode *htmlCode = malloc(sizeof(HTMLCode));
    htmlCode->size = HTML_INITIAL_SIZE;
    htmlCode->used = 0;
    htmlCode->html = calloc(htmlCode->size, sizeof(char)); // Inicio con 0 para no poner basura.

    // Obtengo posiciones para ver lo que tiene dentro.
    // Puede ser Constante, Variable o Elementos. Pero solo uno de estos 3.
    tPositionItem *aux = component->definition->template->positions == NULL ? NULL : component->definition->template->positions->first;
    int identifier = 0; // Usado para identificar los diferentes IDs de los divs en el HTML.
    while (aux != NULL)
    {

        // EL snprintf le pega a auzToken el string que le pasa por parametro con el formato dado.
        char *auxToken = malloc(sizeof(char) * 1000); // TODO :Deberia depender de si tengo o no un tamanio maximo de nombre de componente.
        printf("hmlt: %s\n", htmlCode->html);
        // TODO: Podria estar bueno hacer un hasheo para el class o simplemente sacarlo y usar solo ID
        snprintf(auxToken, 200, "<div id=\"%s-%d\" class=\"%s\" %s>\n", component->name, identifier, component->name, getPositionToken(aux->posToken));
        identifier++;
        copyAndCheck(htmlCode, auxToken); // Se que auxToken no es NULL;
        printf("hmlt 2 : %s\n", htmlCode->html);

        //  printf("%s\n", auxToken);

        if (aux->constant != NULL)
        {
            printf("constant %s\n", aux->constant->value);
            copyAndCheck(htmlCode, aux->constant->value);
        }

        else if (aux->variable != NULL)
        {
            // TODO: Tengo que ver de intercambiar el valor del js por esta variable.
            // checkHTMLSize(htmlCode);
        }

        else
        { // hay elementos

            tElement *auxElement = aux->elements != NULL ? aux->elements->first : NULL;
            while (auxElement != NULL)
            {
                // Debo buscar en los demas elementos si hay alguno que tenga el mismo nombre
                // HTMLCode * childHTML = generateHTMLCode(auxElement);
                // TODO : Sacar esto, cuando este arreglado el problema de que toma un caracter de mas cuando
                // todo: genero el nombre del elemento en la pItem

                // auxElement->name[strlen(auxElement->name) - 1] = '\0';

                printf("name: %s\n", auxElement->name);
                printf("Founded name: %s\n", findComponentByName(root->components, auxElement->name) == NULL ? "NULL" : findComponentByName(root->components, auxElement->name)->name);

                HTMLCode *childHTML = generateHTMLCode(findComponentByName(root->components, auxElement->name), root);
                if (childHTML != NULL)
                {
                    copyAndCheck(htmlCode, childHTML->html);
                    free(childHTML->html);
                    free(childHTML);
                }
                auxElement = auxElement->next;
            }
        }
        copyAndCheck(htmlCode, "</div>\n");
        printf("hmlt fin: %s\n", htmlCode->html);

        aux = aux->next;
        free(auxToken);
    }

    return htmlCode;
}

tComponentCode *generateComponentCode(tComponent *component)
{
    if (component == NULL)
    {
        return NULL;
    }
    tComponentCode *componentCode = malloc(sizeof(tComponentCode));
    componentCode->script = NULL;
    componentCode->style = NULL;
    componentCode->html = NULL;

    if (component->definition->script != NULL)
        componentCode->script = generateScriptCode(component->definition->script);
    if (component->definition->style != NULL)
        componentCode->style = generateStyleCode(component->definition->style, component->name);
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
        components[i] = generateComponentCode(aux);
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

void printCanvasHTML(tComponentCode *code)
{
    if (code == NULL)
        return;
    printf("%s\n", code->html);
}
tComponentCode *generateCanvas(tComponentAsCanvas *canvas, tModule *root)
{
    if (canvas == NULL)
    {
        return NULL;
    }
    // preparo el return
    tComponentCode *componentCode = malloc(sizeof(tComponentCode));
    componentCode->script = NULL;
    componentCode->style = NULL;
    componentCode->html = NULL;

    // Genero el css y el js

    if (canvas->definition->script != NULL)
        componentCode->script = generateScriptCode(canvas->definition->script);
    if (canvas->definition->style != NULL)
        componentCode->style = generateStyleCode(canvas->definition->style, "canvas");

    // Para armar el HTML necesito pasarlo como componente por que la funcion es recursiva.
    // Como todo se arma a partir del canvas, este recorre todos los elementos que tiene dentro
    // buscando los componentes que tienen definiciones y poniendo su HTML dentro del canvas.
    // ya que si tengo un elemento en topRight tengo que ponerlo en esa posicion.
    tComponent *auxComponent = malloc(sizeof(tComponent));

    auxComponent->definition = canvas->definition;
    auxComponent->name = "Canvas";
    auxComponent->next = NULL;

    if (canvas->definition->template != NULL)
        componentCode->html = generateHTMLCode(auxComponent, root)->html;

    return componentCode;
}