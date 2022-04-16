#ifndef SHARED_HEADER
#define SHARED_HEADER

#include <stdio.h>
// Descriptor del archivo de entrada que utiliza Bison.
extern FILE *yyin;

// Descriptor del archivo de salida que utiliza Bison.
extern FILE *yyout;

// Variable global que contiene el número escaneado.
// ! Como no esta el UNION en el bison, yylval por defecto es int.
extern int yylval;

// Variable global que contiene el número de la línea analizada.
extern int yylineno;

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

// Estado global de toda la aplicación.
typedef struct
{

	// Indica si la compilación tuvo problemas hasta el momento:
	boolean succeed;

	// Indica el resultado de la compilación:
	int result;

	// Agregar una pila para almacenar tokens/nodos.
	// Agregar un nodo hacia la raíz del árbol de sintaxis abstracta.
	// Agregar una tabla de símbolos.
	// ...

} CompilerState;

// El estado se define e inicializa en el archivo "main.c":
extern CompilerState state;

// Estructuras para el backend.

/*
typedef struct tArgument
{
	char *name;
	void *value;
} tArgument;
typedef struct tElement
{
	char *name;
	char **tArgument;
} tElement;
typedef struct tPositionItem
{
	char *name;
	char **tElement;
} tPositionItem;

typedef struct tStyle
{
	char *value;
} tStyle;
typedef struct tScript
{
	char *value;
} tScript;

typedef struct tTemplate
{
	tPositionItem **positions;
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
} tComponent;

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
	tComponent **components;
} tModule;

typedef union tYYSTYPE
{
	tComponent *component;
	tComponent **componentList;
	tModule *modules;
	tComponentAsCanvas *componentAsCanvas;
	tDefinition *definition;
	tCanvas *canvas;
	tArgument *argument;
	tArgument **argumentList;
	tElement *element;
	tElement **elementList;
	tPositionItem *positionItem;
	tPositionItem **positioning;
	tTemplate *template;
	tStyle *style;
	tScript *script;
	char *string;
	int integer;
	double floatNumber;
	boolean boolean;
	int token;
} tYYSTYPE;
*/
#endif
