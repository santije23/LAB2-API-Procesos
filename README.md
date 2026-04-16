# LAB2-API-Procesos

## Para compilar ejecutar el comando ``gcc -o wish wish.c -Wall``

## (a) Nombres completos de los integrantes, correos y números de documento.


### Santiago Jiménez Escobar - santiago.jimeneze@udea.edu.co - C.C 1036959331
### Emiro Moreno Soto - emiro.morenos@udea.edu.co - C.C 1001547311



## (b) Documentación de todas las funciones desarrolladas en el código.

- Funcion  ``print_error()``: Esta función es utilizada para los casos en los cuales el aplicativo genere algún error en ejecución, por lo cual se centraliza con esta función la cual incluye subfunciones como ``write()`` para poder imprimir por la salida de errores el mensaje y ``strlen()`` la cual ayuda a contar la cantidad de caracteres o bytes que tiene el mensaje a mostrar.

- La función ``clear_path()`` es utilizada dentro de la ejecución del código en los casos en que se utiliza el path y es necesario liberar la memoria asociada a los paths guardados en la variable ``search_path``. Esta liberación se realiza en 3 momentos: una cuando el usuario actualiza el path, otra cuando el usuario ejecuta el comando route sin ningún argumento y cuando se finaliza la ejecución con la funcion ``exit()``, en los tres casos se libera esa memoria mediante esta función.

- Con la función ``fopen(argv[1], "r")`` se realiza la apertura del archivo cuando el usuario lo envía después de la ejecución del programa mediante ./wish, antes de esta apertura, se contempló que si el usuario enviaba más de 1 archivo, debía aparecer error, o si en la apertura del archivo no se encontraba en la ruta o estaba vacío, también se salió con error.

- La función ``fflush(stdout)`` permite imprimir en pantalla sin necesidad de esperar que el buffer de memoria esté lleno o que haya un salto de línea; esto se implementó para poder mostrar de manera correcta la leyenda wish> en pantalla y que fuera más interactiva.

- La función ``strcspn(line, "\n")`` se encarga de encontrar en una linea "comando ingresado" el salto de línea "\n", con esto podemos reemplazar ese carácter por un "\0" (carácter nulo), lo cual le indicaría al sistema que es el final de la línea y asi se evitarían errores de ejecucion.

- Con ``strsep()`` es posible delimitar una cadena de caracteres por un carácter en especial; de esta manera se puede segmentar en diferentes partes para una utilización posterior. 

- Mediante ``strcmp()`` permite realizar la implementación de comandos internos como exit, en la cual, por medio de ``strcmp()`` se puede realizar la comparación de dos caracteres; en caso de ser exactamente iguales, devuelve 0, y se ejecuta el código correspondiente. Con esto podemos validar cuándo un usuario ingresa un comando correctamente. 

- Mediante ``strdup()`` la utilizamos para duplicar una cadena, en este caso una copia del path ya que en el siguiente ciclo del shell esta ruta se borrará.

- Con la funcion ``snprintf(buffer, sizeof(buffer), "%s/%s", search_path[i], args[0])`` podemos concatenar las rutas del path con los comandos que se envian por pantalla o por archivo, lo cual me permite utilizar un comando sin necesidad de construir la ruta completa donde se encuentra guardado.

- Implementación de ``access(buffer, X_OK) == 0``, con access se realiza una llamada al sistema para verificar si contamos con los permisos para intentar abrir un archivo, en caso de que no, se ignora esa ruta y se pasaría a la siguiente.
## (c) Problemas presentados durante el desarrollo de la práctica y sus soluciones.

Uno de los problema tubo que ver en cuando a la estructuracion del proyecto, debido a que en esta oportunidad era un solo aplicativo en funcionamiento, se requeria de una coordinacion mucho mayor para poder realizar la integracion de todas las funcinalidades de una manera adecuada, inicialmente se contemplo una estructura divida en forma de sprint, con epicas y task asignadas, sin embargo debido a que vamos comprendiendo el funcioamiento del codigo sobre la marcha, se volvia una estructura demasiado compleja para seguir, por lo cual se desidio implementar el codigo en dos partes, una consistia en implementar la logica basica de la consola, pasando por el parser y la verificacion de documentos ingresados por aparte y otra en cuando la ejecucion de los comandos y el path, con esto consideramos que se pudo avanzar de una manera mucho mas agil y entendible para todos.


## (d) Pruebas realizadas a los programas que verificaron su funcionalidad.



## (e) Un enlace a un video de 10 minutos donde se sustente el desarrollo.



## (f) Manifiesto de transparencia: En que puntos se apoyaron de la IA generativa.
Se solicitó ayuda en la generación de una estructura para trabajar simultáneamente el desarrollo del proyecto, sin embargo, el resultado no fue el esperado debido a que organizar la codificación de un aplicativo tan lineal de esa manera no es tan conveniente con ese tipo de estructura.