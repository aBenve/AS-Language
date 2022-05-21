#ifndef COMPONENT_GENERATOR_HEADER
#define COMPONENT_GENERATOR_HEADER
#include "../support/shared.h"

typedef struct tComponentCode
{
    char *script;
    char *style;
    char *html;
} tComponentCode;

tComponentCode *generateCanvas(tComponentAsCanvas *canvas);
void printCanvasJs(tComponentCode *code);
void printCanvasCss(tComponentCode *code);
void printJs(tComponentCode **code, int count);
void printCss(tComponentCode **code, int count);
tComponentCode **generateComponents(tComponent *component, int componentAmount);
int hasScript(tComponentCode *code);
int hasStyle(tComponentCode *code);
tComponentCode *generateComponentCode(tDefinition *definition);
char *generateScriptCode(tScript *script);
char *generateStyleCode(tStyle *style);
char *generateHTMLCode(tTemplate *template);

#endif
