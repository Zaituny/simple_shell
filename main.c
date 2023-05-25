#include "shell.h"

/**
 * main - Entry point
 *
 * Return: 0 on success, 1 on error
 */
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

		execute_command(command);
	}

	printf("\n");
	return (0);
}
