%{

#include "bison-actions.h"

%}


%union{
	tComponent * component;
	tComponentHeader * componentList;
	tModule * modules;
	tComponentAsCanvas * componentAsCanvas;
	tDefinition * definition;
	tCanvas * canvas;
	tArgument * argument;
	tArgumentHeader * argumentList;
	tVariable * variable;
	tConstant * constant;
	tElement * element;
	tElementHeader * elementList;
	tPosToken * posToken;
	tPositionItem * positionItem;
	tPositionHeader * positioning;
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
%type <variable> variable
%type <constant> constant
%type <argumentList> argumentList
%type <argument> argument
%type <posToken> pItem
%type <string> componentName
%type <string> elementName
%type <string> variableName


%token <token> OPEN_PARENTHESIS
%token <token> CLOSE_PARENTHESIS
%token <token> OPEN_CURLY_BRACKET
%token <token> CLOSE_CURLY_BRACKET
%token <token> OPEN_SQUARE_BRACKET
%token <token> CLOSE_SQUARE_BRACKET

%token <token> COMMA
%token <token> COLON
%token <token> LINE_COMMENT
%token <token> DOLLAR
%token <token> DOT

%token <integer> INTEGER
%token <string> STRING
%token <floatNumber> FLOAT
%token <boolean> BOOLEAN
%token <string> TEXT

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
%token <token> PROPS
%token <token> AS
%token <token> CANVAS
%token <token> SCRIPT
%token <token> TEMPLATE
%token <token> STYLE
%token <string> CSS_CODE
%token <string> JS_CODE
%token <token> IMPORT


%%

	program: modules { state.succeed = true;  state.result = ProgramModulesGrammarAction($1);}
		;
	
	modules: canvas { $$ = CanvasModuleGrammarAction($1);  }
		| canvas componentList { $$ = MultipleComponentModuleGrammarAction($1, $2);  }
		| componentAsCanvas { $$ = ComponentAsCanvasModuleGrammarAction($1);   }
		| componentAsCanvas componentList { $$ = MultipleComponentAsCanvasModuleGrammarAction($1, $2);   }
		;

	componentList: componentList component { $$ = MultipleComponentListGrammarAction($1, $2);   }
		| component { $$ = SingleComponentListGrammarAction($1);  }
		;

	component: MODULE componentName OPEN_CURLY_BRACKET definition CLOSE_CURLY_BRACKET 	{ $$ = ComponentGrammarAction($2, $4);    }
		;

	componentAsCanvas:	MODULE componentName AS CANVAS OPEN_CURLY_BRACKET definition CLOSE_CURLY_BRACKET { $$ = ComponentAsCanvasGrammarAction($2, $6);   }
		;

	componentName: STRING { $$ = ComponentNameGrammarAction($1);  }
		;

	canvas: MODULE CANVAS OPEN_CURLY_BRACKET definition CLOSE_CURLY_BRACKET 	{ $$ = CanvasGrammarAction($4);   }
		;

	definition: template {  $$ = TemplateDefinitionGrammarAction($1);   }
		| template script {  $$ = TemplateScriptDefinitionGrammarAction($1, $2);  }
		| template style { $$ = TemplateStyleDefinitionGrammarAction($1, $2);  }
		| template script style { $$ = TemplateScriptStyleDefinitionGrammarAction($1, $2, $3);  }
		| template style script { $$ = TemplateStyleScriptDefinitionGrammarAction($1, $2, $3);  }
		;

	template: TEMPLATE COLON OPEN_CURLY_BRACKET positioning CLOSE_CURLY_BRACKET { $$ = TemplateGrammarAction($4);  }
		| TEMPLATE COLON OPEN_CURLY_BRACKET CLOSE_CURLY_BRACKET { $$ = TemplateEmptyGrammarAction();  }
		;

	positioning: positioning COMMA positionItem { $$ = MultiplePositioningGrammarAction($1, $3);  }
		| positionItem { $$ = SinglePositionItemGrammarAction($1);  }
		;

	/* ? Podria servir una positionItem que no tenga nada adentro*/

	positionItem: pItem COLON OPEN_SQUARE_BRACKET elementList CLOSE_SQUARE_BRACKET { $$ = PositionItemElementListGrammarAction($1, $4);  }
		| pItem COLON variable { $$ = PositionItemVariableGrammarAction($1, $3);  }
		| pItem COLON constant { $$ = PositionItemConstantGrammarAction($1, $3);  }
		;

	pItem: 	TOP_RIGHT { $$ = TopRightGrammarAction($1);  }
		| TOP_LEFT { $$ = TopLeftGrammarAction($1);  }
		| BOTTOM_RIGHT { $$ = BottomRightGrammarAction($1);  }
		| BOTTOM_LEFT { $$ = BottomLeftGrammarAction($1);  }
		| TOP_CENTER { $$ = TopCenterGrammarAction($1);  }
		| BOTTOM_CENTER { $$ = BottomCenterGrammarAction($1);  }
		| LEFT_CENTER { $$ = LeftCenterGrammarAction($1);  }
		| RIGHT_CENTER { $$ = RightCenterGrammarAction($1);  }
		| RIGHT { $$ = RightGrammarAction($1);  }
		| LEFT { $$ = LeftGrammarAction($1);  }
		| BOTTOM { $$ = BottomGrammarAction($1);  }
		| TOP { $$ = TopGrammarAction($1);  }
		| CENTER { $$ = CenterGrammarAction($1);  }
		| CHILDREN { $$ = ChildrenGrammarAction($1);  }
		;

	script: SCRIPT COLON JS_CODE  { $$ = ScriptGrammarAction($3);  }
		;

	style: STYLE COLON CSS_CODE  { $$ = StyleGrammarAction($3);  }
		;

	elementList: elementList COMMA element { $$ = MultipleElementListGrammarAction($1, $3);  }
		| element { $$ = OneElementListGrammarAction($1);  }
		;

	element: elementName { $$ = ElementGrammarAction($1);  }
		| elementName OPEN_PARENTHESIS argumentList CLOSE_PARENTHESIS { $$ = ElementWithArgumentsGrammarAction($1, $3);  }
		;

	elementName: STRING { $$ = ElementNameGrammarAction($1);  }
		;

	variable: DOLLAR OPEN_CURLY_BRACKET variableName CLOSE_CURLY_BRACKET { $$ = DollarVariableGrammarAction($3);  }
		| PROPS DOT variableName { $$ = PropVariableGrammarAction($3);  }
		;

	variableName: STRING { $$ = VariableNameGrammarAction($1);  }
		;

	constant: TEXT { $$ = ConstantGrammarAction($1);  }
		;

	argumentList: argument { $$ = SingleArgumentGrammarAction($1);  }
		| argumentList COMMA argument { $$ = MultipleArgumentGrammarAction($1, $3);  }
		;
	argument: STRING COLON STRING {$$ = StringArgumentGrammarAction($1, $3);	 }
		| STRING COLON INTEGER {$$ = IntegerArgumentGrammarAction($1, $3);   }
		| STRING COLON FLOAT { $$ = FloatArgumentGrammarAction($1, $3);  }
		| STRING COLON BOOLEAN { $$ = BooleanArgumentGrammarAction($1, $3);  }
		| STRING COLON OPEN_PARENTHESIS argument CLOSE_PARENTHESIS { $$ = ConcatenatedArgumentGrammarAction($1, $4);  }
		| STRING {  $$ = OnlyStringArgumentGrammarAction($1);  }
		| INTEGER {  $$ = OnlyIntegerArgumentGrammarAction($1);  }
		| FLOAT {  $$ = OnlyFloatArgumentGrammarAction($1);  }
		| BOOLEAN {  $$ = OnlyBooleanArgumentGrammarAction($1);  }
		;
%%