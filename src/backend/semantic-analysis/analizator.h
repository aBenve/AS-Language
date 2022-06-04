#ifndef ANALIZATOR_HEADER
#define ANALIZATOR_HEADER
#include "../support/shared.h"
#include <string.h>
#include <stdlib.h>
#include "../support/logger.h"

int hasStyleDef(tDefinition *def);
int hasScriptDef(tDefinition *def);

void Analice(tModule *root);

#endif