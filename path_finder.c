#include "shell.h"

/**
 * _getenv - Öz getenv funksiyamız (standart getenv qadağandır)
 * @name: Axtarılan dəyişənin adı (məs: PATH)
 * Return: Dəyişənin dəyəri və ya NULL
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
		{
			return (environ[i] + len + 1);
		}
	}
	return (NULL);
}

/**
 * _which - Komandanın PATH-də olub-olmadığını yoxlayır
 * @command: Komanda adı (ls, pwd və s.)
 * Return: Tam yol (path) və ya NULL
 */
char *_which(char *command)
{
	char *path, *path_copy, *token, *full_path;
	struct stat st;

	if (command == NULL)
		return (NULL);

	/* Əgər artıq tam yoldursa (/bin/ls), birbaşa yoxla */
	if (stat(command, &st) == 0)
		return (strdup(command));

	/* DİQQƏT: Burada _getenv çağırılır (standart getenv yox!) */
	path = _getenv("PATH");
	if (path == NULL || strlen(path) == 0)
		return (NULL);

	path_copy = strdup(path);
	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		full_path = malloc(strlen(token) + strlen(command) + 2);
		if (full_path == NULL)
		{
			free(path_copy);
			return (NULL);
		}
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
