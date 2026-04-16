#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

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

        if (getline(&line, &len, input) == -1) {
            exit(0);
        }

        line[strcspn(line, "\n")] = '\0';

        // 🔥 SEPARAR POR &
        char *commands[100];
        int cmd_count = 0;
        char *line_ptr = line;
        char *cmd;

        while ((cmd = strsep(&line_ptr, "&")) != NULL) {
            if (strlen(cmd) > 0) {
                commands[cmd_count++] = cmd;
            }
        }

        pid_t pids[100];
        int pid_count = 0;

        for (int c = 0; c < cmd_count; c++) {
            char *args[100];
            int arg_count = 0;

            char *cmd_ptr = commands[c];
            char *token;

            while ((token = strsep(&cmd_ptr, " \t")) != NULL) {
                if (strlen(token) > 0) {
                    args[arg_count++] = token;
                }
            }
            args[arg_count] = NULL;

            if (arg_count == 0) continue;

            // 🔹 BUILT-IN
            if (strcmp(args[0], "exit") == 0) {
                if (arg_count > 1) print_error();
                else {
                    clear_path();
                    free(line);
                    exit(0);
                }
            } 
            else if (strcmp(args[0], "cd") == 0) {
                if (arg_count != 2) print_error();
                else if (chdir(args[1]) != 0) print_error();
            } 
            else if (strcmp(args[0], "path") == 0) {
                clear_path();
                for (int i = 1; i < arg_count; i++) {
                    search_path[path_count++] = strdup(args[i]);
                }
                search_path[path_count] = NULL;
            } 
            else {
                // 🔹 REDIRECCIÓN
                char *out_file = NULL;
                int red_idx = -1;

                for (int i = 0; i < arg_count; i++) {
                    if (strcmp(args[i], ">") == 0) {
                        if (red_idx != -1 || i == 0 || i != arg_count - 2) {
                            print_error();
                            goto next_command;
                        }
                        red_idx = i;
                    }
                }

                if (red_idx != -1) {
                    out_file = args[red_idx + 1];
                    args[red_idx] = NULL;
                }

                // 🔹 BUSCAR EJECUTABLE
                char *executable = NULL;
                for (int i = 0; i < path_count; i++) {
                    char buffer[512];
                    snprintf(buffer, sizeof(buffer), "%s/%s", search_path[i], args[0]);
                    if (access(buffer, X_OK) == 0) {
                        executable = strdup(buffer);
                        break;
                    }
                }

                if (executable == NULL) {
                    print_error();
                    goto next_command;
                }

                pid_t pid = fork();
                if (pid == 0) {
                    // 🔹 HIJO
                    if (out_file != NULL) {
                        int fd = open(out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                        if (fd < 0) {
                            print_error();
                            exit(1);
                        }
                        dup2(fd, STDOUT_FILENO);
                        dup2(fd, STDERR_FILENO);
                        close(fd);
                    }

                    execv(executable, args);
                    exit(1);
                } 
                else if (pid > 0) {
                    pids[pid_count++] = pid;
                } 
                else {
                    print_error();
                }

                free(executable);
            }

            next_command: ;
        }

        // 🔥 ESPERAR TODOS LOS PROCESOS (PARALELOS)
        for (int i = 0; i < pid_count; i++) {
            waitpid(pids[i], NULL, 0);
        }
    }

    return 0;
}