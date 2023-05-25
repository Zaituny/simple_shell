#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

/* Function declarations */
void execute_command(char *command);
void handle_child_process(char *command);
void execute_child_process(char *command, int pipefd[]);
void execute_parent_process(int pipefd[]);

#endif /* SHELL_H */
