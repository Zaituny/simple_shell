#include "shell.h"

/**
 * main - Entry point
 *
 * Return: Always 0
 */
#define BUFFER_SIZE 1024

int main(void)
{
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    size_t buffer_len = BUFFER_SIZE;

    while (1)
    {
        printf("#cisfun$ ");

        bytes_read = getline(&buffer, &buffer_len, stdin);
        if (bytes_read == -1)
        {
            printf("\n");
            break;
        }

        buffer[bytes_read - 1] = '\0'; /* Remove the newline character */

        if (fork() == 0)
        {
            /* Child process */
            if (execve(buffer, NULL, NULL) == -1)
            {
                perror("execve");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            /* Parent process */
            wait(NULL);
        }
    }

    return 0;
}