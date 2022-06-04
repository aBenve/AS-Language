#include "backend/code-generation/generator.h"
#include "backend/support/logger.h"
#include "backend/support/shared.h"
#include "frontend/syntactic-analysis/bison-actions.h"
#include "frontend/syntactic-analysis/bison-parser.h"
#include <stdio.h>
#include "backend/semantic-analysis/analizator.h"
#include "backend/free-allocated-mem/freeTree.h"
// Estado de la aplicación.
CompilerState state;

// Punto de entrada principal del compilador.
const int main(const int argumentCount, const char **arguments)
{
	// Inicializar estado de la aplicación.
	state.result = 0;
	state.succeed = false;

	// Mostrar parámetros recibidos por consola.
	for (int i = 0; i < argumentCount; ++i)
	{
		LogInfo("Argumento %d: '%s'", i, arguments[i]);
	}

	// Compilar el programa de entrada.
	LogInfo("Compilando...\n");

	// ! Valgrind me dice que yyparse() likea memoria.
	const int result = yyparse();
	switch (result)
	{
	case 0:
		if (state.succeed)
		{
			LogInfo("La compilacion fue exitosa. 😃😃😃 ");
			Analice(state.result);
			Generator(state.result);
		}
		else
		{
			LogError("Se produjo un error en la aplicacion.");
			return -1;
		}
		break;
	case 1:
		LogError("Bison finalizo debido a un error de sintaxis.");
		break;
	case 2:
		LogError("Bison finalizo abruptamente debido a que ya no hay memoria disponible.");
		break;
	default:
		LogError("Error desconocido mientras se ejecutaba el analizador Bison (codigo %d).", result);
	}
	LogInfo("Fin.");
	// no olvidar liberar memoria del arbol de sintaxis.
	freeTree(state.result);
	return result;
}
