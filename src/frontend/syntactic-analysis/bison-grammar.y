%{

#include "bison-actions.h"

%}

%token OPEN_PARENTHESIS
%token CLOSE_PARENTHESIS

%token INTEGER
%token STRING
%token FLOAT
%token BOOLEAN

%token TOP
%token BOTTOM
%token LEFT
%token RIGHT
%token TOP_LEFT
%token TOP_RIGHT
%token BOTTOM_LEFT
%token BOTTOM_RIGHT
%token CENTER_RIGHT
%token CENTER_LEFT
%token CENTER_BOTTOM
%token CENTER_TOP
%token CHILDREN
%token CENTER

%token OPEN_CURLY_BRACKET
%token CLOSE_CURLY_BRACKET
%token OPEN_SQUARE_BRACKET
%token CLOSE_SQUARE_BRACKET

%token IMPORT
%token MODULE
%token CANVAS
%token AS
%token TEMPLATE
%token SCRIPT
%token STYLE

%token LINE_COMMENT
%token COLON
%token COMMA


%%

	program: modules 
		{ $$ = ProgramModulesGrammarAction($1); }
		;
	
	modules: canvas { $$ = CanvasModuleGrammarAction($1); }
		canvas componentList { $$ = MultipleComponentModuleGrammarAction($1, $2); }
		;

	componentList: componentList component { $$ = MultipleComponentListGrammarAction($1, $2); }
		| component { $$ = SingleComponentListGrammarAction($1); }
		;

	component: module STRING OPEN_CURLY_BRACKET definition CLOSE_CURLY_BRACKET 	{ $$ = ComponentGrammarAction($2, $4); }
		;

	canvas: module CANVAS OPEN_CURLY_BRACKET definition CLOSE_CURLY_BRACKET 	{ $$ = CanvasGrammarAction($4); }
		module STRING AS CANVAS OPEN_CURLY_BRACKET definition CLOSE_CURLY_BRACKET { $$ = ComponentAsCanvasGrammarAction($2, $6); }
		;

	definition: template { $$ = TemplateDefinitionGrammarAction($1); }
		| template script { $$ = TemplateScriptDefinitionGrammarAction($1, $2); }
		| template style { $$ = TemplateStyleDefinitionGrammarAction($1, $2); }
		| template script style { $$ = TemplateScriptStyleDefinitionGrammarAction($1, $2, $3); }
		;

	template: TEMPLATE OPEN_CURLY_BRACKET positioning CLOSE_CURLY_BRACKET { $$ = TemplateGrammarAction($3); }
		;

	positioning: positioning COMMA positionItem { $$ = MultiplePositioningGrammarAction($1, $2); }
		positionItem { $$ = SinglePositionItemGrammarAction($1); }
		;

	positionItem: TOP COLON OPEN_SQUARE_BRACKET elementList CLOSE_SQUARE_BRACKET { $$ = TopPositioningGrammarAction($1,$3); }
		| BOTTOM COLON OPEN_SQUARE_BRACKET elementList CLOSE_SQUARE_BRACKET { $$ = BottomPositioningGrammarAction($1,$3); }
		| LEFT COLON OPEN_SQUARE_BRACKET elementList CLOSE_SQUARE_BRACKET { $$ = LeftPositioningGrammarAction($1,$3); }
		| RIGHT COLON OPEN_SQUARE_BRACKET elementList CLOSE_SQUARE_BRACKET { $$ = RightositioningGrammarAction($1,$3); }
		| TOP_RIGHT COLON OPEN_SQUARE_BRACKET elementList CLOSE_SQUARE_BRACKET { $$ = TopRightPositioningGrammarAction($1,$3); }
		| TOP_LEFT COLON OPEN_SQUARE_BRACKET elementList CLOSE_SQUARE_BRACKET { $$ = TopLeftPositioningGrammarAction($1,$3); }
		| BOTTOM_RIGHT COLON OPEN_SQUARE_BRACKET elementList CLOSE_SQUARE_BRACKET { $$ = BottomRightPositioningGrammarAction($1,$3); }
		| BOTTOM_LEFT COLON OPEN_SQUARE_BRACKET elementList CLOSE_SQUARE_BRACKET { $$ = BottomLeftPositioningGrammarAction($1,$3); }
		| CENTER COLON OPEN_SQUARE_BRACKET elementList CLOSE_SQUARE_BRACKET { $$ = CenterPositioningGrammarAction($1,$3); }
		| CENTER_BOTTOM COLON OPEN_SQUARE_BRACKET elementList CLOSE_SQUARE_BRACKET { $$ = CenterBottomPositioningGrammarAction($1,$3); }
		| CENTER_LEFT COLON OPEN_SQUARE_BRACKET elementList CLOSE_SQUARE_BRACKET { $$ = CenterLeftPositioningGrammarAction($1,$3); }
		| CENTER_RIGHT COLON OPEN_SQUARE_BRACKET elementList CLOSE_SQUARE_BRACKET { $$ = CenterRightPositioningGrammarAction($1,$3); }
		| CENTER_TOP COLON OPEN_SQUARE_BRACKET elementList CLOSE_SQUARE_BRACKET { $$ = CenterTopPositioningGrammarAction($1,$3); }
		| CHILDREN COLON OPEN_SQUARE_BRACKET elementList CLOSE_SQUARE_BRACKET { $$ = ChildrenPositioningGrammarAction($1,$3); }
		;

	script: SCRIPT COLON OPEN_CURLY_BRACKET CLOSE_CURLY_BRACKET { $$ = ScriptGrammarAction(); }
		;

	style: STYLE COLON OPEN_CURLY_BRACKET CLOSE_CURLY_BRACKET { $$ = StyleGrammarAction(); }
		;

	elementList: elementList COMMA element { $$ = MultipleElementListGrammarAction($1, $3); }
		| element { $$ = OneElementListGrammarAction($1, null); }
		;
	element: STRING { $$ = ElementGrammarAction($1); }
		| STRING OPEN_PARENTHESIS argumentList CLOSE_PARENTHESIS { $$ = ElementWithArgumentsGrammarAction($1, $3); }
		;
	argumentList: argument { $$ = SingleArgumentGrammarAction($1);}
		| argumentList COMMA argument { $$ = MultipleArgumentGrammarAction($1, $3); }
		;
	argument: STRING COLON STRING { $$ = StringArgumentGrammarAction($1, $3); }
		| STRING COLON INTEGER { $$ = IntegerArgumentGrammarAction($1, $3); }
		| STRING COLON FLOAT { $$ = FloatArgumentGrammarAction($1, $3); }
		| STRING COLON BOOLEAN { $$ = BooleanArgumentGrammarAction($1, $3); }
		| STRING COLON OPEN_PARENTHESIS expression CLOSE_PARENTHESIS { $$ = ConcatenatedArgumentGrammarAction($1, $4); }
		| STRING { $$ = OnlyStringArgumentGrammarAction($1); }
		| INTEGER { $$ = OnlyIntegerArgumentGrammarAction($1); }
		| FLOAT { $$ = OnlyFloatArgumentGrammarAction($1); }
		| BOOLEAN { $$ = OnlyBooleanArgumentGrammarAction($1); }
		;
%%