#include "shell.h"

/**
 * count_tokens - Count number of tokens in a string
 * @str: String to count tokens in
 *
 * Return: Number of tokens
 */
int count_tokens(char *str)
{
	int count = 0;
	char *token;
	char *str_copy;
	char *delim = " \t\n";

	if (str == NULL || str[0] == '\0')
		return (0);

	str_copy = strdup(str);
	if (str_copy == NULL)
		return (0);

	token = strtok(str_copy, delim);
	while (token != NULL)
	{
		count++;
		token = strtok(NULL, delim);
	}

	free(str_copy);
	return (count);
}

/**
 * tokenize_line - Split a line into arguments
 * @line: Line to tokenize
 *
 * Return: NULL-terminated array of strings
 */
char **tokenize_line(char *line)
{
	char **args;
	char *token;
	int i, token_count;
	char *delim = " \t\n";

	if (line == NULL || line[0] == '\0')
		return (NULL);

	token_count = count_tokens(line);
	if (token_count == 0)
		return (NULL);

	args = malloc(sizeof(char *) * (token_count + 1));
	if (args == NULL)
		return (NULL);

	token = strtok(line, delim);
	i = 0;
	while (token != NULL)
	{
		args[i] = strdup(token);
		if (args[i] == NULL)
		{
			while (--i >= 0)
				free(args[i]);
			free(args);
			return (NULL);
		}
		i++;
		token = strtok(NULL, delim);
	}
	args[i] = NULL;

	return (args);
}
