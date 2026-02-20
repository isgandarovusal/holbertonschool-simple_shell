#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

/* Function prototypes */
void display_prompt(void);
char *read_line(void);
char **tokenize_line(char *line);
void free_args(char **args);
char *find_command_path(char *cmd, char **env);
char *get_path_env(char **env);
char *build_path(char *dir, char *cmd);
int check_file_exists(char *path);
char *find_in_path(char *cmd, char **env);
void execute_command(char **args, char **env, char *program_name);
void print_not_found(char *program_name, char *command);
int is_exit_command(char **args);
void handle_exit(char **args);

#endif /* SHELL_H */
