%{

#include "bison-actions.h"

%}

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

%token <integer> INTEGER
%token <string> STRING
%token <floatNumber> FLOAT
%token <boolean> BOOLEAN

%token <token> TOP
%token <token> BOTTOM
%token <token> LEFT
%token <token> RIGHT
%token <token> TOP_LEFT
%token <token> TOP_RIGHT
%token <token> BOTTOM_LEFT
%token <token> BOTTOM_RIGHT
%token <token> CENTER_RIGHT
%token <token> CENTER_LEFT
%token <token> CENTER_BOTTOM
%token <token> CENTER_TOP
%token <token> CHILDREN
%token <token> CENTER

%token <token> OPEN_CURLY_BRACKET
%token <token> CLOSE_CURLY_BRACKET
%token <token> OPEN_SQUARE_BRACKET
%token <token> CLOSE_SQUARE_BRACKET

%token <token> IMPORT
%token <token> MODULE
%token <token> CANVAS
%token <token> AS
%token <token> TEMPLATE
%token <token> SCRIPT
%token <token> STYLE

%token <token> LINE_COMMENT
%token <token> COLON
%token <token> COMMA


%%

	program: modules {  $$ = ProgramModulesGrammarAction($1); }
		;
	
	modules: canvas {  $$ = CanvasModuleGrammarAction($1);  }
		| canvas componentList {  $$ = MultipleComponentModuleGrammarAction($1, $2);  }
		| componentAsCanvas {  $$ = ComponentAsCanvasModuleGrammarAction($1);  }
		| componentAsCanvas componentList {  $$ = MultipleComponentAsCancasModuleGrammarAction($1, $2);  }
		;

	componentList: componentList component {  $$ = MultipleComponentListGrammarAction($1, $2);  }
		| component {  $$ = SingleComponentListGrammarAction($1);  }
		;

	component: MODULE STRING OPEN_CURLY_BRACKET definition CLOSE_CURLY_BRACKET 	{  $$ = ComponentGrammarAction($2, $4);  }
		;

	componentAsCanvas:	MODULE STRING AS CANVAS OPEN_CURLY_BRACKET definition CLOSE_CURLY_BRACKET {  $$ = ComponentAsCanvasGrammarAction($2, $6);  }
		;

	canvas: MODULE CANVAS OPEN_CURLY_BRACKET definition CLOSE_CURLY_BRACKET 	{  $$ = CanvasGrammarAction($4);  }
		;

	definition: template { /*  $$ = TemplateDefinitionGrammarAction($1);  */ }
		| template script { /*  $$ = TemplateScriptDefinitionGrammarAction($1, $2); */ }
		| template style { /* $$ = TemplateStyleDefinitionGrammarAction($1, $2); */ }
		| template script style { /* $$ = TemplateScriptStyleDefinitionGrammarAction($1, $2, $3); */ }
		;

	template: TEMPLATE COLON OPEN_CURLY_BRACKET positioning CLOSE_CURLY_BRACKET { /* $$ = TemplateGrammarAction($4); */ }
		;

	positioning: positioning COMMA positionItem { /* $$ = MultiplePositioningGrammarAction($1, $3); */ }
		| positionItem { /*$$ = SinglePositionItemGrammarAction($1); */ }
		;

	positionItem: TOP COLON OPEN_SQUARE_BRACKET elementList CLOSE_SQUARE_BRACKET { /* $$ = TopPositioningGrammarAction($1,$4); */ }
		| BOTTOM COLON OPEN_SQUARE_BRACKET elementList CLOSE_SQUARE_BRACKET {/* $$ = BottomPositioningGrammarAction($1,$4); */ }
		| LEFT COLON OPEN_SQUARE_BRACKET elementList CLOSE_SQUARE_BRACKET {/* $$ = LeftPositioningGrammarAction($1,$4); */ }
		| RIGHT COLON OPEN_SQUARE_BRACKET elementList CLOSE_SQUARE_BRACKET { /* $$ = RightositioningGrammarAction($1,$4); */ }
		| TOP_RIGHT COLON OPEN_SQUARE_BRACKET elementList CLOSE_SQUARE_BRACKET { /*	$$ = TopRightPositioningGrammarAction($1,$4); */ }
		| TOP_LEFT COLON OPEN_SQUARE_BRACKET elementList CLOSE_SQUARE_BRACKET {/* $$ = TopLeftPositioningGrammarAction($1,$4); 	*/ }
		| BOTTOM_RIGHT COLON OPEN_SQUARE_BRACKET elementList CLOSE_SQUARE_BRACKET { /* $$ = BottomRightPositioningGrammarAction($1,$4); */ }
		| BOTTOM_LEFT COLON OPEN_SQUARE_BRACKET elementList CLOSE_SQUARE_BRACKET { /* $$ = BottomLeftPositioningGrammarAction($1,$4); */ }
		| CENTER COLON OPEN_SQUARE_BRACKET elementList CLOSE_SQUARE_BRACKET { /* $$ = CenterPositioningGrammarAction($1,$4); */ }
		| CENTER_BOTTOM COLON OPEN_SQUARE_BRACKET elementList CLOSE_SQUARE_BRACKET {/* $$ = CenterBottomPositioningGrammarAction($1,$4); */ }
		| CENTER_LEFT COLON OPEN_SQUARE_BRACKET elementList CLOSE_SQUARE_BRACKET { /* $$ = CenterLeftPositioningGrammarAction($1,$4); */ }
		| CENTER_RIGHT COLON OPEN_SQUARE_BRACKET elementList CLOSE_SQUARE_BRACKET { /* $$ = CenterRightPositioningGrammarAction($1,$4); */ }
		| CENTER_TOP COLON OPEN_SQUARE_BRACKET elementList CLOSE_SQUARE_BRACKET {/* $$ = CenterTopPositioningGrammarAction($1,$4); */ }
		| CHILDREN COLON OPEN_SQUARE_BRACKET elementList CLOSE_SQUARE_BRACKET { /* $$ = ChildrenPositioningGrammarAction($1,$4); */ }
		;

	script: SCRIPT COLON OPEN_CURLY_BRACKET CLOSE_CURLY_BRACKET { /* $$ = ScriptGrammarAction(); */ }
		;

	style: STYLE COLON OPEN_CURLY_BRACKET CLOSE_CURLY_BRACKET {/*  $$ = StyleGrammarAction(); */ }
		;

	elementList: elementList COMMA element { /* $$ = MultipleElementListGrammarAction($1, $3); */ }
		| element { /* $$ = OneElementListGrammarAction($1, null); */ }
		;
	element: STRING { /*$$ = ElementGrammarAction($1); 	*/ }
		| STRING OPEN_PARENTHESIS argumentList CLOSE_PARENTHESIS { /*$$ = ElementWithArgumentsGrammarAction($1, $3); */ }
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