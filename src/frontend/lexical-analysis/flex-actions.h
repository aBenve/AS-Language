#ifndef FLEX_ACTIONS_HEADER
#define FLEX_ACTIONS_HEADER

#include "../../backend/support/shared.h"
#include "../../backend/support/logger.h"
//#include "../syntactic-analysis/bison-parser.h"

// ! Quiza sirva para el backend.
// extern tYYSTYPE yylval;
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
	DOLLAR,
	DOT,
	// Tipos de dato.
	INTEGER,
	STRING,
	FLOAT,
	BOOLEAN,
	TEXT,
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
	PROPS,
	AS,
	CANVAS,
	SCRIPT,
	TEMPLATE,
	STYLE,
	CSS_CODE,
	JS_CODE,

	IMPORT

} TokenID;

/**
 * Se definen las acciones a ejecutar sobre cada patrón hallado mediante el
 * analizador léxico Flex. Este analizador solo puede identificar
 * construcciones regulares, ya que utiliza un autómata finito determinístico
 * (a.k.a. DFA), como mecanismo de escaneo y reconocimiento.
 */

TokenID OpenParenthesisPatternAction();
TokenID CloseParenthesisPatternAction();
TokenID ColonPatternAction();
TokenID CommentPatternAction();
TokenID CommaPatternAction();
TokenID DollarPatternAction();
TokenID DotPatternAction();
TokenID TopPositionPatternAction();
TokenID BottomPositionPatternAction();
TokenID LeftPositionPatternAction();
TokenID RightPositionPatternAction();
TokenID CenterPositionPatternAction();
TokenID TopRightPositionPatternAction();
TokenID TopLeftPositionPatternAction();
TokenID BottomLeftPositionPatternAction();
TokenID BottomRightPositionPatternAction();
TokenID BottomCenterPositionPatternAction();
TokenID TopCenterPositionPatternAction();
TokenID LeftCenterPositionPatternAction();
TokenID RightCenterPositionPatternAction();
TokenID ChildrenPositionPatternAction();
TokenID OpenCurlyPatternAction();
TokenID CloseCurlyPatternAction();
TokenID CloseSquarePatternAction();
TokenID OpenSquarePatternAction();
TokenID ImportPatternAction();
TokenID PropsPatternAction();
TokenID AsPatternAction();
TokenID TemplatePatternAction();
TokenID ScriptPatternAction();
TokenID JsCodePatternAction(char *lexeme);
TokenID StylePatternAction();
TokenID CssCodePatternAction(char *lexeme);
TokenID ModulePatternAction();
TokenID CanvasPatternAction();
TokenID StringPatternAction(char *lexeme);
TokenID TextPatternAction(char *lexeme);
TokenID FloatPatternAction(const char *lexeme);
TokenID BooleanPatternAction(const char *lexeme);

TokenID IntegerPatternAction(const char *lexeme);

void IgnoredPatternAction(const char *lexeme);

TokenID UnknownPatternAction(const char *lexeme);

#endif
