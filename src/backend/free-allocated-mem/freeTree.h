#ifndef FREE_TREE_H
#define FREE_TREE_H
#include "../support/shared.h"
#include <string.h>
#include <stdlib.h>

void freeTree(tModule *root);
void freeCanvas(tComponentAsCanvas *canvas);
void freeAllComponents(tComponentHeader *components);
void freeComponent(tComponent *component);
void freeDefinition(tDefinition *definition);
void freeTemplate(tTemplate *template);
void freeAllPositions(tPositionHeader *positions);
void freePosition(tPositionItem *position);
void freeToken(tPosToken *token);
void freeVariable(tVariable *variable);
void freeConstant(tConstant *constant);
void freeAllElements(tElementHeader *elements);
void freeElement(tElement *element);
void freeAllArguments(tArgumentHeader *arguments);
void freeArgument(tArgument *argument);

#endif