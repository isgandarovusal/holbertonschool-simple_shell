#include "shell.h"

/**
 * execute_command - Komandanı icra edir
 * @args: Komanda və arqumentlər
 * @env: Environment
 * @prog_name: Proqramın adı
 */
void execute_command(char **args, char **env, char *prog_name)
{
	char *actual_command;
	pid_t child_pid;
	int status;

	if (args == NULL || args[0] == NULL)
		return;

	actual_command = _which(args[0]);

	if (actual_command == NULL)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", prog_name, args[0]);
		
		/* VALGRIND XƏTASINI DÜZƏLTMƏK ÜÇÜN: */
		/* Burada main-dən gələn args massivini təmizləyirik */
		if (args)
			free(args); 
		
		/* QEYD: Əgər main.c-dəki 'line' dəyişəni buraya gəlmirsə, 
		   still reachable qalacaq. Amma ilk addım olaraq bunu et: */
		exit(127);
	}

	child_pid = fork();
	if (child_pid == 0)
	{
		if (execve(actual_command, args, env) == -1)
		{
			perror(prog_name);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
		if (actual_command != args[0])
			free(actual_command);
	}
}
