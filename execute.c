#include "shell.h"

/**
 * handle_child_process - Handle the child process
 * @command: The command to execute
 */
void handle_child_process(char *command)
{
	pid_t pid;
	int pipefd[2];

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
		execute_child_process(command, pipefd);
	}
	else
	{
		/* Parent process */
		execute_parent_process(pipefd);
	}
}

/**
 * execute_child_process - Execute the child process
 * @command: The command to execute
 * @pipefd: The pipe file descriptors
 */
void execute_child_process(char *command, int pipefd[])
{
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);

	if (execlp(command, command, NULL) == -1)
	{
		perror(command);
		exit(EXIT_FAILURE);
	}
}

/**
 * execute_parent_process - Execute the parent process
 * @pipefd: The pipe file descriptors
 */
void execute_parent_process(int pipefd[])
{
	char output[BUFFER_SIZE];
	int nbytes;
	int buffer_size = 0;
	char buffer[BUFFER_SIZE];

	close(pipefd[1]);

	while ((nbytes = read(pipefd[0], output, BUFFER_SIZE - 1)) > 0)
	{
		output[nbytes] = '\0';
		strncpy(buffer + buffer_size, output, nbytes);
		buffer_size += nbytes;
	}

	close(pipefd[0]);

	/* Process the buffer and print output in the correct order */
	for (int i = 0; i < buffer_size; i++)
	{
		if (buffer[i] == '\n')
		{
			buffer[i] = '\0';
			printf("%s\n", buffer);
			buffer_size -= (i + 1);
			memmove(buffer, buffer + i + 1, buffer_size);
			i = -1;
		}
	}

	wait(NULL);
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
 * handle_parent_process - Handle the parent process
 */
void handle_parent_process(void)
{
	  wait(NULL);
}
