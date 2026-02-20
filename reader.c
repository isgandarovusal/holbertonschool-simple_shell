#include "shell.h"

/**
 * read_line - İstifadəçidən sətri oxuyur
 * Return: Oxunmuş sətir
 */
char *read_line(void)
{
    char *line = NULL;
    size_t bufsize = 0;

    if (getline(&line, &bufsize, stdin) == -1)
    {
        free(line);
        return (NULL); /* EOF (Ctrl+D) */
    }
    return (line);
}
