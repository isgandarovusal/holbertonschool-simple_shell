#include "shell.h"

/**
 * main - Simple shell proqramının əsas funksiyası
 * @ac: Arqument sayı
 * @av: Arqument massivi
 * @env: Environment
 * Return: Sonuncu status kodu
 */
int main(int ac, char **av, char **env)
{
	char *line = NULL;
	char **args = NULL;
	int status = 0;
	int i;
	(void)ac;

	while (1)
	{
		/* İnteraktiv rejimdə prompt göstər */
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, ":) ", 3);

		line = read_line();
		if (line == NULL) /* Ctrl+D (EOF) */
			break;

		args = tokenize_line(line);
		if (args && args[0])
		{
			/* 1. EXIT built-in yoxlanması */
			if (strcmp(args[0], "exit") == 0)
			{
				free(line);
				free(args);
				exit(status);
			}

			/* 2. ENV built-in yoxlanması */
			if (strcmp(args[0], "env") == 0)
			{
				for (i = 0; environ[i]; i++)
				{
					write(STDOUT_FILENO, environ[i], strlen(environ[i]));
					write(STDOUT_FILENO, "\n", 1);
				}
				status = 0;
			}
			else
			{
				/* 3. Normal komanda icrası */
				status = execute_command(args, env, av[0]);
			}

			/* Komanda tapılmadıqda və qeyri-interaktiv rejimdə çıxış */
			if (status == 127 && !isatty(STDIN_FILENO))
			{
				free(line);
				free(args);
				exit(127);
			}
		}

		/* Hər döngənin sonunda yaddaşı təmizləyirik */
		free(line);
		free(args);
		line = NULL;
		args = NULL;
	}

	return (status);
}
