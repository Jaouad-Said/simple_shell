#include "shell.h"

/**
 * prompt - Displays a shell prompt to the user.
 *
 * This function checks if the standard input is a terminal (interactive mode)
 * and then displays the shell prompt "#cisfun$ " if it is.
 *
 * Return: Void.
 */
void prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, "#cisfun$ ", 9);
	}
}

