#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h> // Necesario para open()

char error_message[30] = "An error has occurred\n";
char *search_path[100]; 
int path_count = 0;

void print_error() {
    write(STDERR_FILENO, error_message, strlen(error_message));
}

void clear_path() {
    for (int i = 0; i < path_count; i++) {
        if (search_path[i] != NULL) free(search_path[i]);
    }
    path_count = 0;
}

int main(int argc, char *argv[]) {
    FILE *input = stdin;
    char *line = NULL;
    size_t len = 0;

    search_path[path_count++] = strdup("/bin");
    search_path[path_count] = NULL;

    if (argc > 2) {
        print_error();
        exit(1);
    }
    if (argc == 2) {
        input = fopen(argv[1], "r");
        if (input == NULL) {
            print_error();
            exit(1);
        }
    }

    while (1) {
        if (input == stdin) {
            printf("wish> ");
            fflush(stdout);
        }

        if (getline(&line, &len, input) == -1) break;
        line[strcspn(line, "\n")] = '\0';

        char *line_ptr = line;
        char *token;
        char *args[100];
        int arg_count = 0;

        while ((token = strsep(&line_ptr, " \t")) != NULL) {
            if (strlen(token) > 0) args[arg_count++] = token;
        }
        args[arg_count] = NULL;

        if (arg_count == 0) continue;

        /* --- COMANDOS BUILT-IN --- */
        if (strcmp(args[0], "exit") == 0) {
            if (arg_count > 1) print_error();
            else { clear_path(); free(line); exit(0); }
        } 
        else if (strcmp(args[0], "cd") == 0) {
            if (arg_count != 2) print_error();
            else if (chdir(args[1]) != 0) print_error();
        } 
        else if (strcmp(args[0], "path") == 0) {
            clear_path();
            for (int i = 1; i < arg_count; i++) search_path[path_count++] = strdup(args[i]);
            search_path[path_count] = NULL;
        } 
        /* --- COMANDOS EXTERNOS --- */
        else {
            char *out_file = NULL;
            int red_idx = -1;

            // BUSCAR SI HAY UN '>' EN LOS ARGUMENTOS
            for (int i = 0; i < arg_count; i++) {
                if (strcmp(args[i], ">") == 0) {
                    // Validar: solo un '>', que no sea el primero, y que haya exactamente un archivo después
                    if (red_idx != -1 || i == 0 || i != arg_count - 2) {
                        print_error();
                        goto next_iter;
                    }
                    red_idx = i;
                }
            }

            if (red_idx != -1) {
                out_file = args[red_idx + 1]; // El archivo es el que sigue al '>'
                args[red_idx] = NULL;         // Cortamos los argumentos para que execv no vea el '>'
            }

            char *executable = NULL;
            for (int i = 0; i < path_count; i++) {
                char buffer[512];
                snprintf(buffer, sizeof(buffer), "%s/%s", search_path[i], args[0]);
                if (access(buffer, X_OK) == 0) {
                    executable = strdup(buffer);
                    break;
                }
            }

            if (executable) {
                pid_t pid = fork();
                if (pid == 0) { // Proceso Hijo
                    if (out_file != NULL) {
                        // RE-DIRECCIÓN: Cerramos la salida normal y abrimos el archivo
                        int fd = open(out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                        if (fd < 0) { print_error(); exit(1); }
                        dup2(fd, STDOUT_FILENO); // Redirigir salida
                        dup2(fd, STDERR_FILENO); // Redirigir error (según PDF)
                        close(fd);
                    }
                    execv(executable, args);
                    exit(1); 
                } else {
                    wait(NULL);
                }
                free(executable);
            } else {
                print_error();
            }
        }
        next_iter: ;
    }
    return 0;
}