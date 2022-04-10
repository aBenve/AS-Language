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
crlf			\r\n
digit			[0-9]
float           [0-9]*\.[0-9]*
boolean          (true|false)
endline			\n
whitespace		[ \f\n\r\t\v]
word            [a-zA-Z][a-zA-Z0-9_]*

%%

"("											{ return OPEN_PARENTHESIS; }
")"											{ return CLOSE_PARENTHESIS; }

":"                                            { return COLON; }
"~"                                            { return LINE_COMMENT; }
","                                            { return COMMA; }

"top"											{ return TOP; }
"bottom"										{ return BOTTOM; }
"left"											{ return LEFT; }
"right"											{ return RIGHT; }
"center"										{ return CENTER; }

"topRight"										{ return TOP_RIGHT; }
"bottomLeft"									{ return BOTTOM_LEFT; }
"bottomRight"									{ return BOTTOM_RIGHT; }
"topLeft"										{ return TOP_LEFT; }

"topCenter"										{ return TOP_CENTER; }
"bottomCenter"									{ return BOTTOM_CENTER; }
"leftCenter"									{ return LEFT_CENTER; }
"rightCenter"									{ return RIGHT_CENTER; }

"children"											{ return CHILDREN; }

"{"											{ return OPEN_CURLY_BRACKET; }
"}"											{ return CLOSE_CURLY_BRACKET; }

"["											{ return OPEN_SQUARE_BRACKET; }
"]"											{ return CLOSE_SQUARE_BRACKET; }

"import"                                            { return IMPORT; }

"module"                                        { return MODULE; }
"Canvas"                                        { return CANVAS; }
"as"                                            { return AS; }
"Template"                                      { return TEMPLATE; }
"Script"                                        { return SCRIPT; }
"Style"                                         { return STYLE; }

{word}                                          { return StringPatternAction(yytext); }
{float}                                        { return FloatPatternAction(yytext); }
{boolean}                                      { return BooleanPatternAction(yytext); }

{digit}+									{ return IntegerPatternAction(yytext); }

{whitespace}								{ IgnoredPatternAction(yytext); }

.											{ return UnknownPatternAction(yytext); }

%%
