#include "shell.h"

/**
 * run - Execute a command or program.
 * Function attempts to execute a command specified by the `tokens` arguments.
 *
 * @tokens: An array of strings containing the command and its arguments.
 * @args: Program arguments (not used in this version).
 * Return: 0 if the execution is successful, otherwise -1.
 */
int run(char **tokens, char *args)
{
	char *err1, *err2, *err3;
	pid_t child_pid;
	int status;
	char *path;

	if (_isBuiltIn(*tokens) == 0)
	{
		status = _executeBuiltIn(tokens);
		return (status);
	}

	path = path_builder(tokens);
	if (path != NULL)
	{
		status = execute2(tokens, path, args);
		return (status);
	}

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error: ");
		return (1);
	}
	if (child_pid == 0)
	{
		if (execve(tokens[0], tokens, NULL) == -1)
		{
			err1 = _strcat(*tokens, ": No such file or directory\n");
			err2 = _strcat(args, ":");
			err3 = _strcat(err2, err1);
			write(STDERR_FILENO, err3, _strlen(err3));
			free(tokens);
			exit(EXIT_FAILURE);
		}
		return (EXIT_SUCCESS);
	}

	wait(&status);
	return (0);
}

