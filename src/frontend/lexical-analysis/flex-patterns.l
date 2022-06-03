%{

#include "flex-actions.h"


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

/*cssCode         (.|\n)+?(?=\}js)*/
/*jsCode          (.|\n)+?(?=\}js)*/

word            [a-zA-Z][a-zA-Z0-9_]*
text            \"(.*?)\"


/* Contextos */

%%


<INITIAL>{
"("											{ return OpenParenthesisPatternAction(); }
")"											{ return CloseParenthesisPatternAction(); }

":"                                            { return ColonPatternAction(); }
"~"                                            { return CommentPatternAction(); }
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

"css{"                                          { printf("BEGIN CSS\n");

                                                    char *css = malloc(sizeof(char) * INITIAL_BUFFER_SIZE);
                                                    char c = input();
                                                    int use = 0;
                                                    int size = INITIAL_BUFFER_SIZE;
                                                    char auxC;
                                                    while (true)
                                                    {
                                                        if (c == '}')
                                                        {   
                                                            auxC = c;
                                                            if ((c = input()) == 'c')
                                                            {
                                                                auxC = c;

                                                                if ((c = input()) == 's')
                                                                {
                                                                    auxC = c;

                                                                    if ((c = input()) == 's')
                                                                    {
                                                                        printf("END CSS\n");
                                                                        return CssCodePatternAction(css);
                                                                    }
                                                                    unput(c);
                                                                }
                                                                unput(c);
                                                            } 
                                                            unput(c);
                                                            // Guarde el valor de c ya que al hacer unput no lo puedo volver a restaurar
                                                            c = auxC;
                                                        }
                                                        if (c == EOF)
                                                        {
                                                            strcpy(css, "error");
                                                            return CssCodePatternAction(css);
                                                        }
                                                        if (use == size)
                                                        {
                                                            css = realloc(css, sizeof(char) + strlen(css) + INITIAL_BUFFER_SIZE);
                                                            size += INITIAL_BUFFER_SIZE;
                                                        }
                                                        css[use++] = c;
                                                        c = input();
                                                    }
    }

"js{"                                           { 
                                                        printf("BEGIN JS\n");
                                                        char *js = malloc(sizeof(char) * INITIAL_BUFFER_SIZE);
                                                        char c = input();
                                                        char auxC = 0;
                                                        int use = 0;
                                                        int size = INITIAL_BUFFER_SIZE;
                                                        while(true)
                                                        {
                                                            if(c == '}'){
                                                                auxC = c;
                                                                if((c = input()) == 'j'){
                                                                    auxC = c;
                                                                    if((c = input()) == 's'){
                                                                        printf("END JS\n");
                                                                        printf("js-end: %s\n", js);
                                                                        return JsCodePatternAction(js);
                                                                    }
                                                                    unput(c);
                                                                }
                                                                unput(c);
                                                                // Guarde el valor de c ya que al hacer unput no lo puedo volver a restaurar
                                                                c = auxC;
                                                            }
                                                            if(c == EOF){
                                                                    strcpy(js, "error");
                                                                    return JsCodePatternAction("error");
                                                            }
                                                            if (use == size)
                                                            {
                                                                js = realloc(js, sizeof(char) + strlen(js) + INITIAL_BUFFER_SIZE);
                                                                size += INITIAL_BUFFER_SIZE;
                                                            }
                                                            js[use++] = c;
                                                            c = input();
                                                        }
                                            }


{boolean}                                      { return BooleanPatternAction(yytext); }

{text}                                          { return TextPatternAction(yytext); }
{word}                                          { return StringPatternAction(yytext); }
{float}                                        { return FloatPatternAction(yytext); }

{digit}+									{ return IntegerPatternAction(yytext); }

{whitespace}								{ IgnoredPatternAction(yytext); }

.											{ return UnknownPatternAction(yytext); }
}

%%