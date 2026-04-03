# 🤝 Organización de Trabajo en Equipo - Shell Wish

## 🎯 Objetivo

Trabajar en paralelo en el laboratorio del shell (`wish`) sin conflictos, dividiendo responsabilidades y usando buenas prácticas con Git.

---

## 🌿 Estrategia de ramas

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

## 🔄 Flujo de trabajo

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

## 🧩 División de tareas (tipo Jira)

### 🧱 ÉPICA 1: Base del shell

* **TASK-1 (Santiago):** Loop principal (`main`, `getline`)
* **TASK-2 (Emiro):** Modo batch (leer desde archivo)

---

### 🔍 ÉPICA 2: Parsing

* **TASK-3 (Santiago):** Tokenización (`strsep`)
* **TASK-4 (Santiago):** Estructura `Command`
* **TASK-5 (Santiago):** Parsing de `>` y `&`

---

### ⚙️ ÉPICA 3: Ejecución

* **TASK-6 (Emiro):** `fork()` + `execv()`
* **TASK-7 (Emiro):** Manejo de argumentos
* **TASK-8 (Emiro):** `wait()` / `waitpid()`

---

### 🧠 ÉPICA 4: Built-in commands

* **TASK-9 (Emiro):** `exit`
* **TASK-10 (Emiro):** `cd`
* **TASK-11 (Emiro):** `path`

---

### 📂 ÉPICA 5: Path

* **TASK-12 (Emiro):** Búsqueda de ejecutables (`access`)

---

### 📤 ÉPICA 6: Redirección

* **TASK-13 (Emiro):** Redirección `>`

---

### ⚡ ÉPICA 7: Paralelismo

* **TASK-14 (Santiago + Emiro):**

  * Santiago: parsing de `&`
  * Emiro: ejecución en paralelo

---

### ❌ ÉPICA 8: Manejo de errores

* **TASK-15 (Santiago):** Mensaje único de error

---

### 🔗 ÉPICA 9: Integración

* **TASK-16 (Ambos):** Integrar parser + ejecución

---

### 🧪 ÉPICA 10: Testing

* **TASK-17 (Ambos):** Pruebas completas

---

## 📦 Contrato entre módulos

Para evitar conflictos, se define esta estructura:

```c
typedef struct {
    char *command;
    char **args;
    int background;
    char *redirect_file;
} Command;
```

* **Santiago** construye esta estructura (parser)
* **Emiro** la usa para ejecutar comandos

---

## 🕒 Reglas de trabajo

* Hacer commits pequeños y claros
* No trabajar directamente en `main`
* Hacer pull antes de empezar
* Integrar cambios diariamente
* Probar antes de hacer push

---


