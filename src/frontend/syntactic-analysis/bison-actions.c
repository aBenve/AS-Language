#include "../../backend/domain-specific/calculator.h"
#include "../../backend/support/logger.h"
#include "bison-actions.h"
#include <stdio.h>
#include <string.h>

/**
 * Implementación de "bison-grammar.h".
 */

void yyerror(const char *string)
{
	LogError("Mensaje: '%s' debido a '%s' (linea %d).", string, yytext, yylineno);
	LogError("En ASCII es:");
	LogErrorRaw("\t");
	const int length = strlen(yytext);
	for (int i = 0; i < length; ++i)
	{
		LogErrorRaw("[%d]", yytext[i]);
	}
	LogErrorRaw("\n\n");
}
// Program.
tModule ProgramModulesGrammarAction(tModule module);

// Module.
tModule CanvasModuleGrammarAction(tCanvas canvas);
tModule MultipleComponentModuleGrammarAction(tCanvas canvas, tComponent component);

// ComponentList.
tComponent *MultipleComponentListGrammarAction(tComponent *prevComponents, tComponent component);
tComponent SingleComponentListGrammarAction(tComponent component);

// Component.
tComponent ComponentGrammarAction(char *name, tDefinition definition);

// Canvas.
tCanvas CanvasGrammarAction(tDefinition definition);
tComponentAsCanvas ComponentAsCanvasGrammarAction(const char *name, tDefinition definition);

// Definition.
tDefinition TemplateDefinitionGrammarAction(tTemplate *template);
tDefinition TemplateScriptDefinitionGrammarAction(tTemplate *template, tScript *script);
tDefinition TemplateStyleDefinitionGrammarAction(tTemplate *template, tStyle *style);
tDefinition TemplateScriptStyleDefinitionGrammarAction(tTemplate *template, tScript *script, tStyle *style);
// Template.
tTemplate TemplateGrammarAction(tPositionItem *positions);
// positioning.
tPositionItem SinglePositionItemGrammarAction(tPositionItem element);
tPositionItem *MultiplePositioningGrammarAction(tPositionItem *prevItems, tPositionItem value);

// positionItem.
tPositionItem TopPositioningGrammarAction(const char *name, tElement *element);
tPositionItem BottomPositioningGrammarAction(const char *name, tElement *element);
tPositionItem LeftPositioningGrammarAction(const char *name, tElement *element);
tPositionItem RightositioningGrammarAction(const char *name, tElement *element);
tPositionItem TopRightPositioningGrammarAction(const char *name, tElement *element);
tPositionItem TopLeftPositioningGrammarAction(const char *name, tElement *element);
tPositionItem BottomRightPositioningGrammarAction(const char *name, tElement *element);
tPositionItem BottomLeftPositioningGrammarAction(const char *name, tElement *element);
tPositionItem CenterPositioningGrammarAction(const char *name, tElement *element);
tPositionItem CenterBottomPositioningGrammarAction(const char *name, tElement *element);
tPositionItem CenterLeftPositioningGrammarAction(const char *name, tElement *element);
tPositionItem CenterRightPositioningGrammarAction(const char *name, tElement *element);
tPositionItem CenterTopPositioningGrammarAction(const char *name, tElement *element);
tPositionItem ChildrenPositioningGrammarAction(const char *name, tElement *element);

// Style.
void StyleGrammarAction();

// Script.
void ScriptGrammarAction();

// ElementList.
tElement *MultipleElementListGrammarAction(tElement **elementList, tElement *element);
tElement OneElementListGrammarAction(tElement *element);
// Element.
tElement ElementGrammarAction(const char *name);
tElement ElementWithArgumentsGrammarAction(const char *name, const tArgument **arguments);

// ArgumentList.
tArgument SingleArgumentGrammarAction(const tArgument *value);
tArgument *MultipleArgumentGrammarAction(const tArgument **prevArguments, const tArgument *value);

// Argument.
tArgument StringArgumentGrammarAction(const char *name, const char *value);
tArgument IntegerArgumentGrammarAction(const char *name, const int value);
tArgument FloatArgumentGrammarAction(const char *name, const float value);
tArgument BooleanArgumentGrammarAction(const char *name, const boolean value);
tArgument ConcatenatedArgumentGrammarAction(const char *name, const tArgument *value);
tArgument OnlyStringArgumentGrammarAction(const char *value);
tArgument OnlyIntegerArgumentGrammarAction(const int value);
tArgument OnlyFloatArgumentGrammarAction(const float value);
tArgument OnlyBooleanArgumentGrammarAction(const boolean value);
#endif