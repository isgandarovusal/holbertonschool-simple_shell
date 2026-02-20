
#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* Access to environment */
extern char **environ;

/* PROTOTYPES - These must match your function definitions exactly */
char *read_line(void);             /* Found in reader.c */
char **tokenize_line(char *line);  /* Found in tokenizer.c */
void execute_command(char **args); /* Found in executor.c */
char *_which(char *command);       /* Found in path_finder.c */

#endif
