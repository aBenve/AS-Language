//#include "../../backend/support/logger.h"
#include "flex-actions.h"

#include <stdlib.h>
#include <string.h>
/**
 * Implementación de "flex-rules.h".
 */
TokenID CanvasPatternAction(const char *lexeme)
{
	LogDebug("CanvasPatternAction: module");
	return CANVAS;
}
TokenID ModulePatternAction(const char *lexeme)
{

	LogDebug("ModulePatternAction: module");
	return MODULE;
}

TokenID StringPatternAction(char *lexeme)
{
	LogDebug("StringPatternAction: '%s'.", lexeme);
	yylval.string = lexeme;
	return STRING;
}

TokenID FloatPatternAction(const char *lexeme)
{
	LogDebug("FloatPatternAction: '%s'.", lexeme);
	yylval.floatNumber = atof(lexeme);
	return FLOAT;
}

TokenID BooleanPatternAction(const char *lexeme)
{
	LogDebug("BooleanPatternAction: '%s'.", lexeme);
	yylval.boolean = (strcmp(lexeme, "true") == 0);
	return BOOLEAN;
}

TokenID IntegerPatternAction(const char *lexeme)
{
	LogDebug("IntegerPatternAction: '%s'.", lexeme);
	yylval.integer = atoi(lexeme);
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
