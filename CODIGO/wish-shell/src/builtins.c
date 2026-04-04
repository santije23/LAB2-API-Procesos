#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "builtins.h"

int is_builtin(Command *cmd) {
    return strcmp(cmd->command, "exit") == 0 ||
           strcmp(cmd->command, "cd") == 0 ||
           strcmp(cmd->command, "path") == 0;
}

void run_builtin(Command *cmd) {
    if (strcmp(cmd->command, "exit") == 0) {
        exit(0);
    }
    if (strcmp(cmd->command, "cd") == 0) {
        chdir(cmd->args[1]);
    }
}