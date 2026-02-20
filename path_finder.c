#include "shell.h"

/**
 * get_path_env - Get PATH from environment
 * @env: Environment variables
 *
 * Return: PATH value or NULL
 */
char *get_path_env(char **env)
{
	int i;

	if (env == NULL)
		return (NULL);

	for (i = 0; env[i] != NULL; i++)
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
		{
			if (env[i][5] == '\0')
				return (NULL);
			return (env[i] + 5);
		}
	}
	return (NULL);
}

/**
 * build_path - Build full path from directory and command
 * @dir: Directory
 * @cmd: Command
 *
 * Return: Full path or NULL
 */
char *build_path(char *dir, char *cmd)
{
	char *full;
	size_t len;

	if (dir == NULL || cmd == NULL)
		return (NULL);

	len = strlen(dir) + strlen(cmd) + 2;
	full = malloc(len);
	if (full == NULL)
		return (NULL);

	sprintf(full, "%s/%s", dir, cmd);
	return (full);
}

/**
 * check_file_exists - Check if file exists
 * @path: Path to check
 *
 * Return: 1 if exists, 0 otherwise
 */
int check_file_exists(char *path)
{
	struct stat st;

	if (path == NULL)
		return (0);

	if (stat(path, &st) == 0)
		return (1);
	return (0);
}

/**
 * find_in_path - Search for command in PATH directories
 * @cmd: Command to find
 * @env: Environment variables
 *
 * Return: Full path or NULL
 */
char *find_in_path(char *cmd, char **env)
{
	char *path, *path_copy, *dir, *full = NULL;

	if (env == NULL || env[0] == NULL)
		return (NULL);

	path = get_path_env(env);
	if (path == NULL)
		return (NULL);

	path_copy = strdup(path);
	if (path_copy == NULL)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		full = build_path(dir, cmd);
		if (full && check_file_exists(full))
		{
			free(path_copy);
			return (full);
		}
		if (full)
			free(full);
		full = NULL;
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

/**
 * find_command_path - Find full path of a command
 * @cmd: Command to find
 * @env: Environment variables
 *
 * Return: Full path or NULL
 */
char *find_command_path(char *cmd, char **env)
{
	if (cmd == NULL)
		return (NULL);

	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (check_file_exists(cmd))
			return (strdup(cmd));
		return (NULL);
	}

	if (env == NULL || env[0] == NULL)
		return (NULL);

	return (find_in_path(cmd, env));
}
