#include "shell.h"

/**
 * main - Entry point
 *
 * Return: Always 0
 */

#define BUFFER_SIZE 1024

int main(void) {
    char command[BUFFER_SIZE];
    pid_t child_pid;
    int status;

    while (1) {
        printf("#cisfun$ ");
        fgets(command, BUFFER_SIZE, stdin);

        // Remove the trailing newline character from the command
        if (command[strlen(command) - 1] == '\n') {
            command[strlen(command) - 1] = '\0';
        }

        if (strlen(command) > 0) {
            child_pid = fork();
            if (child_pid == -1) {
                perror("fork");
                exit(EXIT_FAILURE);
            } else if (child_pid == 0) {
                // Child process
                if (execve(command, NULL, NULL) == -1) {
                    perror("execve");
                    exit(EXIT_FAILURE);
                }
            } else {
                // Parent process
                wait(&status);
            }
        }
    }

    return 0;
}
