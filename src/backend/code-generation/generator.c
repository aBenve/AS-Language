#include "generator.h"

/**
 * Implementación de "generator.h".
 */

void Generator(tModule *result)
{
	if (result == NULL)
	{
		LogInfo("El resultado de la compilacion es nulo.");
		return;
	}

	// LogInfo("%d", result->components->size);
	LogInfo("Generador de codigo...\n");

	int componentsAmount = result->components == NULL ? 0 : result->components->size;

	tComponentCode **componentsCode = NULL;
	tComponentCode *canvasCode = NULL;

	// primero el canvas que se que esta siempre
	LogInfo("\tGeneradando Canvas...");
	canvasCode = generateCanvas(result->canvas, result);
	// Puede ser que no haya ningun componente
	if (componentsAmount > 0)
	{
		LogInfo("\tGenerando Componentes...");
		componentsCode = generateComponents(result->components->first, componentsAmount);
	}

	LogInfo("\tGenerando codigo intermedio...\n");
	printf("<!DOCTYPE html>\n<html>\n<head>\n<title>Intermediate Code</title>\n");

	// css
	printf("<style>\n");
	printCanvasCss(canvasCode);
	printCss(componentsCode, componentsAmount);
	printf("</style>\n");

	printf("</head>\n");
	printf("<body>\n");

	// html
	printf("<div id=\"app\">\n");
	printCanvasHTML(canvasCode);
	printf("</div>\n");

	// Global js functions
	printf("<script>\n");
	printf("function updateView(variableName, value) {\n\tdocument.getElementById(variableName).innerHTML = value; \n}\n");
	printf("</script>\n");

	// js
	printf("<script>\n");
	printCanvasJs(canvasCode);
	printJs(componentsCode, componentsAmount);
	printf("</script>\n");

	printf("</body>\n");
	printf("</html>\n");

	// libero memoria
	for (int i = 0; i < componentsAmount; i++)
	{
		if (componentsCode[i]->script != NULL)
			free(componentsCode[i]->script);
		if (componentsCode[i]->style != NULL)
			free(componentsCode[i]->style);

		free(componentsCode[i]->html);
		free(componentsCode[i]);
	}
	free(componentsCode);

	if (canvasCode->script != NULL)
		free(canvasCode->script);
	if (canvasCode->style != NULL)
		free(canvasCode->style);
	free(canvasCode->html);
	free(canvasCode);
}
