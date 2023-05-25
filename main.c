#include "shell.h"

/**
 * main - Entry point
 *
 * Return: 0 on success, 1 on error
 */
#define BUFFER_SIZE 1024

/* Function declarations */
void execute_command(char *command);
void handle_child_process(char *command);
void handle_parent_process(void);

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

/**
 * execute_command - Execute the given command
 * @command: The command to execute
 */
void execute_command(char *command)
{
	if (fork() == 0)
	{
		/* Child process */
		handle_child_process(command);
	}
	else
	{
		/* Parent process */
		handle_parent_process();
	}
}

/**
 * handle_child_process - Handle the child process
 * @command: The command to execute
 */
void handle_child_process(char *command)
{
	char *args[] = {"/bin/sh", "-c", NULL, NULL};
	args[2] = command;

	if (execve(args[0], args, NULL) == -1)
	{
		/* Command not found */
		perror(command);
		exit(EXIT_FAILURE);
	}
}

/**
 * handle_parent_process - Handle the parent process
 */
void handle_parent_process(void)
{
	wait(NULL); /* Wait for the child process to complete */
}

