#include "shell.h"

void display_prompt(void)
{
    if (isatty(STDIN_FILENO))
        printf("#cisfun$ ");
    fflush(stdout);
}

void free_args(char **args)
{
    int i;
    if (args == NULL)
        return;
    for (i = 0; args[i] != NULL; i++)
        free(args[i]);
    free(args);
}

int main(int ac, char **av, char **env)
{
    char *line;
    char **args;
    int interactive = isatty(STDIN_FILENO);
    (void)ac;
    while (1)
    {
        display_prompt();
        line = read_line();
        if (line == NULL)
        {
            if (interactive)
                printf("\n");
            break;
        }
        if (line[0] == '\0')
        {
            free(line);
            continue;
        }
        args = tokenize_line(line);
        free(line);
        if (args == NULL || args[0] == NULL)
        {
            free_args(args);
            continue;
        }
        execute_command(args, env, av[0]);
        free_args(args);
    }
    return (0);
}
