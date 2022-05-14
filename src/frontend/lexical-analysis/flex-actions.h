#ifndef FLEX_ACTIONS_HEADER
#define FLEX_ACTIONS_HEADER

#include "../../backend/support/shared.h"
#include "../../backend/support/logger.h"
#include "../syntactic-analysis/bison-parser.h"

// ! Quiza sirva para el backend.
// extern tYYSTYPE yylval;
/**
 * Se definen los diferentes IDs de cada token disponible para el scanner Flex.
 */

// typedef enum TokenID
// {

// 	// Por defecto, el valor "0" hace fallar el analizador sintáctico.
// 	UNKNOWN = 0,

// 	// Código de error de Bison, que permite abortar el escaneo de lexemas cuando
// 	// se presente un patrón desconocido. El número "257" coincide con el valor
// 	// que Bison le otorga por defecto, pero además permite que el resto de
// 	// tokens continúen desde el valor "258" lo que permite proteger los IDs
// 	// internos que Bison reserva para crear "tokens literales":
// 	YYUNDEF = 257,

// 	// Paréntesis.
// 	OPEN_PARENTHESIS,
// 	CLOSE_PARENTHESIS,
// 	OPEN_CURLY_BRACKET,
// 	CLOSE_CURLY_BRACKET,
// 	OPEN_SQUARE_BRACKET,
// 	CLOSE_SQUARE_BRACKET,

// 	// Separators.
// 	COMMA,
// 	COLON,
// 	LINE_COMMENT,
// 	DOLLAR,
// 	DOT,
// 	// Tipos de dato.
// 	INTEGER,
// 	STRING,
// 	FLOAT,
// 	BOOLEAN,
// 	TEXT,
// 	// Template positions.
// 	RIGHT,
// 	LEFT,
// 	BOTTOM,
// 	TOP,
// 	CENTER,

// 	TOP_RIGHT,
// 	TOP_LEFT,
// 	BOTTOM_RIGHT,
// 	BOTTOM_LEFT,

// 	TOP_CENTER,
// 	BOTTOM_CENTER,
// 	LEFT_CENTER,
// 	RIGHT_CENTER,

// 	CHILDREN,

// 	// Parts of module
// 	MODULE,
// 	PROPS,
// 	AS,
// 	CANVAS,
// 	SCRIPT,
// 	TEMPLATE,
// 	STYLE,
// 	CSS_CODE,
// 	JS_CODE,

// 	IMPORT

// } TokenID;

/**
 * Se definen las acciones a ejecutar sobre cada patrón hallado mediante el
 * analizador léxico Flex. Este analizador solo puede identificar
 * construcciones regulares, ya que utiliza un autómata finito determinístico
 * (a.k.a. DFA), como mecanismo de escaneo y reconocimiento.
 */

yytoken_kind_t OpenParenthesisPatternAction();
yytoken_kind_t CloseParenthesisPatternAction();
yytoken_kind_t ColonPatternAction();
yytoken_kind_t CommentPatternAction();
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
