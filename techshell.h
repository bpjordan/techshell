#ifndef TECHSHELL_H
#define TECHSHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT 256

void prompt();
char** tokenize(char *);

#endif
