#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* Access to the environment strings */
extern char **environ;

/* Function prototypes */
char *_which(char *command);
void execute(char **args);

#endif
