## Estructura del Proyecto

```bash
wish-shell/
│
├── src/
│   ├── main.c
│   ├── parser.c
│   ├── executor.c
│   ├── builtins.c
│   ├── path.c
│   ├── redirect.c
│   └── parallel.c
│
├── include/
│   ├── parser.h
│   ├── executor.h
│   ├── builtins.h
│   ├── path.h
│   ├── redirect.h
│   └── parallel.h
│
├── Makefile
└── README.md
```


La carpeta `src/` contiene toda la implementación real del programa, es decir, donde vive la lógica. Ahí está `main.c`, que actúa como el punto central del shell: no hace trabajo pesado, sino que coordina todo. Es el que lee lo que escribe el usuario, llama al parser y luego al executor. Es importante que se mantenga simple porque es el punto donde se conectan todos los módulos.

Luego está `parser.c`, que tiene una responsabilidad muy específica: tomar el texto que escribe el usuario (por ejemplo `"ls -la > out.txt"`) y convertirlo en algo estructurado que el programa pueda entender. Aquí es donde defines cómo separar el comando, los argumentos, si hay redirección o ejecución en paralelo. Este archivo no ejecuta nada, solo interpreta.

Después viene `executor.c`, que recibe ese resultado ya estructurado (el `Command`) y decide qué hacer. Aquí es donde ocurre la acción real: si el comando es interno, delega a `builtins`; si es externo, usa llamadas del sistema como `fork` y `execv`. Este archivo no debería preocuparse por cómo se parseó el comando, solo por ejecutarlo.

`builtins.c` contiene los comandos que tu shell implementa directamente, como `exit`, `cd` y `path`. Estos no usan `fork` porque modifican el estado del propio proceso del shell. Por ejemplo, `cd` cambia el directorio del proceso actual, no de un hijo.

`path.c` se encarga de algo muy específico: resolver dónde está un ejecutable. Cuando el usuario escribe `ls`, tu shell necesita encontrar algo como `/bin/ls`. Esa lógica vive aquí, normalmente usando funciones como `access`.

`redirect.c` maneja la redirección de salida (`>`). Esto implica manipular descriptores de archivo con cosas como `dup2`, para que la salida estándar y de error se escriban en un archivo en lugar de la pantalla. Es una responsabilidad separada porque es una lógica distinta a ejecutar el comando en sí.

`parallel.c` maneja los comandos con `&`, es decir, cuando quieres ejecutar varios procesos al mismo tiempo. Aquí se crean múltiples procesos hijos antes de hacer los `wait`, lo cual cambia completamente el flujo respecto a la ejecución secuencial.

La carpeta `include/` contiene los `.h`, que son los contratos del sistema. Ahí defines qué funciones existen y cómo se ven (firmas), además de estructuras como `Command`. Esto permite que un archivo use funciones de otro sin conocer su implementación. Por ejemplo, `main.c` puede usar `parse_input` porque está declarado en `parser.h`, sin saber cómo está implementado en `parser.c`. Esta separación es lo que hace posible el trabajo en paralelo: uno puede implementar mientras el otro consume esas funciones.

El `Makefile` es el pegamento de todo. Le dice al compilador cómo tomar todos esos archivos separados y convertirlos en un solo ejecutable (`wish`). Además, incluye configuraciones como la ruta de los headers (`-Iinclude`) y evita que tengas que compilar manualmente archivo por archivo.

Finalmente, el `README.md` no afecta el programa en sí, pero es fundamental para documentar el proyecto: explicar qué hace, cómo se ejecuta, cómo está organizado y quién hizo qué. En tu laboratorio, además, es parte de la entrega.

En conjunto, esta estructura refleja una arquitectura modular: cada archivo tiene una responsabilidad clara, todos se comunican a través de interfaces (`.h`), y eso permite escalar el proyecto y dividir el trabajo sin conflictos.
