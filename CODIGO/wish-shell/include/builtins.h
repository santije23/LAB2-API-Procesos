#ifndef BUILTINS_H
#define BUILTINS_H

#include "parser.h"

int is_builtin(Command *cmd);
void run_builtin(Command *cmd);

#endif