%{

#include "flex-actions.h"


char *css = NULL;
char * js = NULL;
int useCss = 0, useJs = 0;
int sizeCss = INITIAL_BUFFER_SIZE, sizeJs = INITIAL_BUFFER_SIZE;

%}



/* Obliga a crear una regla explícita para manejar lexemas desconocidos. */
%option nodefault

/* Escanea un único archivo y se detiene. */
%option noyywrap

/* Dispone una variable global "yylineno" con el número de línea actual. */
%option yylineno

/* Patrones reutilizables. */
digit			[0-9]
float           [0-9]+\.[0-9]*
boolean          (true|false)
whitespace		[ \f\n\r\t\v]


word            [a-zA-Z_][a-zA-Z0-9_]*
text            \"(.*?)\"


/* Contextos */

%x CSS JS COMMENT


%%


<INITIAL>{
"("											{ return OpenParenthesisPatternAction(); }
")"											{ return CloseParenthesisPatternAction(); }

":"                                            { return ColonPatternAction(); }
"~"                                            { 
                                                printf("BEGIN COMMENT\n");
                                                BEGIN(COMMENT);
                                               }    
","                                            { return CommaPatternAction(); }
"$"                                            { return DollarPatternAction(); }
"."                                            { return DotPatternAction(); }

"top"											{ return TopPositionPatternAction(); }
"bottom"										{ return BottomPositionPatternAction(); }
"left"											{ return LeftPositionPatternAction(); }
"right"											{ return RightPositionPatternAction(); }
"center"										{ return CenterPositionPatternAction(); }

"topRight"										{ return TopRightPositionPatternAction(); }
"bottomLeft"									{ return BottomLeftPositionPatternAction(); }
"bottomRight"									{ return BottomRightPositionPatternAction(); }
"topLeft"										{ return TopLeftPositionPatternAction(); }

"topCenter"										{ return TopCenterPositionPatternAction(); }
"bottomCenter"									{ return BottomCenterPositionPatternAction(); }
"leftCenter"									{ return LeftCenterPositionPatternAction(); }
"rightCenter"									{ return RightCenterPositionPatternAction(); }

"children"											{ return ChildrenPositionPatternAction(); }

"{"											{ return OpenCurlyPatternAction(); }
"}"											{ return CloseCurlyPatternAction(); }

"["											{ return OpenSquarePatternAction(); }
"]"											{ return CloseSquarePatternAction(); }

"import"                                            { return ImportPatternAction(); }
"props"                                            { return PropsPatternAction(); }

"module"                                        { return ModulePatternAction(); }
"Canvas"                                        { return CanvasPatternAction(); }
"as"                                            { return AsPatternAction(); }
"Template"                                      { return TemplatePatternAction(); }
"Script"                                        { return ScriptPatternAction(); }
"Style"                                         { return StylePatternAction(); }

"css{"                                          {   
                                                    printf("BEGIN CSS\n");
                                                    css = malloc(sizeof(char) * INITIAL_BUFFER_SIZE);
                                                    useCss = 0; 
                                                    sizeCss = INITIAL_BUFFER_SIZE;
                                                    BEGIN(CSS);
                                                }

"js{"                                           { 
                                                    printf("BEGIN JS\n");
                                                    js = malloc(sizeof(char) * INITIAL_BUFFER_SIZE);
                                                    useJs = 0;
                                                    sizeJs = INITIAL_BUFFER_SIZE;
                                                    BEGIN(JS);
                                                }


{boolean}                                      { return BooleanPatternAction(yytext); }

{text}                                          { return TextPatternAction(yytext); }
{word}                                          { return StringPatternAction(yytext); }
{float}                                        { return FloatPatternAction(yytext); }

{digit}+									{ return IntegerPatternAction(yytext); }

{whitespace}								{ IgnoredPatternAction(yytext); }

.											{ return UnknownPatternAction(yytext); }
}

<COMMENT>"~"                                        {
                                                        BEGIN(INITIAL);
                                                        printf("END COMMENT\n");
                                                         
                                                    }
<COMMENT>[\n]                                       {}
<COMMENT>.                                          {}


<CSS>"}css"                                         { 
                                                        BEGIN(INITIAL);
                                                        printf("END CSS\n");
                                                        return CssCodePatternAction(css); 
                                                    }

<CSS>[\n]                                           { 
                                                        /* 
                                                            No encontre forma de juntar estas dos reglas. 
                                                            Parece que si o si se necesita que este la regla default del "." para que no se caiga el parser
                                                        */
                                                        if (useCss == sizeCss)
                                                        {
                                                            int auxSize = 50;
                                                                if(css != NULL){
                                                                    auxSize = sizeCss;
                                                                }
                                                                auxSize += sizeof(char) + INITIAL_BUFFER_SIZE;
                                                             css = realloc(css, auxSize);
                                                             sizeCss += INITIAL_BUFFER_SIZE;
                                                        }
                                                        css[useCss++] = yytext[0];
                                                    }
<CSS>.                                              { 
                                                        if (useCss == sizeCss)
                                                        {
                                                                int auxSize = 50;
                                                                if(css != NULL){
                                                                    auxSize = sizeCss;
                                                                }
                                                                auxSize += sizeof(char) + INITIAL_BUFFER_SIZE;
                                                                css = realloc(css, auxSize);
                                                                sizeCss += INITIAL_BUFFER_SIZE;
                                                        }
                                                        css[useCss++] = yytext[0];
                                                    }
<JS>"}js"                                           { 
                                                        BEGIN(INITIAL);
                                                        printf("END JS\n");
                                                        return JsCodePatternAction(js); 
                                                    }

<JS>[\n]                                            { 
                                                        /* 
                                                            No encontre forma de juntar estas dos reglas. 
                                                            Parece que si o si se necesita que este la regla default del "." para que no se caiga el parser
                                                        */
                                                        if (useJs == sizeJs)
                                                        {
                                                                int auxSize = 50;
                                                                if(js != NULL){
                                                                    auxSize = strlen(js);
                                                                }
                                                                js = realloc(js, sizeof(char) + auxSize + INITIAL_BUFFER_SIZE);
                                                                sizeJs += INITIAL_BUFFER_SIZE;
                                                        }
                                                        js[useJs++] = yytext[0];
                                                    }
<JS>.                                               { 
                                                        if (useJs == sizeJs)
                                                        {
                                                                int auxSize = 50;
                                                                if(js != NULL){
                                                                    auxSize = strlen(js);
                                                                }
                                                                js = realloc(js, sizeof(char) + auxSize + INITIAL_BUFFER_SIZE);
                                                                sizeJs += INITIAL_BUFFER_SIZE;
                                                        }
                                                        js[useJs++] = yytext[0];
                                                    }                                                  


%%