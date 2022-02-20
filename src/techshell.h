#ifndef TECHSHELL_H
#define TECHSHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "tokenizer.h"
#include "redirection.h"
#include "builtins.h"

#define MAX_INPUT 256
#define CWD_BUFF 256

void prompt();

#endif
