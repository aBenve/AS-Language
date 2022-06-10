#ifndef ANALIZATOR_HEADER
#define ANALIZATOR_HEADER
#include "../support/shared.h"
#include <string.h>
#include <stdlib.h>
#include "../support/logger.h"

#define INITIAL_VAR_TABLE_SIZE 5
#define INITIAL_CONCATENATED_STRING_SIZE 50

typedef struct tJsVariable
{
    char *name;
} tJsVariable;

typedef struct varTable
{
    char **elements;
    int used;
    int size;
} varTable;

// node struct for storing string tokens of script->content
typedef struct tScriptNode
{
    char *string;
    int isVariable;
    int isValue;
    char *value; // si es un valor, quiero guardarme el dato limpio, sin \n o ; pero sigo queriendo mantener el string para cuando debo volver a juntar todos los strings
    char *variable;
    struct tScriptNode *next;
    struct tScriptNode *prev;
} tScriptNode;

// tScriptNode head
typedef struct tScriptNodeHead
{
    tScriptNode *head;
} tScriptNodeHead;

int hasStyleDef(tDefinition *def);
int hasScriptDef(tDefinition *def);
int findByName(varTable *table, char *name, int size);
int findByVarInHTML(varTable *table, char *name, int size);
char *getUpdateFunction(char *varName, char *value);
tScriptNode *createTokensListRec(char *token, tScriptNode *prev);
tScriptNode *createTokensList(char *jsCode);
void freeTokensList(tScriptNode *node);
void freeTokenHead(tScriptNodeHead *head);
tScriptNodeHead *updateScriptCode(tScript *script);
varTable *createVarTable(tScript *script, tScriptNodeHead *tokensList);
int analiceTemplate(tTemplate *template, varTable *varTable);
void RepareCanvas(tModule *root);
void Analice(tModule *root);

#endif