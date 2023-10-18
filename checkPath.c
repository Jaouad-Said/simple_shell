#include "shell.h"

/**
 * if_file_exists - Checks the status of a file.
 * @s: Pointer to the file name.
 * Return: 0 if the file exists, else a non-zero value.
 */
int if_file_exists(char *s)
{
	struct stat st;

	return (stat(s, &st));
}

/**
 * path_builder - Constructs a path to binary executables.
 * @tokens: Double pointer to tokens.
 * Return: Returns the constructed path or NULL if not found.
 */
char *path_builder(char **tokens)
{
	char path1[100] = "/bin/";
	char path2[100] = "/usr/bin/";

	char *finalPath1;
	char *finalPath2;

	finalPath1 = _strcat(path1, tokens[0]);

	if ((if_file_exists(finalPath1) == 0))
		return (finalPath1);
	finalPath2 = _strcat(path2, tokens[0]);
	if ((if_file_exists(finalPath2) == 0))
		return (finalPath2);

	return (NULL);
}

/**
 * execute_with_path - Executes a file with a specified path.
 * @tokens: Split string into tokens from stdin.
 * @path: Path obtained from path_builder function.
 * @args: Program arguments.
 * Return: 0 on success, else 1.
 */
int execute_with_path(char **tokens, char *path, char *args)
{
	char *error_msg1, *error_msg2, *error_msg3;
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error: ");
		return (1);
	}

	if (child_pid == 0)
	{
		tokens[0] = path;

		if (execve(tokens[0], tokens, NULL) == -1)
		{
			error_msg1 = _strcat(*tokens, ": No such file or directory\n");
			error_msg2 = _strcat(args, ":");
			error_msg3 = _strcat(error_msg2, error_msg1);
			write(STDERR_FILENO, error_msg3, _strlen(error_msg3));
			free(tokens);
			exit(EXIT_FAILURE);
		}
		return (EXIT_SUCCESS);
	}

	wait(&status);
	return (EXIT_SUCCESS);
}

