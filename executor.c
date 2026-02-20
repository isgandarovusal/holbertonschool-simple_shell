#include "shell.h"

/**
 * execute_command - Komandanı PATH-də axtarır və icra edir
 * @args: Komanda və parametrlər
 * @env: Environment
 * @prog_name: Proqramın adı (hsh)
 * Return: Komanda tapılmasa 127, uğurlu olsa 0
 */
int execute_command(char **args, char **env, char *prog_name)
{
	char *actual_command;
	pid_t child_pid;
	int status;

	if (args == NULL || args[0] == NULL)
		return (0);

	actual_command = _which(args[0]);

	if (actual_command == NULL)
	{
		/* Xəta mesajını standart error-a çap edirik */
		fprintf(stderr, "%s: 1: %s: not found\n", prog_name, args[0]);
		return (127);
	}

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Fork failed");
		if (actual_command != args[0])
			free(actual_command);
		return (1);
	}

	if (child_pid == 0) /* Child process */
	{
		if (execve(actual_command, args, env) == -1)
		{
			perror(prog_name);
			exit(EXIT_FAILURE);
		}
	}
	else /* Parent process */
	{
		wait(&status);
		if (actual_command != args[0])
			free(actual_command);
	}

	return (0);
}
