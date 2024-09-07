#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * read_line - Reads a line of input from the user.
 *
 * Return: Pointer to the input line.
 */
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t characters_read;

	characters_read = getline(&line, &bufsize, stdin);
	if (characters_read == -1)
	{
	if (feof(stdin))
	{
	/* Handle EOF (Ctrl+D) */
	printf("\n");
	free(line);
	exit(EXIT_SUCCESS);
	}
	else
	{
	perror("getline");
	exit(EXIT_FAILURE);
	}
	}

	return (line);
}

/**
 * execute_command - Executes a command using execve.
 * @command: The command to execute.
 */
void execute_command(char *command)
{
	pid_t pid;
	char *argv[2];

	command[strcspn(command, "\n")] = '\0';
	argv[0] = command;
	argv[1] = NULL;

	pid = fork();

	if (pid == -1)
	{
	perror("fork");
	exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
	/* Child process */
	if (execve(argv[0], argv, environ) == -1)
	{
	perror("./shell");
	}
	exit(EXIT_FAILURE);
	}
	else
	{
	/* Parent process waits for the child to finish */
	wait(NULL);
	}
}

/**
 * main - Entry point of the simple shell.
 *
 * Return: Always 0.
 */
int main(void)
{
	char *line;

	while (1)
	{
	printf("#cisfun$ "); /* Display the prompt */
	line = read_line(); /* Read user input */

	if (strcmp(line, "exit\n") == 0) /* Exit command */
	{
	free(line);
	break;
	}

	execute_command(line); /* Execute the entered command */
	free(line);
	}

	return (0);
}
