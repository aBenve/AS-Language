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
float           [0-9]+\.[0-9]*
boolean          (true|false)
endline			\n
whitespace		[ \f\n\r\t\v]

jsCode          js\{(.|\n)*js\}

cssCode         css\{(.|\n)*css\}

word            [a-zA-Z][a-zA-Z0-9_]*
text            \"(.*?)\"

%%

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

{cssCode}                                       { return CssCodePatternAction(yytext); }
{jsCode}                                        { return JsCodePatternAction(yytext); }

{boolean}                                      { return BooleanPatternAction(yytext); }

{text}                                          { return TextPatternAction(yytext); }
{word}                                          { return StringPatternAction(yytext); }
{float}                                        { return FloatPatternAction(yytext); }

{digit}+									{ return IntegerPatternAction(yytext); }

{whitespace}								{ IgnoredPatternAction(yytext); }

.											{ return UnknownPatternAction(yytext); }

%%
