#include "shell.h"

/**
 * main - entry point
 *
 * Return: 0 on success, 1 on error
 */
#define BUFFER_SIZE 1024

int main(void)
{
	char *command;
	char buffer[BUFFER_SIZE];

	while (1)
	{
		printf("#cisfun$ ");
		if (!fgets(buffer, BUFFER_SIZE, stdin))
			break; /* Exit on Ctrl+D (EOF) */

		/* Remove trailing newline character */
		if (buffer[strlen(buffer) - 1] == '\n')
			buffer[strlen(buffer) - 1] = '\0';

		command = buffer;

		/* Check if the command is "exit" */
		if (strcmp(command, "exit") == 0)
			break;

		/* Execute the command */
		if (fork() == 0)
		{
			/* Child process */
			char *args[] = {"/bin/sh", "-c", NULL, NULL};
			args[2] = command;
			if (execve(args[0], args, NULL) == -1)
			{
				/* Command not found */
				printf("%s: command not found\n", command);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			/* Parent process */
			wait(NULL); /* Wait for the child process to complete */
		}
	}

	printf("\n");
	return (0);
}
