# Organización de Trabajo en Equipo - Shell Wish

## Objetivo

Trabajar en paralelo en el laboratorio del shell (`wish`) sin conflictos, dividiendo responsabilidades y usando buenas prácticas con Git.

---

## Estrategia de ramas

* Rama principal: `main`
* Rama para realizar pull request:`develop`
* Cada integrante trabaja en su propia rama:

```bash
feature/parser
feature/executor
feature/builtins
feature/redirection
```

---

## Flujo de trabajo

1. Actualizar repositorio:

```bash
git pull origin develop
```

2. Crear rama:

```bash
git checkout -b feature/nombre-tarea
```

3. Trabajar en la tarea asignada

4. Guardar cambios:

```bash
git add .
git commit -m "feat: descripción clara del cambio"
```

5. Subir cambios:

```bash
git push origin feature/nombre-tarea
```

6. Crear Pull Request en GitHub

7. Revisar y hacer merge a `develop`

---

## División de tareas (tipo Jira)

## División de tareas (tipo Jira)

### ÉPICA 1: Base del shell

* **TASK-1 (Santiago): Loop principal (`main`, `getline`)**
  
  Implementar el ciclo infinito del shell en `main`:
  - Mostrar el prompt `wish> ` en modo interactivo.
  - Leer entrada usando `getline()`.
  - Detectar EOF (Ctrl+D) y terminar con `exit(0)`.
  - Validar que el shell se ejecute con 0 o 1 argumento.
  - Delegar la línea leída al módulo de parsing.

* **TASK-2 (Emiro): Modo batch (leer desde archivo)**

  Implementar ejecución en modo batch:
  - Detectar si se recibe un archivo como argumento.
  - Leer comandos línea por línea desde el archivo.
  - No imprimir el prompt en este modo.
  - Manejar errores si el archivo no existe o no se puede abrir.
  - Reutilizar el mismo flujo de parsing y ejecución.

---

### ÉPICA 2: Parsing

* **TASK-3 (Santiago): Tokenización (`strsep`)**

  Separar la entrada en tokens:
  - Usar `strsep()` para dividir por espacios y tabs.
  - Manejar múltiples espacios consecutivos.
  - Ignorar tokens vacíos.
  - Preparar base para detectar operadores especiales (`>`, `&`).

* **TASK-4 (Santiago): Estructura `Command`**

  Construir una abstracción del comando:
  - Llenar `command` (nombre del ejecutable).
  - Construir arreglo `args` terminado en `NULL` (requerido por `execv`).
  - Inicializar flags (`background`, `redirect_file`).
  - Validar consistencia de datos.

* **TASK-5 (Santiago): Parsing de `>` y `&`**

  Extender el parser para operadores:
  - Detectar redirección `>` y capturar archivo destino.
  - Validar que solo exista una redirección.
  - Detectar ejecución en background con `&`.
  - Separar múltiples comandos si hay varios `&`.
  - Marcar errores de sintaxis (ej: múltiples `>` o falta de archivo).

---

### ÉPICA 3: Ejecución

* **TASK-6 (Emiro): `fork()` + `execv()`**

  Ejecutar comandos externos:
  - Crear proceso hijo con `fork()`.
  - En el hijo, llamar `execv()` con el comando y argumentos.
  - Manejar error si `execv` retorna.
  - El padre continúa controlando el flujo.

* **TASK-7 (Emiro): Manejo de argumentos**

  Preparar correctamente los argumentos:
  - Asegurar que `args` termine en `NULL`.
  - Pasar correctamente `argv[0]` como nombre del comando.
  - Validar casos sin argumentos.

* **TASK-8 (Emiro): `wait()` / `waitpid()`**

  Sincronización de procesos:
  - Usar `wait()` o `waitpid()` para esperar procesos hijos.
  - No esperar si el comando es en background.
  - Manejar múltiples hijos en caso de paralelismo.

---

### ÉPICA 4: Built-in commands

* **TASK-9 (Emiro): `exit`**

  Implementar comando interno:
  - Terminar el shell con `exit(0)`.
  - Validar que no reciba argumentos.

* **TASK-10 (Emiro): `cd`**

  Cambio de directorio:
  - Usar `chdir()`.
  - Validar que reciba exactamente un argumento.
  - Manejar error si falla.

* **TASK-11 (Emiro): `path`**

  Manejo de rutas:
  - Mantener lista de directorios.
  - Permitir sobrescribir rutas existentes.
  - Soportar múltiples rutas separadas por espacios.

---

### ÉPICA 5: Path

* **TASK-12 (Emiro): Búsqueda de ejecutables (`access`)**

  Resolver comandos:
  - Recorrer directorios del `path`.
  - Verificar existencia con `access(path, X_OK)`.
  - Construir ruta completa del ejecutable.
  - Manejar error si no se encuentra.

---

### ÉPICA 6: Redirección

* **TASK-13 (Emiro): Redirección `>`**

  Redirigir salida estándar y error:
  - Abrir archivo con `open()` (crear o truncar).
  - Usar `dup2()` para redirigir `STDOUT` y `STDERR`.
  - Cerrar descriptores innecesarios.
  - Validar errores de sintaxis.

---

### ÉPICA 7: Paralelismo

* **TASK-14 (Santiago + Emiro):**

  * **Santiago: parsing de `&`**
    - Separar múltiples comandos en una misma línea.
    - Generar múltiples estructuras `Command`.

  * **Emiro: ejecución en paralelo**
    - Ejecutar todos los comandos sin bloquear.
    - Guardar PIDs de procesos hijos.
    - Esperar todos los procesos al final.

---

### ÉPICA 8: Manejo de errores

* **TASK-15 (Santiago): Mensaje único de error**

  Centralizar errores:
  - Implementar mensaje: `"An error has occurred\n"`.
  - Escribir en `STDERR`.
  - Reutilizar para todos los casos de error.
  - No imprimir mensajes adicionales.

---

### ÉPICA 9: Integración

* **TASK-16 (Ambos): Integrar parser + ejecución**

  Integración completa:
  - Conectar salida del parser con módulo de ejecución.
  - Manejar flujo completo: input → parse → execute.
  - Validar interacción entre features (path, redirección, paralelismo).
  - Resolver conflictos entre módulos.

---

### ÉPICA 10: Testing

* **TASK-17 (Ambos): Pruebas completas**

  Validación del sistema:
  - Probar comandos simples (`ls`, `pwd`).
  - Probar con argumentos.
  - Probar built-ins (`cd`, `exit`, `path`).
  - Probar redirección (`>`).
  - Probar paralelismo (`&`).
  - Probar casos de error.
  - Crear casos de prueba en batch mode.

---

## Contrato entre módulos

Para evitar conflictos, se define esta estructura:

```c
typedef struct {
    char *command;
    char **args;
    int background;
    char *redirect_file;
} Command;
```

## Responsabilidades:

Santiago (Parser):
Construye completamente la estructura Command.
Garantiza que los datos sean válidos y consistentes.
Emiro (Ejecución):
Consume la estructura sin modificarla.
Ejecuta según los campos definidos.

---

## Reglas de trabajo

* Hacer commits pequeños y claros
* No trabajar directamente en `main`
* Hacer pull antes de empezar
* Integrar cambios diariamente
* Probar antes de hacer push

---


