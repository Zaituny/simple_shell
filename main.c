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
	int pipefd[2];
	pid_t pid;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		/* Child process */
		close(pipefd[0]); /* Close the read end of the pipe */
		dup2(pipefd[1], STDOUT_FILENO); /* Redirect stdout to the write end of the pipe */
		close(pipefd[1]); /* Close the write end of the pipe */

		if (execlp(command, command, NULL) == -1)
		{
			/* Command not found */
			perror(command);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process */
		char output[BUFFER_SIZE];
		int nbytes;

		close(pipefd[1]); /* Close the write end of the pipe */

		while ((nbytes = read(pipefd[0], output, BUFFER_SIZE - 1)) > 0)
		{
			output[nbytes] = '\0';
			printf("%s", output); /* Print the output from the child process */
		}

		close(pipefd[0]); /* Close the read end of the pipe */

		wait(NULL); /* Wait for the child process to complete */
	}
}

/**
 * handle_parent_process - Handle the parent process
 */
void handle_parent_process(void)
{
	wait(NULL); /* Wait for the child process to complete */
}
