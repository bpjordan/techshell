#ifndef REDIRECTION_H
#define REDIRECTION_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int *parseRedirection(char **);
void cleanupRedirection(int* filenos);

#endif
