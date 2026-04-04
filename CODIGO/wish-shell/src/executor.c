#include <unistd.h>
#include <sys/wait.h>
#include "executor.h"
#include "builtins.h"

void execute_command(Command *cmd) {
    if (is_builtin(cmd)) {
        run_builtin(cmd);
    } else {
        if (fork() == 0) {
            execv(cmd->command, cmd->args);
        } else {
            wait(NULL);
        }
    }
}