#include "shell.h"

/**
 * execute_command - Komandanı PATH-də axtarır və icra edir
 * @args: İstifadəçinin daxil etdiyi komanda və arqumentlər
 * @env: Ətraf mühit dəyişənləri
 * @prog_name: Shell proqramının adı (xəta mesajı üçün)
 */
void execute_command(char **args, char **env, char *prog_name)
{
    char *actual_command;
    pid_t child_pid;
    int status;

    if (args == NULL || args[0] == NULL)
        return;

    /* 1. FORK ETMƏDƏN ƏVVƏL komandanın olub-olmadığını yoxla */
    actual_command = _which(args[0]);

    if (actual_command == NULL)
    {
        fprintf(stderr, "%s: 1: %s: not found\n", prog_name, args[0]);
        exit(127); 
}

    /* 2. Komanda mütləq varsa, indi fork edə bilərik */
    child_pid = fork();
    if (child_pid == -1)
    {
        perror("Fork failed");
        if (actual_command != args[0])
            free(actual_command);
        return;
    }

    if (child_pid == 0)
    {
        /* Uşaq proses (Child Process) komandanı icra edir */
        if (execve(actual_command, args, env) == -1)
        {
            perror(prog_name);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        /* Ana proses (Parent Process) uşaq prosesin bitməsini gözləyir */
        wait(&status);
        
        /* Əgər _which funksiyası yeni (malloc ilə) string yaradıbsa, onu təmizlə */
        if (actual_command != args[0])
            free(actual_command);
    }
}
