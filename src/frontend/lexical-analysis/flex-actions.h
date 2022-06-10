#ifndef FLEX_ACTIONS_HEADER
#define FLEX_ACTIONS_HEADER

#include "../../backend/support/shared.h"
#include "../../backend/support/logger.h"
#include "../syntactic-analysis/bison-parser.h"

#define INITIAL_BUFFER_SIZE 50

/*

    ? Otra forma de hacer reglas a mano por si alguna vez son necesarias.

    char *css = malloc(sizeof(char) * INITIAL_BUFFER_SIZE);
    int use = 0;
    int size = INITIAL_BUFFER_SIZE;
    char c = input();
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
*/

yytoken_kind_t OpenParenthesisPatternAction();
yytoken_kind_t CloseParenthesisPatternAction();
yytoken_kind_t ColonPatternAction();
yytoken_kind_t CommaPatternAction();
yytoken_kind_t DollarPatternAction();
yytoken_kind_t DotPatternAction();
yytoken_kind_t TopPositionPatternAction();
yytoken_kind_t BottomPositionPatternAction();
yytoken_kind_t LeftPositionPatternAction();
yytoken_kind_t RightPositionPatternAction();
yytoken_kind_t CenterPositionPatternAction();
yytoken_kind_t TopRightPositionPatternAction();
yytoken_kind_t TopLeftPositionPatternAction();
yytoken_kind_t BottomLeftPositionPatternAction();
yytoken_kind_t BottomRightPositionPatternAction();
yytoken_kind_t BottomCenterPositionPatternAction();
yytoken_kind_t TopCenterPositionPatternAction();
yytoken_kind_t LeftCenterPositionPatternAction();
yytoken_kind_t RightCenterPositionPatternAction();
yytoken_kind_t ChildrenPositionPatternAction();
yytoken_kind_t OpenCurlyPatternAction();
yytoken_kind_t CloseCurlyPatternAction();
yytoken_kind_t CloseSquarePatternAction();
yytoken_kind_t OpenSquarePatternAction();
yytoken_kind_t ImportPatternAction();
yytoken_kind_t PropsPatternAction();
yytoken_kind_t AsPatternAction();
yytoken_kind_t TemplatePatternAction();
yytoken_kind_t ScriptPatternAction();
yytoken_kind_t JsCodePatternAction(char *lexeme);
yytoken_kind_t StylePatternAction();
yytoken_kind_t CssCodePatternAction(char *lexeme);
yytoken_kind_t ModulePatternAction();
yytoken_kind_t CanvasPatternAction();
yytoken_kind_t StringPatternAction(char *lexeme);
yytoken_kind_t TextPatternAction(char *lexeme);
yytoken_kind_t FloatPatternAction(const char *lexeme);
yytoken_kind_t BooleanPatternAction(const char *lexeme);

yytoken_kind_t IntegerPatternAction(const char *lexeme);

void IgnoredPatternAction(const char *lexeme);

yytoken_kind_t UnknownPatternAction(const char *lexeme);

#endif
