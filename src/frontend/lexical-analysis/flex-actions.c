//#include "../../backend/support/logger.h"
#include "flex-actions.h"

#include <stdlib.h>
#include <string.h>
/**
 * Implementación de "flex-rules.h".
 */

TokenID OpenParenthesisPatternAction()
{
	LogDebug("OpenParenthesisPatternAction");
	return OPEN_PARENTHESIS;
}
TokenID CloseParenthesisPatternAction()
{
	LogDebug("CloseParenthesisPatternAction");
	return CLOSE_PARENTHESIS;
}
TokenID ColonPatternAction()
{
	LogDebug("ColonPatternAction");
	return COLON;
}
TokenID CommentPatternAction()
{
	LogDebug("CommentPatternAction");
	return LINE_COMMENT;
}
TokenID CommaPatternAction()
{
	LogDebug("CommaPatternAction");
	return COMMA;
}
TokenID DollarPatternAction()
{
	LogDebug("DollarPatternAction");
	return DOLLAR;
}
TokenID DotPatternAction()
{
	LogDebug("DotPatternAction");
	return DOT;
}

TokenID TopPositionPatternAction()
{
	LogDebug("TopPositionPatternAction");
	return TOP;
}
TokenID BottomPositionPatternAction()
{
	LogDebug("BottomPositionPatternAction");
	return BOTTOM;
}
TokenID LeftPositionPatternAction()
{
	LogDebug("LeftPositionPatternAction");
	return LEFT;
}
TokenID RightPositionPatternAction()
{
	LogDebug("RightPositionPatternAction");
	return RIGHT;
}
TokenID CenterPositionPatternAction()
{
	LogDebug("CenterPositionPatternAction");
	return CENTER;
}
TokenID TopRightPositionPatternAction()
{
	LogDebug("TopRightPositionPatternAction");
	return TOP_RIGHT;
}
TokenID TopLeftPositionPatternAction()
{
	LogDebug("TopLeftPositionPatternAction");
	return TOP_LEFT;
}
TokenID BottomLeftPositionPatternAction()
{
	LogDebug("BottomLeftPositionPatternAction");
	return BOTTOM_LEFT;
}
TokenID BottomRightPositionPatternAction()
{
	LogDebug("BottomRightPositionPatternAction");
	return BOTTOM_RIGHT;
}
TokenID BottomCenterPositionPatternAction()
{
	LogDebug("BottomCenterPositionPatternAction");
	return BOTTOM_CENTER;
}
TokenID TopCenterPositionPatternAction()
{
	LogDebug("TopCenterPositionPatternAction");
	return TOP_CENTER;
}
TokenID LeftCenterPositionPatternAction()
{
	LogDebug("LeftCenterPositionPatternAction");
	return LEFT_CENTER;
}
TokenID RightCenterPositionPatternAction()
{
	LogDebug("RightCenterPositionPatternAction");
	return RIGHT_CENTER;
}
TokenID ChildrenPositionPatternAction()
{
	LogDebug("ChildrenPositionPatternAction");
	return CHILDREN;
}
TokenID OpenCurlyPatternAction()
{
	LogDebug("OpenCurlyPatternAction");
	return OPEN_CURLY_BRACKET;
}
TokenID CloseCurlyPatternAction()
{
	LogDebug("CloseCurlyPatternAction");
	return CLOSE_CURLY_BRACKET;
}
TokenID CloseSquarePatternAction()
{
	LogDebug("CloseSquarePatternAction");
	return CLOSE_SQUARE_BRACKET;
}
TokenID OpenSquarePatternAction()
{
	LogDebug("OpenSquarePatternAction");
	return OPEN_SQUARE_BRACKET;
}
TokenID ImportPatternAction()
{
	LogDebug("ImportPatternAction");
	return IMPORT;
}
TokenID AsPatternAction()
{
	LogDebug("AsPatternAction");
	return AS;
}
TokenID TemplatePatternAction()
{
	LogDebug("TemplatePatternAction");
	return TEMPLATE;
}
TokenID ScriptPatternAction()
{
	LogDebug("ScriptPatternAction");
	return SCRIPT;
}
TokenID JsCodePatternAction(char *lexeme)
{
	LogDebug("JsCodePatternAction: %s", lexeme);
	return JS_CODE;
}
TokenID CssCodePatternAction(char *lexeme)
{
	LogDebug("CssCodePatternAction: %s", lexeme);
	return CSS_CODE;
}
TokenID StylePatternAction()
{
	LogDebug("StylePatternAction");
	return STYLE;
}
TokenID CanvasPatternAction()
{
	LogDebug("CanvasPatternAction");
	return CANVAS;
}
TokenID ModulePatternAction()
{

	LogDebug("ModulePatternAction");
	return MODULE;
}
TokenID PropsPatternAction()
{
	LogDebug("PropsPatternAction");
	return PROPS;
}

TokenID StringPatternAction(char *lexeme)
{
	LogDebug("StringPatternAction: '%s'.", lexeme);
	// yylval.string = lexeme;
	return STRING;
}
TokenID TextPatternAction(char *lexeme)
{
	LogDebug("TextPatternAction: '%s'.", lexeme);
	// yylval.string = lexeme;
	return TEXT;
}

TokenID FloatPatternAction(const char *lexeme)
{
	LogDebug("FloatPatternAction: '%s'.", lexeme);
	// yylval.floatNumber = atof(lexeme);
	return FLOAT;
}

TokenID BooleanPatternAction(const char *lexeme)
{
	LogDebug("BooleanPatternAction: '%s'.", lexeme);
	// yylval.boolean = (strcmp(lexeme, "true") == 0);
	return BOOLEAN;
}

TokenID IntegerPatternAction(const char *lexeme)
{
	LogDebug("IntegerPatternAction: '%s'.", lexeme);
	// yylval.integer = atoi(lexeme);
	return INTEGER;
}

void IgnoredPatternAction(const char *lexeme)
{
	LogDebug("IgnoredPatternAction: '%s'.", lexeme);
}

TokenID UnknownPatternAction(const char *lexeme)
{
	LogDebug("UnknownPatternAction: '%s'.", lexeme);
	return YYUNDEF;
}
