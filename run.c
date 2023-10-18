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

	if (is_builtIn(*tokens) == 0)
	{
		status = execute_builtin(tokens);
		return (status);
	}

	path = build_executable_path(tokens);
	if (path != NULL)
	{
		status = execute_with_path(tokens, path, args);
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
			err1 = string_concatenate(*tokens, ": No such file or directory\n");
			err2 = string_concatenate(args, ":");
			err3 = string_concatenate(err2, err1);
			write(STDERR_FILENO, err3, string_length(err3));
			free(tokens);
			exit(EXIT_FAILURE);
		}
		return (EXIT_SUCCESS);
	}

	wait(&status);
	return (0);
}

