#include "shell.h"

/**
 * main - Simple shell proqramının başlanğıc nöqtəsi
 * @ac: Arqumentlərin sayı (istifadə olunmur)
 * @av: Arqumentlər massivi (av[0] proqramın adıdır)
 * @env: Ətraf mühit dəyişənləri
 * * Return: Həmişə 0
 */
int main(int ac, char **av, char **env)
{
    char *line;
    char **args;
    (void)ac; /* 'ac' dəyişənini istifadə etmədiyimiz üçün xəbərdarlığı silir */

    while (1)
    {
        /* Yalnız interaktiv rejimdə (terminalda) prompt göstər */
        if (isatty(STDIN_FILENO))
            write(STDOUT_FILENO, ":) ", 3);

        /* 1. Sətri oxu */
        line = read_line();
        if (line == NULL)
        {
            /* EOF (Ctrl+D) gəldikdə çıxış et */
            if (isatty(STDIN_FILENO))
                write(STDOUT_FILENO, "\n", 1);
            break;
        }

        /* 2. Sətri sözlərə (tokenlərə) böl */
        args = tokenize_line(line);
        if (args != NULL && args[0] != NULL)
        {
            /* 3. Komandanı icra et */
            execute_command(args, env, av[0]);
        }

        /* Yaddaşı təmizlə */
        free(line);
        free(args);
    }

    return (0);
}
