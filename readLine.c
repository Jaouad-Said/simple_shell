#include "shell.h"

/**
 * read_line - Reads a line of text from standard input.
 *
 * This function reads a line of text from the standard input (stdin)
 * and returns it as a dynamically allocated string. It uses the getline
 * function to allocate memory for the line and reads characters from stdin
 * until a newline character is encountered or the end of the file is reached.
 * If the input is an empty line, it returns an empty string.
 *
 * Return: A pointer to the line of text (string) or NULL on failure.
 */
char *read_line(void)
{
	char *line = NULL;   /* Pointer to the line (string). */
	size_t size = 0;     /* Initial size of the buffer. */
	ssize_t numOfChars = 0; /* Number of characters read. */

	numOfChars = getline(&line, &size, stdin);

	if (numOfChars == EOF)
	{
		free(line);
		exit(0);
	}

	if (line == NULL)
	{
		write(STDOUT_FILENO, "\n", 1);
		free(line);
		exit(-1);
	}

	return (line);
}

