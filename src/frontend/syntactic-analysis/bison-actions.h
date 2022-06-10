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
tModule *MultipleComponentModuleGrammarAction(tCanvas *canvas, tComponentHeader *components);
tModule *ComponentAsCanvasModuleGrammarAction(tComponentAsCanvas *compAsCanvas);
tModule *MultipleComponentAsCanvasModuleGrammarAction(tComponentAsCanvas *compAsCanvas, tComponentHeader *components);

// ComponentList.
tComponentHeader *MultipleComponentListGrammarAction(tComponentHeader *prevComponents, tComponent *component);
tComponentHeader *SingleComponentListGrammarAction(tComponent *component);

// Component.
tComponent *ComponentGrammarAction(char *name, tDefinition *definition);
// ComponentAsCanvas.
tComponentAsCanvas *ComponentAsCanvasGrammarAction(char *name, tDefinition *definition);
// ComponentName
char *ComponentNameGrammarAction(char *name);
// Canvas.
tCanvas *CanvasGrammarAction(tDefinition *definition);

// Definition.
tDefinition *TemplateDefinitionGrammarAction(tTemplate *template);
tDefinition *TemplateScriptDefinitionGrammarAction(tTemplate *template, tScript *script);
tDefinition *TemplateStyleDefinitionGrammarAction(tTemplate *template, tStyle *style);
tDefinition *TemplateScriptStyleDefinitionGrammarAction(tTemplate *template, tScript *script, tStyle *style);
tDefinition *TemplateStyleScriptDefinitionGrammarAction(tTemplate *template, tStyle *style, tScript *script);
// Template.
tTemplate *TemplateGrammarAction(tPositionHeader *positions);
tTemplate *TemplateEmptyGrammarAction();
// positioning.
tPositionHeader *SinglePositionItemGrammarAction(tPositionItem *element);
tPositionHeader *MultiplePositioningGrammarAction(tPositionHeader *prevItems, tPositionItem *value);

// positionItem.
tPositionItem *PositionItemElementListGrammarAction(tPosToken *token, tElementHeader *elementList);
tPositionItem *PositionItemVariableGrammarAction(tPosToken *token, tVariable *variable);
tPositionItem *PositionItemConstantGrammarAction(tPosToken *token, tConstant *constant);

// pItem
tPosToken *TopRightGrammarAction(int token);
tPosToken *TopLeftGrammarAction(int token);
tPosToken *BottomRightGrammarAction(int token);
tPosToken *BottomLeftGrammarAction(int token);
tPosToken *TopCenterGrammarAction(int token);
tPosToken *BottomCenterGrammarAction(int token);
tPosToken *RightCenterGrammarAction(int token);
tPosToken *LeftCenterGrammarAction(int token);
tPosToken *RightGrammarAction(int token);
tPosToken *LeftGrammarAction(int token);
tPosToken *BottomGrammarAction(int token);
tPosToken *TopGrammarAction(int token);
tPosToken *CenterGrammarAction(int token);
tPosToken *ChildrenGrammarAction(int token);

// Style.
tStyle *StyleGrammarAction(char *cssCode);

// Script.
tScript *ScriptGrammarAction(char *jsCode);

// ElementList.
tElementHeader *MultipleElementListGrammarAction(tElementHeader *elementList, tElement *element);
tElementHeader *OneElementListGrammarAction(tElement *element);
// Element.
tElement *ElementGrammarAction(char *name);
tElement *ElementWithArgumentsGrammarAction(char *name, tArgumentHeader *arguments);

// ElementName
char *ElementNameGrammarAction(char *name);

// Variable
tVariable *DollarVariableGrammarAction(char *name);
tVariable *PropVariableGrammarAction(char *name);

// VariableName
char *VariableNameGrammarAction(char *name);

// Constant
tConstant *ConstantGrammarAction(char *value);
// ArgumentList.
tArgumentHeader *SingleArgumentGrammarAction(tArgument *value);
tArgumentHeader *MultipleArgumentGrammarAction(tArgumentHeader *prevArguments, tArgument *value);

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
