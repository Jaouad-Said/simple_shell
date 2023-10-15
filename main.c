#include "shell.h"

/**
 * main - Entry point for the Simple Shell program.
 *
 * @argc: Number of arguments.
 * @argv: Pointer to an array of arguments.
 *
 * Return: Always returns 0 if the program runs successfully, otherwise 1.
 */
int main(int argc, char *argv[])
{
	char *line;
	int status;
	char **tokens;

	(void)argc;

	signal(SIGINT, ctrlc);
	status = 0;

	while (status == 0)
	{
		prompt();
		line = read_line();

		if (_strcmp(line, "\n") == 0)
		{
			tokens = NULL;
			free(line);
			continue;
		}
		tokens = _strtotokens(line);

		if (tokens[0] == NULL)
		{
			free(tokens);
			free(line);
			continue;
		}
		if (_strcmp(tokens[0], "exit") == 0)
		{
			exit_simple_shell(tokens, line);
		}
		else
		{
			status = run(tokens, argv[0]);
		}
		free(line);
		free(tokens);
	}
	return (status);
}

