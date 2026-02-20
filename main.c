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
			status = execute_command(args, env, av[0]);

			/* Komanda tapılmadıqda və boru (pipe) rejimində olduqda */
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
