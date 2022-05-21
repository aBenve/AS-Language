#include "generator.h"

#define HTML_INITIAL_SIZE 100

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

	int componentsAmount = result->components == NULL ? 0 : result->components->size;

	tComponentCode **componentsCode = malloc(sizeof(tComponentCode *) * componentsAmount);
	tComponentCode *canvasCode = malloc(sizeof(tComponentCode *));

	// primero el canvas que se que esta siempre
	canvasCode = generateCanvas(result->canvas);
	// Puede ser que no haya ningun componente
	componentsCode = result->components == NULL ? NULL : generateComponents(result->components->first, componentsAmount);

	LogInfo("Generando codigo intermedio...");
	printf("<!DOCTYPE html>\n<html>\n<head>\n<title>Intermediate Code</title>\n");

	// css
	printCanvasCss(canvasCode);
	printCss(componentsCode, componentsAmount);

	printf("</head>\n");
	printf("<body>\n");
	printf("<div id=\"app\">\n");
	// html
	printf("<script>\n");

	// js
	printCanvasJs(canvasCode);
	printJs(componentsCode, componentsAmount);

	printf("</script>\n");
	printf("</body>\n");
	printf("</html>\n");
}

/*
<!DOCTYPE html>
<html>
<body >

<h1 style="position:absolute;top:0px;right:0px;color:blue">My First Heading</h1>
<h1 style="position:absolute;top:0px;left:0px;color:blue">My First Heading</h1>

<h1 style="position:absolute;bottom:0px;right:0px;color:blue">My First Heading</h1>
<h1 style="position:absolute;bottom:0px;left:0px;color:blue">My First Heading</h1>

<h1 style="position:absolute;top:50%;right:0px;color:blue;transform:translate(0,-50%)">My First Heading</h1>
<h1 style="position:absolute;top:50%;left:0px;color:blue;transform:translate(0,-50%)">My First Heading</h1>

<h1 style="position:absolute;bottom:0px;right:50%;color:blue;background:red;width:50%;margin-right:-25%">My First Heading</h1>
<h1 style="position:absolute;top:0px;left:50%;color:blue;background:red;transform:translate(-50%,0)">My First Heading</h1>
<h1 style="position:absolute; top: 50%; right: 50%;
  transform: translate(50%,-50%);color:blue;
  background: black;">My First Heading</h1>

</body>
</html>

*/