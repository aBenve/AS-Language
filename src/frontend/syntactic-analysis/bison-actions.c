#include "../../backend/domain-specific/calculator.h"
#include "../../backend/support/logger.h"
#include "bison-actions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define VARIABLE_TYPE_DOLLAR 0
#define VARIABLE_TYPE_PROP 1
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
	// LogInfo("ProgramModulesGrammarAction: '%s'.", module->canvas->name == NULL ? "Canvas" : module->canvas->name);
	return module;
}

// Module.
tModule *CanvasModuleGrammarAction(tCanvas *canvas)
{
	LogInfo("CanvasModuleGrammarAction: Canvas.");
	tModule *module = (tModule *)malloc(sizeof(tModule));
	tComponentAsCanvas *compAsCanvas = (tComponentAsCanvas *)malloc(sizeof(tComponentAsCanvas));
	compAsCanvas->name = NULL;
	compAsCanvas->definition = canvas->definition;
	module->canvas = compAsCanvas;
	return module;
}
tModule *MultipleComponentModuleGrammarAction(tCanvas *canvas, tComponent **components)
{
	LogInfo("MultipleComponentModuleGrammarAction: ", "Canvas");
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
	LogInfo("MultipleComponentModuleGrammarAction: '%s'.", compAsCanvas->name);
	tModule *module = malloc(sizeof(tModule));
	module->canvas = compAsCanvas;
	return module;
}
tModule *MultipleComponentAsCanvasModuleGrammarAction(tComponentAsCanvas *compAsCanvas, tComponent **components)
{
	LogInfo("CanvasModuleGrammarAction: Canvas.");
	tModule *module = (tModule *)malloc(sizeof(tModule));
	module->canvas = compAsCanvas;
	module->components = components;

	return module;
}
// ComponentList.
tComponent **MultipleComponentListGrammarAction(tComponent **prevComponents, tComponent *component)
{
	LogInfo("MultipleComponentListGrammarAction: '%s'.", component->name);
	// No importa si no esta bien ahora.
	tComponent **components = malloc(sizeof(tComponent) * ((sizeof(prevComponents) / sizeof(tComponent *)) + 1));
	memcpy(components, prevComponents, sizeof(prevComponents));
	components[(sizeof(prevComponents) / sizeof(tComponent *))] = component;
	return components;
}
tComponent **SingleComponentListGrammarAction(tComponent *component)
{
	LogInfo("SingleComponentListGrammarAction: '%s'.", component->name);
	tComponent **components = malloc(sizeof(tComponent *));
	return components;
}

// Component.
tComponent *ComponentGrammarAction(char *name, tDefinition *definition)
{
	LogInfo("ComponentGrammarAction: '%s'.", name);
	tComponent *component = malloc(sizeof(tComponent));
	component->name = name;
	component->definition = definition;
	return component;
}

// Canvas.
tCanvas *CanvasGrammarAction(tDefinition *definition)
{
	LogInfo("CanvasGrammarAction: '%s, %s, %s'.", definition->template == NULL ? "Template" : "No Template", definition->style == NULL ? "Style" : "No Style", definition->script == NULL ? "Script" : "No Script");
	tCanvas *canvas = malloc(sizeof(tCanvas));
	canvas->definition = definition;
	return canvas;
}

// ComponentAsCanvas.
tComponentAsCanvas *ComponentAsCanvasGrammarAction(char *name, tDefinition *definition)
{
	LogInfo("ComponentAsCanvasGrammarAction: '%s'.", name);
	tComponentAsCanvas *componentAsCanvas = malloc(sizeof(tComponentAsCanvas));
	componentAsCanvas->name = name;
	componentAsCanvas->definition = definition;
	return componentAsCanvas;
}

// Definition.
tDefinition *TemplateDefinitionGrammarAction(tTemplate *template)
{
	LogInfo("TemplateDefinitionGrammarAction: '%s'.", "template");
	tDefinition *definition = malloc(sizeof(tDefinition));
	definition->template = template;
	definition->style = NULL;
	definition->script = NULL;
	return definition;
}
tDefinition *TemplateScriptDefinitionGrammarAction(tTemplate *template, tScript *script)
{
	LogInfo("TemplateDefinitionGrammarAction: '%s'.", "template + script");
	tDefinition *definition = malloc(sizeof(tDefinition));
	definition->template = template;
	definition->style = NULL;
	definition->script = script;
	return definition;
}
tDefinition *TemplateStyleDefinitionGrammarAction(tTemplate *template, tStyle *style)
{
	LogInfo("TemplateDefinitionGrammarAction: '%s'.", "template + style");
	tDefinition *definition = malloc(sizeof(tDefinition));
	definition->template = template;
	definition->style = style;
	definition->script = NULL;
	return definition;
}
tDefinition *TemplateScriptStyleDefinitionGrammarAction(tTemplate *template, tScript *script, tStyle *style)
{
	LogInfo("TemplateDefinitionGrammarAction: '%s'.", "template + script + style");
	tDefinition *definition = malloc(sizeof(tDefinition));
	definition->template = template;
	definition->style = style;
	definition->script = script;
	return definition;
}
tDefinition *TemplateStyleScriptDefinitionGrammarAction(tTemplate *template, tStyle *style, tScript *script)
{
	return TemplateScriptStyleDefinitionGrammarAction(template, script, style);
}
// Template.
tTemplate *TemplateGrammarAction(tPosition *positions)
{
	LogInfo("TemplateGrammarAction: '%s'.", "template");
	tTemplate *template = malloc(sizeof(tTemplate));
	template->positions = positions;
	return template;
}
tTemplate *TemplateEmptyGrammarAction()
{
	LogInfo("TemplateGrammarAction: '%s'.", "empty template");
	tTemplate *template = malloc(sizeof(tTemplate));
	template->positions = NULL;
	return template;
}

// positioning.
tPosition *SinglePositionItemGrammarAction(tPositionItem *positionItem)
{
	LogInfo("SinglePositionItemGrammarAction: '%s'.", "single position item");
	tPosition *position = malloc(sizeof(tPosition));
	position->items = malloc(sizeof(tPositionItem *));
	position->items[0] = positionItem;
	return position;
}
tPosition *MultiplePositioningGrammarAction(tPosition *prevItems, tPositionItem *newPos)
{
	LogInfo("MultiplePositioningGrammarAction: '%s'.", "multiple position items");
	tPosition *position = malloc(sizeof(tPosition));
	position->items = malloc(sizeof(tPositionItem) * ((sizeof(prevItems->items) / sizeof(tPositionItem)) + 1));
	memcpy(position->items, prevItems->items, sizeof(prevItems->items));
	position->items[(sizeof(prevItems->items) / sizeof(tPositionItem))] = newPos;
	return position;
}

// positionItem.
tPositionItem *PositionItemElementListGrammarAction(int token, tElement **elementList)
{
	LogInfo("PositionItemElementListGrammarAction: '%s'.", token);
	tPositionItem *positionItem = malloc(sizeof(tPositionItem));
	positionItem->posToken = token;
	positionItem->elements = elementList;
	positionItem->variable = NULL;
	positionItem->constant = NULL;
	return positionItem;
}
tPositionItem *PositionItemVariableGrammarAction(int token, tVariable *variable)
{
	LogInfo("PositionItemVariableGrammarAction: '%s'.", token);
	tPositionItem *positionItem = malloc(sizeof(tPositionItem));
	positionItem->posToken = token;
	positionItem->elements = NULL;
	positionItem->variable = variable;
	positionItem->constant = NULL;
	return positionItem;
}
tPositionItem *PositionItemConstantGrammarAction(int token, tConstant *constant)
{
	LogInfo("PositionItemConstantGrammarAction: '%s'.", token);
	tPositionItem *positionItem = malloc(sizeof(tPositionItem));
	positionItem->posToken = token;
	positionItem->elements = NULL;
	positionItem->variable = NULL;
	positionItem->constant = constant;
	return positionItem;
}

// Style.
tStyle *StyleGrammarAction(char *cssCode)
{
	LogInfo("StyleGrammarAction: '%s'.", cssCode);
	tStyle *style = malloc(sizeof(tStyle));
	style->content = cssCode;
	return style;
}

// Script.
tScript *ScriptGrammarAction(char *jsCode)
{
	LogInfo("ScriptGrammarAction: '%s'.", jsCode);
	tScript *script = malloc(sizeof(tScript));
	script->content = jsCode;
	return script;
}

// ElementList.
tElement **MultipleElementListGrammarAction(tElement **elementList, tElement *element)
{
	LogInfo("MultipleElementListGrammarAction: '%s'.", "multiple element list");
	tElement **newElementList = malloc(sizeof(tElement) * ((sizeof(elementList) / sizeof(tElement)) + 1));
	memcpy(newElementList, elementList, sizeof(elementList));
	newElementList[(sizeof(elementList) / sizeof(tElement))] = element;
	return newElementList;
}
tElement **OneElementListGrammarAction(tElement *element)
{
	LogInfo("OneElementListGrammarAction: '%s'.", "one element list");
	tElement **elementList = malloc(sizeof(tElement));
	elementList[0] = element;
	return elementList;
}
// Element.
tElement *ElementGrammarAction(char *name)
{
	LogInfo("ElementGrammarAction: '%s'.", name);
	tElement *element = malloc(sizeof(tElement));
	element->name = name;
	element->arguments = NULL;
	return element;
}
tElement *ElementWithArgumentsGrammarAction(char *name, tArgument **arguments)
{
	LogInfo("ElementWithArgumentsGrammarAction: '%s'.", name);
	tElement *element = malloc(sizeof(tElement));
	element->name = name;
	element->arguments = arguments;
	return element;
}

// Variable
tVariable *DollarVariableGrammarAction(char *name)
{
	LogInfo("DollarVariableGrammarAction: '%s'.", name);
	tVariable *variable = malloc(sizeof(tVariable));
	variable->name = name;
	variable->type = VARIABLE_TYPE_DOLLAR;
	return variable;
}
tVariable *PropVariableGrammarAction(char *name)
{
	LogInfo("PropVariableGrammarAction: '%s'.", name);
	tVariable *variable = malloc(sizeof(tVariable));
	variable->name = name;
	variable->type = VARIABLE_TYPE_PROP;
	return variable;
}

// Constant
tConstant *ConstantGrammarAction(char *value)
{
	LogInfo("ConstantGrammarAction: '%s'.", value);
	tConstant *constant = malloc(sizeof(tConstant));
	constant->value = value;
	return constant;
}

// ArgumentList.
tArgument **SingleArgumentGrammarAction(tArgument *value)
{
	LogInfo("SingleArgumentGrammarAction: '%s'.", "single argument");
	tArgument **arguments = malloc(sizeof(tArgument));
	arguments[0] = value;
	return arguments;
}
tArgument **MultipleArgumentGrammarAction(tArgument **prevArguments, tArgument *value)
{
	LogInfo("MultipleArgumentGrammarAction: '%s'.", "multiple arguments");
	tArgument **arguments = malloc(sizeof(tArgument) * ((sizeof(prevArguments) / sizeof(tArgument)) + 1));
	memcpy(arguments, prevArguments, sizeof(prevArguments));
	arguments[(sizeof(prevArguments) / sizeof(tArgument))] = value;
	return arguments;
}

// Argument.
tArgument *StringArgumentGrammarAction(char *name, char *value)
{
	LogInfo("StringArgumentGrammarAction: '%s'.", name);
	tArgument *argument = malloc(sizeof(tArgument));
	argument->name = name;
	argument->value = value;
	return argument;
}
tArgument *IntegerArgumentGrammarAction(char *name, int value)
{
	LogInfo("IntegerArgumentGrammarAction: '%s'.", name);
	tArgument *argument = malloc(sizeof(tArgument));
	argument->name = name;
	argument->value = malloc(sizeof(int));
	// argument->value = (void *)value;
	*((int *)argument->value) = value;
	return argument;
}
tArgument *FloatArgumentGrammarAction(char *name, float value)
{
	LogInfo("FloatArgumentGrammarAction: '%s'.", name);
	tArgument *argument = malloc(sizeof(tArgument));
	argument->name = name;
	argument->value = malloc(sizeof(float));
	*(float *)argument->value = value;
	return argument;
}
tArgument *BooleanArgumentGrammarAction(char *name, boolean value)
{
	LogInfo("BooleanArgumentGrammarAction: '%s'.", name);
	tArgument *argument = malloc(sizeof(tArgument));
	argument->name = name;
	argument->value = malloc(sizeof(boolean));
	*(boolean *)argument->value = value;
	return argument;
}
tArgument *ConcatenatedArgumentGrammarAction(char *name, tArgument *value)
{
	LogInfo("ConcatenatedArgumentGrammarAction: '%s'.", name);
	tArgument *argument = malloc(sizeof(tArgument));
	argument->name = name;
	argument->value = value;
	return argument;
}
tArgument *OnlyStringArgumentGrammarAction(char *value)
{
	LogInfo("OnlyStringArgumentGrammarAction: '%s'.", value);
	tArgument *argument = malloc(sizeof(tArgument));
	argument->name = NULL;
	argument->value = value;
	return argument;
}
tArgument *OnlyIntegerArgumentGrammarAction(int value)
{
	LogInfo("OnlyIntegerArgumentGrammarAction: '%d'.", value);
	tArgument *argument = malloc(sizeof(tArgument));
	argument->name = NULL;
	argument->value = malloc(sizeof(int));
	*(int *)argument->value = value;
	return argument;
}
tArgument *OnlyFloatArgumentGrammarAction(float value)
{
	LogInfo("OnlyFloatArgumentGrammarAction: '%f'.", value);
	tArgument *argument = malloc(sizeof(tArgument));
	argument->name = NULL;
	argument->value = malloc(sizeof(float));
	*(float *)argument->value = value;
	return argument;
}
tArgument *OnlyBooleanArgumentGrammarAction(boolean value)
{
	LogInfo("OnlyBooleanArgumentGrammarAction: '%d'.", value);
	tArgument *argument = malloc(sizeof(tArgument));
	argument->name = NULL;
	argument->value = malloc(sizeof(boolean));
	*(boolean *)argument->value = value;
	return argument;
}
