#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

#define MAX_TOKENS 100

Command parse_input(char *line) {
    Command cmd;

    // 🔹 Inicializar TODO (muy importante)
    cmd.command = NULL;
    cmd.args = NULL;
    cmd.background = 0;
    cmd.redirect_file = NULL;

    // 🔹 quitar salto de línea
    line[strcspn(line, "\n")] = '\0';

    char *line_copy = line;
    char *token;

    // 🔹 reservar memoria para args
    cmd.args = malloc(sizeof(char*) * MAX_TOKENS);
    int i = 0;

    // 🔹 tokenización
    while ((token = strsep(&line_copy, " \t")) != NULL) {

        // ignorar espacios vacíos
        if (strlen(token) == 0) {
            continue;
        }

        cmd.args[i++] = token;
    }

    // 🔹 si no hay tokens → comando vacío
    if (i == 0) {
        free(cmd.args);
        cmd.args = NULL;
        return cmd;
    }

    // 🔹 terminar args en NULL (OBLIGATORIO)
    cmd.args[i] = NULL;

    // 🔹 el comando es el primer argumento
    cmd.command = cmd.args[0];

    return cmd;
}