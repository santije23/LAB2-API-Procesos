#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "parser.h"
#include "executor.h"


/* Mensaje único de error */
char error_message[] = "An error has occurred\n";

int main(int argc, char *argv[]) {

    FILE *input = stdin;   // Por defecto: modo interactivo
    char *line = NULL;
    size_t len = 0;

    /* Validar argumentos */
    if (argc > 2) {
        write(STDERR_FILENO, error_message, strlen(error_message));
        exit(1);
    }

    /* Modo batch */
    if (argc == 2) {
        input = fopen(argv[1], "r");
        if (input == NULL) {
            write(STDERR_FILENO, error_message, strlen(error_message));
            exit(1);
        }
    }

    /* Loop principal del shell */
    while (1) {

        /* Mostrar prompt SOLO en modo interactivo */
        if (input == stdin) {
            printf("wish> ");
            fflush(stdout);
        }

        /* Leer línea */
        ssize_t read = getline(&line, &len, input);

        /* Detectar EOF (Ctrl+D o fin de archivo) */
        if (read == -1) {
            free(line);
            exit(0);
        }

        /* Ignorar líneas vacías */
        if (read == 1) {
            continue;
        }

        /* Llamar al parser */
        Command cmd = parse_input(line);
        execute_command(&cmd);
    }

    return 0;
}