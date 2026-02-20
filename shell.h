
n
n#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* Ətraf mühit dəyişənləri */
extern char **environ;

/* Funksiya prototipləri */
char *read_line(void);
char **tokenize_line(char *line);
void execute_command(char **args, char **env, char *prog_name);
char *_which(char *command);

#endif /* SHELL_H */
