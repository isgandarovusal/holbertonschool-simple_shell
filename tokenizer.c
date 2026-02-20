#include "shell.h"

/**
 * tokenize_line - Sətri boşluqlara görə hissələrə ayırır
 * @line: bölünəcək sətir
 * Return: Sözlər massivi
 */
char **tokenize_line(char *line)
{
    int bufsize = 64, i = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens)
        return (NULL);

    token = strtok(line, " \t\r\n\a");
    while (token != NULL)
    {
        tokens[i] = token;
        i++;
        token = strtok(NULL, " \t\r\n\a");
    }
    tokens[i] = NULL;
    return (tokens);
}
