#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* Ətraf mühit dəyişənləri (Global variable) */
extern char **environ;

/* --- Funksiya Prototipləri --- */

/* Giriş/Çıxış və Oxuma (reader.c) */
char *read_line(void);

/* Sətrin parçalanması (tokenizer.c) */
char **tokenize_line(char *line);

/* Komandanın icrası (executor.c) */
void execute_command(char **args, char **env, char *prog_name);

/* PATH axtarışı (path_finder.c) */
char *_which(char *command);

char *_getenv(const char *name);

#endif /* SHELL_H */
