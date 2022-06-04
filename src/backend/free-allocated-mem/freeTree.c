#include "freeTree.h"

void freeTree(tModule *root)
{
    if (root == NULL)
        return;

    freeCanvas(root->canvas);
    freeAllComponents(root->components);
    free(root);
}

void freeCanvas(tComponentAsCanvas *canvas)
{
    if (canvas == NULL)
        return;

    freeDefinition(canvas->definition);
    free(canvas);
}

void freeAllComponents(tComponentHeader *components)
{
    if (components == NULL)
        return;
    freeComponent(components->first);
    free(components);
}

void freeComponent(tComponent *component)
{
    if (component == NULL)
        return;
    if (component->next != NULL)
        freeComponent(component->next);
    if (component->name != NULL)
        free(component->name);
    freeDefinition(component->definition);
    free(component);
}

void freeDefinition(tDefinition *definition)
{
    if (definition == NULL)
        return;
    if (definition->style != NULL)
    {
        free(definition->style->content);
        free(definition->style);
    }
    if (definition->script != NULL)
    {
        free(definition->script->content);
        free(definition->style);
    }
    if (definition->template != NULL)
        freeTemplate(definition->template);
    free(definition);
}

void freeTemplate(tTemplate *template)
{
    if (template == NULL)
        return;
    freeAllPositions(template->positions);
    free(template);
}

void freeAllPositions(tPositionHeader *positions)
{
    if (positions == NULL)
        return;
    freePosition(positions->first);
    free(positions);
}

void freePosition(tPositionItem *position)
{
    if (position == NULL)
        return;
    if (position->next != NULL)
        freePosition(position->next);

    freeToken(position->posToken);
    if (position->variable != NULL)
        freeVariable(position->variable);
    if (position->constant != NULL)
        freeConstant(position->constant);
    if (position->elements != NULL)
        freeAllElements(position->elements);

    free(position);
}

void freeToken(tPosToken *token)
{
    if (token == NULL)
        return;
    free(token);
}

void freeVariable(tVariable *variable)
{
    if (variable == NULL)
        return;
    free(variable->name);
    free(variable->value);
    free(variable);
}

void freeConstant(tConstant *constant)
{
    if (constant == NULL)
        return;
    free(constant->value);
    free(constant);
}

void freeAllElements(tElementHeader *elements)
{
    if (elements == NULL)
        return;
    freeElement(elements->first);
    free(elements);
}

void freeElement(tElement *element)
{
    if (element == NULL)
        return;
    if (element->next != NULL)
        freeElement(element->next);

    free(element->name);
    if (element->arguments != NULL)
        freeAllArguments(element->arguments);
    free(element);
}

void freeAllArguments(tArgumentHeader *arguments)
{
    if (arguments == NULL)
        return;
    freeArgument(arguments->first);
    free(arguments);
}

void freeArgument(tArgument *argument)
{
    if (argument == NULL)
        return;
    if (argument->next != NULL)
        freeArgument(argument->next);

    free(argument->name);
    free(argument->value);
    free(argument);
}