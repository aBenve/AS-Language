<!-- omit in toc -->

<!-- esta imagen es solo de prueba -->
<img src="/res/linux.svg" alt="logo" style="float: left; vertical-align:baseline" width="100"/>
<!-- omit in toc -->

# AS Language

---

<!-- omit in toc --> 
# Tabla de contenidos

- [Introducción](#introducción)
- [Consideraciones adicionales](#consideraciones-adicionales)
- [El lenguaje](#el-lenguaje)
- [Desarrollo](#desarrollo)
- [Dificultades encontradas](#dificultades-encontradas)
- [Posibilidades de expansión](#posibilidades-de-expansión)
- [Bibliografía](#bibliografía)

---

## Introducción

<!-- Introducción con idea subyacente y objetivos del lenguaje. -->

*AS* es un lenguaje pensado para el prototipado de interfaces de aplicaciones web y móviles. Con él se pueden diseñar de forma rápida y sencilla prototipos web funcionales, que pueden luego ejecutarse en cualquier navegador. Esto es debido a que al compilar el lenguaje AS se obtiene como resultado código equivalente en HTML, Javascript y CSS para ejecutar en cualquier dispositivo. Además, si bien ofrece propiedades básicas de estilo para un diseñado rápido, este lenguaje no limita las posibilidades de diseño de los prototipos ya que incluye la capacidad de agregar código CSS para extender las propiedades y elementos ya creados.

## Consideraciones adicionales

<!-- Consideraciones adicionales no previstas en este enunciado que afecten a la implementación del lenguaje. -->
1. Por cuestiones de simplificacion de algunas cuestiones, todos los elementos renderizados en el HTML final estarán envueltos en ```<div>``` salvo cuando se usan variables de js donde las mismas se ubican en ```<span>```.
2. Nuevamente por simplifacion, toda variable definida en js que luego se pretenda mostrar en el HTML deberá comenzar con '__' (ej __NombreVariable)
3. Máximo cuidado con dejar espacios demás, especialmente en la sentencia **Script**
4. Actualmente las variables de js a mostrar en el HTML solo pueden ser strings.
5. El concepto de 'props' no fue implementado aunque si esta preparado su tokenizacion y permitido en la gramática.

## El lenguaje

<!-- Descripción de la gramática/sintaxis del lenguaje diseñado. -->
Sintacticamente *AS* esta pensado para que sea algo de rapida aplicacion pero sin tener que aprender todo desde 0 para poder tener algo funcionando. 
```Groovy
module Canvas {
    Template: {
        rightCenter:"Hey! Hola",
    }

    ~ Esto es un comentario :) ~

    Style: css{
		.canvas{
			background: red;
		}
    }css
    
    Script:js{
        console.log("soy el canvas!"); 
    }js
}
```
Con este simple ejemplo vemos el uso y ubicación de los estilos, comportamiento lógico y posiciones en el espacio.
Dentro del Template el usuario debe ubicar en que posición dentro del elemento se quiere ubicar y luego dar un valor. Este valor puede ser:

1. Otro elemento declarado debajo.
2. Una variable de js. Importante saber que esta debe estar declarada en la sentencia Script de el elemento en donde se usa.
3. Una constante. 

Por otro lado, La sentencia **Template** debe estar siempre declarada para todos los módulos que el usuario cree al inicio del mismo. Las otras sentencias de estilo o lógica no son necesarias y pueden aparecer de a una, juntas y en el orden que se prefiera.
Finalmente, para un mejor entendimiendo de la sentencia **Style**, recordar que todo elemento que se muestre en el HTML tendra una clase con el nombre del componente desde donde se creo. En el ejemplo:
```html
<div class="Canvas" id="Canvas-0">"Hey! Hola"</div>
```

## Desarrollo

<!-- Descripción del desarrollo del proyecto y de las fases del compilador. -->
1. **Flex**: matcheo de reglas y obtención de tokens.
2. **Bison**: chequeo de que la entrada cumpla la gramatica del lenguaje y creacion del AST(arbol de sintaxis)
3. **Analicer**: creación de tablas de variables para aquellos componentes con sentencia **Script** y chequeo de que todas las variables de js usadas en el HTML estén definidas en el mismo, y reparación del código de js donde para cada asignación de variable usada en el HTML se coloca una linea respectiva a la actualización de la misma.
4. **Generator**: generación del código final. 

## Dificultades encontradas

<!-- Dificultades a la hora de desarrollar el proyecto o alguna de sus partes (incluso problemas al concebir la idea original). -->
La mayor cantidad de dificultades se vieron relacionadas con la poca experiencia en esta rama de la programación y mas que nada con estas tecnologías, tanto Flex como Bison.
Con Flex nos llevamos la mayoría de los disgustos ya que el regex con el que trabaja no es trivial, es una version que no soporta ciertas características que intenta reemplazar con otras propias y la adaptación y entendimiento de las mismas conllevo bastante tiempo.
Por otro lado, Bison tiene sus cosas también. El mayor problema lo tuvimos con malos matcheos de nombres de variables o componentes, donde flex matcheba bien el nombre pero Bison agregaba un carácter mas al final. 
Finalmente ambas tecnologías en conjunto generaron varios dolores de cabeza hasta el punto de tener el union funcionando con la gramática correctamente seteada.
## Posibilidades de expansión

<!-- Futuras extensiones y/o modificaciones, indicando brevemente la complejidad de cada
una. -->
#### Biblioteca de funciones js
En el futuro seria de gran impacto la implementacion de diferentes ayudas al usuario a una mejor experiencia de uso al programar en este lenguaje, como una biblioteca de funciones especiales de js que el usuario pueda llamar desde el código. 


#### Soporte a mayor cantidad de tipos de datos
Seria ideal el soporte a mas estructuras de datos que si soporta js como listas u objetos. La posibilidad de armar una lista y enviarla directamente al HTML o de tener objetos y poder mostrar ciertas areas del mismo seria una gran ayuda al usuario.

## Bibliografía
1. Flex & Bison (https://web.iitd.ac.in/~sumeet/flex__bison.pdf)
2. Writing Your Own Toy Compiler Using Flex, Bison and LLVM (https://gnuu.org/2009/09/18/writing-your-own-toy-compiler/)
3. Flex regex (https://people.cs.aau.dk/~marius/sw/flex/Flex-Regular-Expressions.html)


<!-- Referencias y bibliografía. La diferencia entre referencia y bibliografía es que las
referencias son aquellos materiales de consulta (sitios web, libros, papers, posts, etc.),
para los cuales se emplea una referencia dentro del informe de forma explícita (e.g.,
“... para más información, ver Aho y col., 2006... ”). La bibliografía, en cambio, es material consultado que no se referencia dentro del informe, pero que sí fue accedido
y/o leído para comprender o para implementar el proyecto (e.g., la documentación de C/C++, o las clases de la cátedra). -->
