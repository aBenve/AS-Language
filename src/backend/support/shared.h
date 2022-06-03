#ifndef SHARED_HEADER
#define SHARED_HEADER

#include <stdio.h>
// Descriptor del archivo de entrada que utiliza Bison.
extern FILE *yyin;

// Descriptor del archivo de salida que utiliza Bison.
extern FILE *yyout;

// Variable global que contiene el número escaneado.
// ! Como no esta el UNION en el bison, yylval por defecto es int.
// extern int yylval;
// extern YYSTYPE yylval;
// Variable global que contiene el número de la línea analizada.
extern int yylineno;

// Longitud de la cadena yytext
extern int yyleng;

// Token actual en el tope de la pila del analizador Bison.
extern char *yytext;

// Función global de manejo de errores en Bison.
extern void yyerror(const char *string);

// Función global del analizador léxico Flex.
extern int yylex(void);

// Función global del analizador sintáctico Bison.
extern int yyparse(void);

// Emular tipo "boolean".
typedef enum
{
	false = 0,
	true = 1
} boolean;

typedef struct tArgument
{
	char *name;
	void *value;
	struct tArgument *next;
} tArgument;

typedef struct tArgumentHeader
{
	int size;
	tArgument *first;
	tArgument *last;
} tArgumentHeader;
typedef struct tVariable
{
	char *name;
	void *value;
	int type;
} tVariable;

typedef struct tConstant
{
	char *name;
	void *value;
} tConstant;
typedef struct tElement
{
	char *name;
	tArgumentHeader *arguments;
	struct tElement *next;
} tElement;

typedef struct tElementHeader
{
	tElement *first;
	tElement *last;
	int size;

} tElementHeader;

typedef struct tPosToken
{
	int token;
} tPosToken;

typedef struct tPositionItem
{
	tPosToken *posToken;
	tVariable *variable; // Solo puede tener 1 de estos 3 valores.
	tConstant *constant;
	tElementHeader *elements;
	struct tPositionItem *next;
} tPositionItem;

typedef struct tPositionHeader
{
	tPositionItem *first;
	tPositionItem *last;
	int size;
} tPositionHeader;

typedef struct tStyle
{
	char *content;
} tStyle;
typedef struct tScript
{
	char *content;
} tScript;

typedef struct tTemplate
{
	tPositionHeader *positions;
} tTemplate;
typedef struct tDefinition
{
	tTemplate *template;
	tStyle *style;
	tScript *script;
} tDefinition;

typedef struct tComponent
{
	char *name;
	tDefinition *definition;
	struct tComponent *next;
} tComponent;

typedef struct tComponentHeader
{
	tComponent *first;
	tComponent *last;
	int size;
} tComponentHeader;

typedef struct tComponentAsCanvas
{
	char *name;
	tDefinition *definition;
} tComponentAsCanvas;

typedef struct tCanvas
{
	tDefinition *definition;
} tCanvas;

typedef struct tModule
{
	tComponentAsCanvas *canvas;
	tComponentHeader *components;
} tModule;

// Estado global de toda la aplicación.
typedef struct
{

	// Indica si la compilación tuvo problemas hasta el momento:
	boolean succeed;

	// Indica el resultado de la compilación:
	tModule *result;

	// Agregar una pila para almacenar tokens/nodos.
	// Agregar un nodo hacia la raíz del árbol de sintaxis abstracta.
	// Agregar una tabla de símbolos.
	// ...

} CompilerState;

// El estado se define e inicializa en el archivo "main.c":
extern CompilerState state;

// Estructuras para el backend.

#endif
