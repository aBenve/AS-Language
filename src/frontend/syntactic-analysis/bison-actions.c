#include "../../backend/domain-specific/calculator.h"
#include "../../backend/support/logger.h"
#include "bison-actions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

// ! Funciones del backend.

// Program.
tModule *ProgramModulesGrammarAction(tModule *module)
{
	// LogDebug("ProgramModulesGrammarAction: '%s'.", module->canvas->name == NULL ? "Canvas" : module->canvas->name);
	return module;
}

// Module.
tModule *CanvasModuleGrammarAction(tCanvas *canvas)
{
	LogDebug("CanvasModuleGrammarAction: Canvas.");
	tModule *module = (tModule *)malloc(sizeof(tModule));
	tComponentAsCanvas *compAsCanvas = (tComponentAsCanvas *)malloc(sizeof(tComponentAsCanvas));
	compAsCanvas->name = NULL;
	compAsCanvas->definition = canvas->definition;
	module->canvas = compAsCanvas;
	return module;
}
tModule *MultipleComponentModuleGrammarAction(tCanvas *canvas, tComponent **components)
{
	LogDebug("MultipleComponentModuleGrammarAction: ", "Canvas");
	tModule *module = malloc(sizeof(tModule));
	tComponentAsCanvas *compAsCanvas = (tComponentAsCanvas *)malloc(sizeof(tComponentAsCanvas));
	compAsCanvas->name = NULL;
	compAsCanvas->definition = canvas->definition;
	module->canvas = compAsCanvas;
	module->components = components;
	return module;
}
tModule *ComponentAsCanvasModuleGrammarAction(tComponentAsCanvas *compAsCanvas)
{
	LogDebug("MultipleComponentModuleGrammarAction: '%s'.", compAsCanvas->name);
	tModule *module = malloc(sizeof(tModule));
	module->canvas = compAsCanvas;
	return module;
}
tModule *MultipleComponentAsCancasModuleGrammarAction(tComponentAsCanvas *compAsCanvas, tComponent **components)
{
	LogDebug("CanvasModuleGrammarAction: Canvas.");
	tModule *module = (tModule *)malloc(sizeof(tModule));
	module->canvas = compAsCanvas;
	module->components = components;

	return module;
}
// ComponentList.
tComponent **MultipleComponentListGrammarAction(tComponent **prevComponents, tComponent *component)
{
	LogDebug("MultipleComponentListGrammarAction: '%s'.", component->name);
	// No importa si no esta bien ahora.
	tComponent **components = malloc(sizeof(tComponent) * ((sizeof(prevComponents) / sizeof(tComponent *)) + 1));
	memcpy(components, prevComponents, sizeof(prevComponents));
	components[(sizeof(prevComponents) / sizeof(tComponent *))] = component;
	return components;
}
tComponent **SingleComponentListGrammarAction(tComponent *component)
{
	LogDebug("SingleComponentListGrammarAction: '%s'.", component->name);
	tComponent **components = malloc(sizeof(tComponent *));
	return components;
}

// Component.
tComponent *ComponentGrammarAction(char *name, tDefinition *definition)
{
	LogDebug("ComponentGrammarAction: '%s'.", name);
	tComponent *component = malloc(sizeof(tComponent));
	component->name = name;
	component->definition = definition;
	return component;
}

// Canvas.
tCanvas *CanvasGrammarAction(tDefinition *definition)
{
	LogDebug("CanvasGrammarAction: '%s, %s, %s'.", definition->template == NULL ? "Template" : "No Template", definition->style == NULL ? "Style" : "No Style", definition->script == NULL ? "Script" : "No Script");
	tCanvas *canvas = malloc(sizeof(tCanvas));
	canvas->definition = definition;
	return canvas;
}

// ComponentAsCanvas.
tComponentAsCanvas *ComponentAsCanvasGrammarAction(char *name, tDefinition *definition)
{
	LogDebug("ComponentAsCanvasGrammarAction: '%s'.", name);
	tComponentAsCanvas *componentAsCanvas = malloc(sizeof(tComponentAsCanvas));
	componentAsCanvas->name = name;
	componentAsCanvas->definition = definition;
	return componentAsCanvas;
}

// Definition.
tDefinition *TemplateDefinitionGrammarAction(tTemplate *template);
tDefinition *TemplateScriptDefinitionGrammarAction(tTemplate *template, tScript *script);
tDefinition *TemplateStyleDefinitionGrammarAction(tTemplate *template, tStyle *style);
tDefinition *TemplateScriptStyleDefinitionGrammarAction(tTemplate *template, tScript *script, tStyle *style);
tDefinition *TemplateStyleScriptDefinitionGrammarAction(tTemplate *template, tStyle *style, tScript *script);
// Template.
tTemplate *TemplateGrammarAction(tPositionItem *positions);
// positioning.
tPositionItem *SinglePositionItemGrammarAction(tPositionItem *element);
tPositionItem **MultiplePositioningGrammarAction(tPositionItem **prevItems, tPositionItem *value);

// positionItem.
tPositionItem *PositionItemElementListGrammarAction(const char *name, tElement **elementList);
tPositionItem *PositionItemVariableGrammarAction(const char *name, tVariable *variable);
tPositionItem *PositionItemConstantGrammarAction(const char *name, tConstant *constant);

// Style.
void StyleGrammarAction();

// Script.
void ScriptGrammarAction();

// ElementList.
tElement **MultipleElementListGrammarAction(tElement **elementList, tElement *element);
tElement *OneElementListGrammarAction(tElement *element);
// Element.
tElement *ElementGrammarAction(const char *name);
tElement *ElementWithArgumentsGrammarAction(const char *name, tArgument **arguments);

// ArgumentList.
tArgument *SingleArgumentGrammarAction(tArgument *value);
tArgument **MultipleArgumentGrammarAction(tArgument **prevArguments, tArgument *value);

// Argument.
tArgument *StringArgumentGrammarAction(const char *name, const char *value);
tArgument *IntegerArgumentGrammarAction(const char *name, const int value);
tArgument *FloatArgumentGrammarAction(const char *name, const float value);
tArgument *BooleanArgumentGrammarAction(const char *name, const boolean value);
tArgument *ConcatenatedArgumentGrammarAction(const char *name, tArgument *value);
tArgument *OnlyStringArgumentGrammarAction(const char *value);
tArgument *OnlyIntegerArgumentGrammarAction(const int value);
tArgument *OnlyFloatArgumentGrammarAction(const float value);
tArgument *OnlyBooleanArgumentGrammarAction(const boolean value);
