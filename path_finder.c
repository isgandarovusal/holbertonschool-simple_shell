#include "shell.h"

/**
 * _which - Komandanın tam yolunu (path) tapır
 * @command: axtarılan komanda (məsələn: ls)
 * Return: Tapılsa tam yol (məsələn: /bin/ls), tapılmasa NULL
 */
char *_which(char *command)
{
    char *path, *path_copy, *token, *full_path;
    struct stat st;

    /* Əgər command artıq tam yoldursa (/bin/ls) və ya movcuddursa */
    if (stat(command, &st) == 0)
        return (command);

    path = getenv("PATH");
    if (path == NULL)
        return (NULL);

    path_copy = strdup(path);
    token = strtok(path_copy, ":");

    while (token != NULL)
    {
        /* directory + "/" + command üçün yer ayırırıq */
        full_path = malloc(strlen(token) + strlen(command) + 2);
        sprintf(full_path, "%s/%s", token, command);

        if (stat(full_path, &st) == 0)
        {
            free(path_copy);
            return (full_path); /* Tapıldı! */
        }

        free(full_path);
        token = strtok(NULL, ":");
    }

    free(path_copy);
    return (NULL);
}
