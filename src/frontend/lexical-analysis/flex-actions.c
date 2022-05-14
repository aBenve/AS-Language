//#include "../../backend/support/logger.h"
#include "flex-actions.h"
#include <stdlib.h>
#include <string.h>

/**
 * Implementación de "flex-rules.h".
 */

yytoken_kind_t OpenParenthesisPatternAction()
{
	LogDebug("OpenParenthesisPatternAction");
	return OPEN_PARENTHESIS;
}
yytoken_kind_t CloseParenthesisPatternAction()
{
	LogDebug("CloseParenthesisPatternAction");
	return CLOSE_PARENTHESIS;
}
yytoken_kind_t ColonPatternAction()
{
	LogDebug("ColonPatternAction");
	return COLON;
}
yytoken_kind_t CommentPatternAction()
{
	LogDebug("CommentPatternAction");
	return LINE_COMMENT;
}
yytoken_kind_t CommaPatternAction()
{
	LogDebug("CommaPatternAction");
	return COMMA;
}
yytoken_kind_t DollarPatternAction()
{
	LogDebug("DollarPatternAction");
	return DOLLAR;
}
yytoken_kind_t DotPatternAction()
{
	LogDebug("DotPatternAction");
	return DOT;
}

yytoken_kind_t TopPositionPatternAction()
{
	LogDebug("TopPositionPatternAction");
	return TOP;
}
yytoken_kind_t BottomPositionPatternAction()
{
	LogDebug("BottomPositionPatternAction");
	return BOTTOM;
}
yytoken_kind_t LeftPositionPatternAction()
{
	LogDebug("LeftPositionPatternAction");
	return LEFT;
}
yytoken_kind_t RightPositionPatternAction()
{
	LogDebug("RightPositionPatternAction");
	return RIGHT;
}
yytoken_kind_t CenterPositionPatternAction()
{
	LogDebug("CenterPositionPatternAction");
	return CENTER;
}
yytoken_kind_t TopRightPositionPatternAction()
{
	LogDebug("TopRightPositionPatternAction");
	return TOP_RIGHT;
}
yytoken_kind_t TopLeftPositionPatternAction()
{
	LogDebug("TopLeftPositionPatternAction");
	return TOP_LEFT;
}
yytoken_kind_t BottomLeftPositionPatternAction()
{
	LogDebug("BottomLeftPositionPatternAction");
	return BOTTOM_LEFT;
}
yytoken_kind_t BottomRightPositionPatternAction()
{
	LogDebug("BottomRightPositionPatternAction");
	return BOTTOM_RIGHT;
}
yytoken_kind_t BottomCenterPositionPatternAction()
{
	LogDebug("BottomCenterPositionPatternAction");
	return BOTTOM_CENTER;
}
yytoken_kind_t TopCenterPositionPatternAction()
{
	LogDebug("TopCenterPositionPatternAction");
	return TOP_CENTER;
}
yytoken_kind_t LeftCenterPositionPatternAction()
{
	LogDebug("LeftCenterPositionPatternAction");
	return LEFT_CENTER;
}
yytoken_kind_t RightCenterPositionPatternAction()
{
	LogDebug("RightCenterPositionPatternAction");
	return RIGHT_CENTER;
}
yytoken_kind_t ChildrenPositionPatternAction()
{
	LogDebug("ChildrenPositionPatternAction");
	return CHILDREN;
}
yytoken_kind_t OpenCurlyPatternAction()
{
	LogDebug("OpenCurlyPatternAction");
	return OPEN_CURLY_BRACKET;
}
yytoken_kind_t CloseCurlyPatternAction()
{
	LogDebug("CloseCurlyPatternAction");
	return CLOSE_CURLY_BRACKET;
}
yytoken_kind_t CloseSquarePatternAction()
{
	LogDebug("CloseSquarePatternAction");
	return CLOSE_SQUARE_BRACKET;
}
yytoken_kind_t OpenSquarePatternAction()
{
	LogDebug("OpenSquarePatternAction");
	return OPEN_SQUARE_BRACKET;
}
yytoken_kind_t ImportPatternAction()
{
	LogDebug("ImportPatternAction");
	return IMPORT;
}
yytoken_kind_t AsPatternAction()
{
	LogDebug("AsPatternAction");
	return AS;
}
yytoken_kind_t TemplatePatternAction()
{
	LogDebug("TemplatePatternAction");
	return TEMPLATE;
}
yytoken_kind_t ScriptPatternAction()
{
	LogDebug("ScriptPatternAction");
	return SCRIPT;
}
yytoken_kind_t JsCodePatternAction(char *lexeme)
{
	LogDebug("JsCodePatternAction: %s", lexeme);
	return JS_CODE;
}
yytoken_kind_t CssCodePatternAction(char *lexeme)
{
	LogDebug("CssCodePatternAction: %s", lexeme);
	return CSS_CODE;
}
yytoken_kind_t StylePatternAction()
{
	LogDebug("StylePatternAction");
	return STYLE;
}
yytoken_kind_t CanvasPatternAction()
{
	LogDebug("CanvasPatternAction");
	return CANVAS;
}
yytoken_kind_t ModulePatternAction()
{

	LogDebug("ModulePatternAction");
	return MODULE;
}
yytoken_kind_t PropsPatternAction()
{
	LogDebug("PropsPatternAction");
	return PROPS;
}

yytoken_kind_t StringPatternAction(char *lexeme)
{
	LogDebug("StringPatternAction: '%s'.", lexeme);
	yylval.string = lexeme;
	return STRING;
}
yytoken_kind_t TextPatternAction(char *lexeme)
{
	LogDebug("TextPatternAction: '%s'.", lexeme);
	yylval.string = lexeme;
	return TEXT;
}

yytoken_kind_t FloatPatternAction(const char *lexeme)
{
	LogDebug("FloatPatternAction: '%s'.", lexeme);
	yylval.floatNumber = atof(lexeme);
	return FLOAT;
}

yytoken_kind_t BooleanPatternAction(const char *lexeme)
{
	LogDebug("BooleanPatternAction: '%s'.", lexeme);
	yylval.boolean = (strcmp(lexeme, "true") == 0);
	return BOOLEAN;
}

yytoken_kind_t IntegerPatternAction(const char *lexeme)
{
	LogDebug("IntegerPatternAction: '%s'.", lexeme);
	yylval.integer = atoi(lexeme);
	return INTEGER;
}

void IgnoredPatternAction(const char *lexeme)
{
	LogDebug("IgnoredPatternAction: '%s'.", lexeme);
}

yytoken_kind_t UnknownPatternAction(const char *lexeme)
{
	LogDebug("UnknownPatternAction: '%s'.", lexeme);
	return YYUNDEF;
}
