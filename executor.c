#include "shell.h"

/**
 * execute - forks and executes a command
 * @args: array of arguments
 */
void execute(char **args)
{
    char *actual_command;
    pid_t child_pid;
    int status;

    if (args == NULL || args[0] == NULL)
        return;

    /* Find path before forking */
    actual_command = _which(args[0]);

    if (actual_command == NULL)
    {
        perror("./hsh"); /* Or your specific error format */
        return;
    }

    child_pid = fork();
    if (child_pid == -1)
    {
        perror("Error:");
        if (actual_command != args[0])
            free(actual_command);
        return;
    }

    if (child_pid == 0)
    {
        if (execve(actual_command, args, environ) == -1)
        {
            perror("Error:");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        wait(&status);
        /* Free if _which returned a newly allocated string */
        if (actual_command != args[0])
            free(actual_command);
    }
}
