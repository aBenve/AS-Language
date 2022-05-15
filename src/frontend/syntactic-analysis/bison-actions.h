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

// Program.
tModule *ProgramModulesGrammarAction(tModule *module);

// Module.
tModule *CanvasModuleGrammarAction(tCanvas *canvas);
tModule *MultipleComponentModuleGrammarAction(tCanvas *canvas, tComponent **components);
tModule *ComponentAsCanvasModuleGrammarAction(tComponentAsCanvas *compAsCanvas);
tModule *MultipleComponentAsCanvasModuleGrammarAction(tComponentAsCanvas *compAsCanvas, tComponent **components);

// ComponentList.
tComponent **MultipleComponentListGrammarAction(tComponent **prevComponents, tComponent *component);
tComponent **SingleComponentListGrammarAction(tComponent *component);

// Component.
tComponent *ComponentGrammarAction(char *name, tDefinition *definition);
// ComponentAsCanvas.
tComponentAsCanvas *ComponentAsCanvasGrammarAction(char *name, tDefinition *definition);

// Canvas.
tCanvas *CanvasGrammarAction(tDefinition *definition);

// Definition.
tDefinition *TemplateDefinitionGrammarAction(tTemplate *template);
tDefinition *TemplateScriptDefinitionGrammarAction(tTemplate *template, tScript *script);
tDefinition *TemplateStyleDefinitionGrammarAction(tTemplate *template, tStyle *style);
tDefinition *TemplateScriptStyleDefinitionGrammarAction(tTemplate *template, tScript *script, tStyle *style);
tDefinition *TemplateStyleScriptDefinitionGrammarAction(tTemplate *template, tStyle *style, tScript *script);
// Template.
tTemplate *TemplateGrammarAction(tPosition *positions);
tTemplate *TemplateEmptyGrammarAction();
// positioning.
tPosition *SinglePositionItemGrammarAction(tPositionItem *element);
tPosition *MultiplePositioningGrammarAction(tPosition *prevItems, tPositionItem *value);

// positionItem.
tPositionItem *PositionItemElementListGrammarAction(int token, tElement **elementList);
tPositionItem *PositionItemVariableGrammarAction(int token, tVariable *variable);
tPositionItem *PositionItemConstantGrammarAction(int token, tConstant *constant);

// pItem

// Style.
tStyle *StyleGrammarAction(char *cssCode);

// Script.
tScript *ScriptGrammarAction(char *jsCode);

// ElementList.
tElement **MultipleElementListGrammarAction(tElement **elementList, tElement *element);
tElement **OneElementListGrammarAction(tElement *element);
// Element.
tElement *ElementGrammarAction(char *name);
tElement *ElementWithArgumentsGrammarAction(char *name, tArgument **arguments);

// Variable
tVariable *DollarVariableGrammarAction(char *name);
tVariable *PropVariableGrammarAction(char *name);

// Constant
tConstant *ConstantGrammarAction(char *value);
// ArgumentList.
tArgument **SingleArgumentGrammarAction(tArgument *value);
tArgument **MultipleArgumentGrammarAction(tArgument **prevArguments, tArgument *value);

// Argument.
tArgument *StringArgumentGrammarAction(char *name, char *value);
tArgument *IntegerArgumentGrammarAction(char *name, int value);
tArgument *FloatArgumentGrammarAction(char *name, float value);
tArgument *BooleanArgumentGrammarAction(char *name, boolean value);
tArgument *ConcatenatedArgumentGrammarAction(char *name, tArgument *value);
tArgument *OnlyStringArgumentGrammarAction(char *value);
tArgument *OnlyIntegerArgumentGrammarAction(int value);
tArgument *OnlyFloatArgumentGrammarAction(float value);
tArgument *OnlyBooleanArgumentGrammarAction(boolean value);

/*


void ProgramModulesGrammarAction();

// Module.
void CanvasModuleGrammarAction();
void MultipleComponentModuleGrammarAction();
void ComponentAsCanvasModuleGrammarAction();
void MultipleComponentAsCanvasModuleGrammarAction();

// ComponentList.
void MultipleComponentListGrammarAction();
void SingleComponentListGrammarAction();

// Component.
void ComponentGrammarAction();
// ComponentAsCanvas.
void ComponentAsCanvasGrammarAction();

// Canvas.
void CanvasGrammarAction();

// Definition.
void TemplateDefinitionGrammarAction();
void TemplateScriptDefinitionGrammarAction();
void TemplateStyleDefinitionGrammarAction();
void TemplateScriptStyleDefinitionGrammarAction();
void TemplateStyleScriptDefinitionGrammarAction();
// Template.
void TemplateGrammarAction();
void TemplateEmptyGrammarAction();
// positioning.
void SinglePositionItemGrammarAction();
void MultiplePositioningGrammarAction();

// positionItem.
void PositionItemElementListGrammarAction();
void PositionItemVariableGrammarAction();
void PositionItemConstantGrammarAction();

// pItem

// Style.
void StyleGrammarAction();

// Script.
void ScriptGrammarAction();

// ElementList.
void MultipleElementListGrammarAction();
void OneElementListGrammarAction();
// Element.
void ElementGrammarAction();
void ElementWithArgumentsGrammarAction();

// Variable

// ArgumentList.
void SingleArgumentGrammarAction();
void MultipleArgumentGrammarAction();

// Argument.
void StringArgumentGrammarAction();
void IntegerArgumentGrammarAction();
void FloatArgumentGrammarAction();
void BooleanArgumentGrammarAction();
void ConcatenatedArgumentGrammarAction();
void OnlyStringArgumentGrammarAction();
void OnlyIntegerArgumentGrammarAction();
void OnlyFloatArgumentGrammarAction();
void OnlyBooleanArgumentGrammarAction();
*/

#endif
