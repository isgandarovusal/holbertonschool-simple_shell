void execute(char **args) {
    char *actual_command;
    pid_t child_pid;
    int status;

    /* 1. Find the path FIRST */
    actual_command = _which(args[0]);

    if (actual_command == NULL) {
        /* Command not found - PRINT ERROR AND RETURN */
        /* DO NOT FORK HERE */
        perror("Error"); 
        return;
    }

    /* 2. ONLY fork if the command was actually found */
    child_pid = fork();
    if (child_pid == -1) {
        perror("Fork failed");
        return;
    }

    if (child_pid == 0) {
        if (execve(actual_command, args, environ) == -1) {
            perror("Execve failed");
            exit(EXIT_FAILURE);
        }
    } else {
        wait(&status);
        /* Don't forget to free actual_command if it was malloc'd in path_finder */
        if (actual_command != args[0])
            free(actual_command);
    }
}
