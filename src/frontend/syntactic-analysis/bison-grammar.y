%{

#include "bison-actions.h"

%}

/*
* Util para el backend.

%union{
	tComponent * component;
	tComponent ** componentList;
	tModule * modules;
	tComponentAsCanvas * componentAsCanvas;
	tDefinition * definition;
	tCanvas * canvas;
	tArgument * argument;
	tArgument ** argumentList;
	tElement * element;
	tElement ** elementList;
	tPositionItem * positionItem;
	tPositionItem ** positioning;
	tTemplate * template;
	tStyle * style;
	tScript * script;
	char * string;
	int integer;
	double floatNumber;
	boolean boolean;
	int token;
}


%type <modules> modules program
%type <component> component
%type <componentList> componentList
%type <canvas> canvas
%type <componentAsCanvas> componentAsCanvas
%type <positionItem> positionItem
%type <positioning> positioning
%type <template> template
%type <style> style
%type <script> script
%type <definition> definition
%type <element> element 
%type <elementList> elementList
%type <argumentList> argumentList
%type <argument> argument



%token <token> OPEN_PARENTHESIS
%token <token> CLOSE_PARENTHESIS
%token <token> OPEN_CURLY_BRACKET
%token <token> CLOSE_CURLY_BRACKET
%token <token> OPEN_SQUARE_BRACKET
%token <token> CLOSE_SQUARE_BRACKET

%token <token> COMMA
%token <token> COLON
%token <token> LINE_COMMENT

%token <integer> INTEGER
%token <string> STRING
%token <floatNumber> FLOAT
%token <boolean> BOOLEAN

%token <token> RIGHT
%token <token> LEFT
%token <token> BOTTOM
%token <token> TOP
%token <token> CENTER

%token <token> TOP_RIGHT
%token <token> TOP_LEFT
%token <token> BOTTOM_RIGHT
%token <token> BOTTOM_LEFT

%token <token> TOP_CENTER
%token <token> BOTTOM_CENTER
%token <token> LEFT_CENTER
%token <token> RIGHT_CENTER

%token <token> CHILDREN


%token <token> MODULE
%token <token> AS
%token <token> CANVAS
%token <token> SCRIPT
%token <token> TEMPLATE
%token <token> STYLE

%token <token> IMPORT

*/


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


%token OPEN_PARENTHESIS
%token CLOSE_PARENTHESIS
%token OPEN_CURLY_BRACKET
%token CLOSE_CURLY_BRACKET
%token OPEN_SQUARE_BRACKET
%token CLOSE_SQUARE_BRACKET

%token COMMA
%token COLON
%token LINE_COMMENT
%token DOLLAR
%token DOT

%token INTEGER
%token STRING
%token FLOAT
%token BOOLEAN
%token TEXT

%token RIGHT
%token LEFT
%token BOTTOM
%token TOP
%token CENTER

%token TOP_RIGHT
%token TOP_LEFT
%token BOTTOM_RIGHT
%token BOTTOM_LEFT

%token TOP_CENTER
%token BOTTOM_CENTER
%token LEFT_CENTER
%token RIGHT_CENTER

%token CHILDREN

%token MODULE
%token PROPS
%token AS
%token CANVAS
%token SCRIPT
%token TEMPLATE
%token STYLE
%token CSS_CODE
%token JS_CODE

%token IMPORT

%%

	program: modules { printf("ProgramGrammarAction\n"); state.succeed = true;  /* $$ = ProgramModulesGrammarAction($1); */}
		;
	
	modules: canvas { /* $$ = CanvasModuleGrammarAction($1); */ }
		| canvas componentList { /* $$ = MultipleComponentModuleGrammarAction($1, $2); */ }
		| componentAsCanvas { /* $$ = ComponentAsCanvasModuleGrammarAction($1);  */ }
		| componentAsCanvas componentList { /* $$ = MultipleComponentAsCancasModuleGrammarAction($1, $2); */  }
		;

	componentList: componentList component { /* $$ = MultipleComponentListGrammarAction($1, $2); */  }
		| component { /* $$ = SingleComponentListGrammarAction($1); */ }
		;

	component: MODULE STRING OPEN_CURLY_BRACKET definition CLOSE_CURLY_BRACKET 	{ /* $$ = ComponentGrammarAction($2, $4); */   }
		;

	componentAsCanvas:	MODULE STRING AS CANVAS OPEN_CURLY_BRACKET definition CLOSE_CURLY_BRACKET { /* $$ = ComponentAsCanvasGrammarAction($2, $6); */  }
		;

	canvas: MODULE CANVAS OPEN_CURLY_BRACKET definition CLOSE_CURLY_BRACKET 	{ /* $$ = CanvasGrammarAction($4); */  }
		;

	definition: template { /*  $$ = TemplateDefinitionGrammarAction($1);  */ }
		| template script { /*  $$ = TemplateScriptDefinitionGrammarAction($1, $2); */ }
		| template style { /* $$ = TemplateStyleDefinitionGrammarAction($1, $2); */ }
		| template script style { /* $$ = TemplateScriptStyleDefinitionGrammarAction($1, $2, $3); */ }
		| template style script { /* $$ = TemplateStyleScriptDefinitionGrammarAction($1, $2, $3); */ }
		;

	template: TEMPLATE COLON OPEN_CURLY_BRACKET positioning CLOSE_CURLY_BRACKET { /* $$ = TemplateGrammarAction($4); */ }
		| TEMPLATE COLON OPEN_CURLY_BRACKET CLOSE_CURLY_BRACKET { /* $$ = TemplateEmptyGrammarAction(); */ }
		;

	positioning: positioning COMMA positionItem { /* $$ = MultiplePositioningGrammarAction($1, $3); */ }
		| positionItem { /*$$ = SinglePositionItemGrammarAction($1); */ }
		;

	positionItem: pItem COLON elementList { /* $$ = PositionItemElementListGrammarAction($1, $3); */ }
		| pItem COLON variable { /* $$ = PositionItemVariableGrammarAction($1, $3); */ }
		;

	pItem: 	TOP_RIGHT | TOP_LEFT | BOTTOM_RIGHT | BOTTOM_LEFT | TOP_CENTER | BOTTOM_CENTER | LEFT_CENTER | RIGHT_CENTER | RIGHT | LEFT | TOP | BOTTOM | CENTER | CHILDREN;

	script: SCRIPT COLON JS_CODE  { /* $$ = ScriptGrammarAction(); */ }
		;

	style: STYLE COLON CSS_CODE  {/*  $$ = StyleGrammarAction(); */ }
		;

	elementList: OPEN_SQUARE_BRACKET elementList COMMA element  CLOSE_SQUARE_BRACKET{ /* $$ = MultipleElementListGrammarAction($2, $4); */ }
		| OPEN_SQUARE_BRACKET element CLOSE_SQUARE_BRACKET { /* $$ = OneElementListGrammarAction($2, null); */ }
		;
	element: STRING { /*$$ = ElementGrammarAction($1); 	*/ }
		| STRING OPEN_PARENTHESIS argumentList CLOSE_PARENTHESIS { /*$$ = ElementWithArgumentsGrammarAction($1, $3); */ }
		;
	variable: STRING { /* $$ = VariableGrammarAction($1); */ }
		| DOLLAR OPEN_CURLY_BRACKET STRING CLOSE_CURLY_BRACKET { /* $$ = DollarVariableGrammarAction($3); */ }
		| PROPS DOT STRING { /* $$ = PropVariableGrammarAction($3); */ }
		| TEXT { /* $$ = StringVariableGrammarAction($1); */ }
		;

	argumentList: argument { /* $$ = SingleArgumentGrammarAction($1); */ }
		| argumentList COMMA argument { /* $$ = MultipleArgumentGrammarAction($1, $3); */ }
		;
	argument: STRING COLON STRING {/* $$ = StringArgumentGrammarAction($1, $3);	*/ }
		| STRING COLON INTEGER {/* $$ = IntegerArgumentGrammarAction($1, $3);  */ }
		| STRING COLON FLOAT { /* $$ = FloatArgumentGrammarAction($1, $3); */ }
		| STRING COLON BOOLEAN { /* $$ = BooleanArgumentGrammarAction($1, $3); */ }
		| STRING COLON OPEN_PARENTHESIS argument CLOSE_PARENTHESIS { /* $$ = ConcatenatedArgumentGrammarAction($1, $4); */ }
		| STRING { /* $$ = OnlyStringArgumentGrammarAction($1); */ }
		| INTEGER { /* $$ = OnlyIntegerArgumentGrammarAction($1); */ }
		| FLOAT { /* $$ = OnlyFloatArgumentGrammarAction($1); */ }
		| BOOLEAN { /* $$ = OnlyBooleanArgumentGrammarAction($1); */ }
		;
%%