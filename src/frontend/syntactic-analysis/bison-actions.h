#ifndef BISON_ACTIONS_HEADER
#define BISON_ACTIONS_HEADER

#include "../../backend/support/shared.h"

/**
 * Se definen las acciones a ejecutar sobre cada regla de producción de la
 * gramática. El objetivo de cada acción debe ser el de construir el nodo
 * adecuado que almacene la información requerida en el árbol de sintaxis
 * abstracta (i.e., el AST).
 */

// -----------------------------------------------------------------------------

// Funciones para el backend.
/*

// Program.
tModule *ProgramModulesGrammarAction(tModule *module);

// Module.
tModule *CanvasModuleGrammarAction(tCanvas *canvas);
tModule *MultipleComponentModuleGrammarAction(tCanvas *canvas, tComponent **components);

tModule *ComponentAsCanvasModuleGrammarAction(tComponentAsCanvas *canvas);
tModule *MultipleComponentAsCancasModuleGrammarAction(tComponentAsCanvas *canvas, tComponent **components);

// ComponentList.
tComponent **MultipleComponentListGrammarAction(tComponent **prevComponents, tComponent *component);
tComponent **SingleComponentListGrammarAction(tComponent *component);

// Component.
tComponent *ComponentGrammarAction(char *name, tDefinition *definition);

// Canvas.
tCanvas *CanvasGrammarAction(tDefinition *definition);
tComponentAsCanvas *ComponentAsCanvasGrammarAction(char *name, tDefinition *definition);

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
tPositionItem *TopPositioningGrammarAction(const char *name, tElement *element);
tPositionItem *BottomPositioningGrammarAction(const char *name, tElement *element);
tPositionItem *LeftPositioningGrammarAction(const char *name, tElement *element);
tPositionItem *RightositioningGrammarAction(const char *name, tElement *element);
tPositionItem *TopRightPositioningGrammarAction(const char *name, tElement *element);
tPositionItem *TopLeftPositioningGrammarAction(const char *name, tElement *element);
tPositionItem *BottomRightPositioningGrammarAction(const char *name, tElement *element);
tPositionItem *BottomLeftPositioningGrammarAction(const char *name, tElement *element);
tPositionItem *CenterPositioningGrammarAction(const char *name, tElement *element);
tPositionItem *CenterBottomPositioningGrammarAction(const char *name, tElement *element);
tPositionItem *CenterLeftPositioningGrammarAction(const char *name, tElement *element);
tPositionItem *CenterRightPositioningGrammarAction(const char *name, tElement *element);
tPositionItem *CenterTopPositioningGrammarAction(const char *name, tElement *element);
tPositionItem *ChildrenPositioningGrammarAction(const char *name, tElement *element);

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


*/
#endif
