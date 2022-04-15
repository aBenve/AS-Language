#ifndef FLEX_ACTIONS_HEADER
#define FLEX_ACTIONS_HEADER

#include "../../backend/support/shared.h"
#include "../../backend/support/logger.h"
//#include "../syntactic-analysis/bison-parser.h"

extern tYYSTYPE yylval;
/**
 * Se definen los diferentes IDs de cada token disponible para el scanner Flex.
 */
typedef enum TokenID
{

	// Por defecto, el valor "0" hace fallar el analizador sintáctico.
	UNKNOWN = 0,

	// Código de error de Bison, que permite abortar el escaneo de lexemas cuando
	// se presente un patrón desconocido. El número "257" coincide con el valor
	// que Bison le otorga por defecto, pero además permite que el resto de
	// tokens continúen desde el valor "258" lo que permite proteger los IDs
	// internos que Bison reserva para crear "tokens literales":
	YYUNDEF = 257,

	// Paréntesis.
	OPEN_PARENTHESIS,
	CLOSE_PARENTHESIS,
	OPEN_CURLY_BRACKET,
	CLOSE_CURLY_BRACKET,
	OPEN_SQUARE_BRACKET,
	CLOSE_SQUARE_BRACKET,

	// Separators.
	COMMA,
	COLON,
	LINE_COMMENT,

	// Tipos de dato.
	INTEGER,
	STRING,
	FLOAT,
	BOOLEAN,
	// Template positions.
	RIGHT,
	LEFT,
	BOTTOM,
	TOP,
	CENTER,

	TOP_RIGHT,
	TOP_LEFT,
	BOTTOM_RIGHT,
	BOTTOM_LEFT,

	TOP_CENTER,
	BOTTOM_CENTER,
	LEFT_CENTER,
	RIGHT_CENTER,

	CHILDREN,

	// Parts of module
	MODULE,
	AS,
	CANVAS,
	SCRIPT,
	TEMPLATE,
	STYLE,

	IMPORT

} TokenID;

/**
 * Se definen las acciones a ejecutar sobre cada patrón hallado mediante el
 * analizador léxico Flex. Este analizador solo puede identificar
 * construcciones regulares, ya que utiliza un autómata finito determinístico
 * (a.k.a. DFA), como mecanismo de escaneo y reconocimiento.
 */

TokenID ModulePatternAction(const char *lexeme);
TokenID CanvasPatternAction(const char *lexeme);
TokenID StringPatternAction(char *lexeme);
TokenID FloatPatternAction(const char *lexeme);
TokenID BooleanPatternAction(const char *lexeme);

TokenID IntegerPatternAction(const char *lexeme);

void IgnoredPatternAction(const char *lexeme);

TokenID UnknownPatternAction(const char *lexeme);

#endif
