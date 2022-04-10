#include "../../backend/support/logger.h"
#include "flex-actions.h"
#include <stdlib.h>

/**
 * Implementación de "flex-rules.h".
 */

TokenID StringPatternAction(const char *lexeme)
{
	LogDebug("StringPatternAction: '%s'.", lexeme);
	yylval = lexeme;
	return STRING;
}

TokenID FloatPatternAction(const char *lexeme)
{
	LogDebug("FloatPatternAction: '%s'.", lexeme);
	yylval = atoi(lexeme);
	return FLOAT;
}

TokenID BooleanPatternAction(const char *lexeme)
{
	LogDebug("BooleanPatternAction: '%s'.", lexeme);
	yylval = lexeme;
	return BOOLEAN;
}

TokenID IntegerPatternAction(const char *lexeme)
{
	LogDebug("IntegerPatternAction: '%s'.", lexeme);
	yylval = atoi(lexeme);
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
