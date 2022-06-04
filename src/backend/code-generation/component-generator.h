#ifndef COMPONENT_GENERATOR_HEADER
#define COMPONENT_GENERATOR_HEADER
#include "../support/shared.h"

typedef struct HTMLCode
{
    char *html;
    int size;
    int used;
} HTMLCode;
typedef struct tComponentCode
{
    char *script;
    char *style;
    char *html;
} tComponentCode;

tComponentCode *generateCanvas(tComponentAsCanvas *canvas, tModule *root);
void printCanvasJs(tComponentCode *code);
void printCanvasCss(tComponentCode *code);
void printCanvasHTML(tComponentCode *code);
void printJs(tComponentCode **code, int count);
void printCss(tComponentCode **code, int count);
tComponentCode **generateComponents(tComponent *component, int componentAmount);
int hasScript(tComponentCode *code);
int hasStyle(tComponentCode *code);
tComponentCode *generateComponentCode(tComponent *component);
char *generateScriptCode(tScript *script);
char *generateStyleCode(tStyle *style, char *id);
HTMLCode *generateHTMLCode(tComponent *component, tModule *root);

#endif
