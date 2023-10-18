#include "shell.h"

/**
  * _printenv - Displays the current working environment's variables.
  * Return: void.
  */
void _printenv(void)
{
	int i = 0;

	while (environ[i])
	{
		print_string(environ[i]);
		i++;
	}
}

/**
 * _isBuiltIn - Checks if a given token represents a built-in shell command.
 * @str: Pointer to the string to check.
 * Return: 0 if it's a built-in command, else 1.
 */
int _isBuiltIn(char *str)
{
    /* Compare the string with known built-in commands */
	if ((_strcmp(str, "env")) == 0)
	{
		return (0);
	}
	if ((_strcmp(str, "exit")) == 0)
		return (0);
	if ((_strcmp(str, "setenv")) == 0)
		return (0);
	if ((_strcmp(str, "unsetenv")) == 0)
		return (0);
	return (1);
}

/**
 * _executeBuiltIn - Executes a built-in shell function.
 * @tokens: Double pointer to command tokens.
 * Return: 0 if the execution is successful.
 */
int _executeBuiltIn(char **tokens)
{
    /* Check if the first token corresponds to a built-in command */
	if ((_strcmp(*tokens, "env")) == 0)
	{
		_printenv();
		return (0);
	}
	if ((_strcmp(*tokens, "setenv")) == 0)
	{
		/* Check if the user provides the correct format */
		if (tokens[1] && tokens[2])
		{
			_setenv(tokens[1], tokens[2]);
			return (0);
		}
		/* Otherwise, print an error message */
		printf("Usage: setenv var_name var_value\n");
		return (0);
	}
	if (_strcmp(*tokens, "unsetenv") == 0)
	{
		/* Check for VAR_NAME to unset */
		if (tokens[1])
		{
			_unsetenv(tokens[1]);
			return (0);
		}
		/* Otherwise, display an error message */
		printf("Usage: unsetenv VAR_NAME\n");
		return (0);
	}

	/* Code path should not be reached */
	return (1);
}

/**
 * _exitSimpleShell - Exits the shell and frees allocated memory.
 * @tokens: Double pointer to words split from the command line.
 * @line: Pointer to the string obtained using getLine().
 * Return: void.
 */
void _exitSimpleShell(char **tokens, char *line)
{
	int status;

	if (tokens[1] != NULL)
	{
		status = atoi(tokens[1]);
		if (status >= 0)
		{
			free(line);
			free(tokens);
			exit(status);
		}
		write(STDERR_FILENO, "Exit: illegal exit status: ", 28);
		write(STDERR_FILENO, tokens[1], 1);
		write(STDERR_FILENO, "\n", 1);
	}
	else
	{
		free(line);
		free(tokens);
		exit(0);
	}
}

