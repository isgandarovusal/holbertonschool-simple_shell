#include "shell.h"

/**
 * _getenv - Öz getenv funksiyamız
 * @name: Dəyişənin adı
 * Return: Dəyəri və ya NULL
 */
char *_getenv(const char *name)
{
	int i;
	size_t len = strlen(name);

	if (environ == NULL || name == NULL)
		return (NULL);

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
			return (environ[i] + len + 1);
	}
	return (NULL);
}

/**
 * _which - Komandanı yalnız PATH-də axtarır
 * @command: Komanda adı
 * Return: Tam yol və ya NULL
 */
char *_which(char *command)
{
	char *path, *path_copy, *token, *full_path;
	struct stat st;
	int i, has_slash = 0;

	if (command == NULL)
		return (NULL);

	/* Komandanın içində '/' olub-olmadığını yoxla */
	for (i = 0; command[i]; i++)
	{
		if (command[i] == '/')
		{
			has_slash = 1;
			break;
		}
	}

	/* Əgər '/' varsa, birbaşa sistemdə yoxla */
	if (has_slash)
	{
		if (stat(command, &st) == 0)
			return (strdup(command));
		return (NULL);
	}

	path = _getenv("PATH");
	if (path == NULL || strlen(path) == 0)
		return (NULL);

	path_copy = strdup(path);
	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		full_path = malloc(strlen(token) + strlen(command) + 2);
		sprintf(full_path, "%s/%s", token, command);
		if (stat(full_path, &st) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		token = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
