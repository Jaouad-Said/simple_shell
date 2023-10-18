#include "shell.h"

/**
 * is_delim - Checks if a character is a delimiter.
 * @c: The character to check.
 * @delim: A string containing delimiters.
 * Return: 1 if 'c' is a delimiter, 0 otherwise.
 */
int is_delim(char c, const char *delim)
{
	while (delim && *delim)
	{
		if (c == *delim)
		{
			return (1);
		}
		++delim;
	}
	return (0);
}

/**
 * _strtok - Custom implementation of strtok, which tokenizes a string.
 * @src: The string to tokenize.
 * @delim: A string containing delimiters.
 * Return: Pointer to the next token or NULL if no more tokens are found.
 */
char *_strtok(char *src, const char *delim)
{
	static char *s;
	static unsigned int i;
	char *result = NULL;
	int is_space = 0;

	if (src)
	{
		s = src;
		for (i = 0; s[i]; i++)
		{
			if (is_delim(s[i], delim))
				s[i] = '\0';
		}
	}

	if (s == NULL || *s == '\0')
		return (NULL);
	result = s;
	i = _strlen(s);
	if (s[i] == '\0' && _strlen(s) > 0)
		is_space = 1;
	s = s + _strlen(s) + is_space;
	return (result);
}

/**
 * ctrlc - Handles the Ctrl+C signal.
 * @signum: The signal number received (unused in this function).
 */
void ctrlc(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n#cisfun$ ", 10);
}

/**
 * get_line - Reads a line from input and stores it in a malloced buffer.
 * @str: Pointer to the buffer where the line will be stored.
 * Return: Number of characters read or -1 on error.
 */
ssize_t get_line(char **str)
{
	ssize_t i = 0, size = 0, t = 0, t2 = 0, n = 0;
	char buffer[1024];

	while (t2 == 0 && (i = read(STDIN_FILENO, buffer, 1024 - 1)))
	{
		if (i == -1)
			return (-1);

		buffer[i] = '\0';

		n = 0;
		while (buffer[n] != '\0')
		{
			if (buffer[n] == '\n')
				t2 = 1;
			n++;
		}

		if (t == 0)
		{
			i++;
			*str = malloc(sizeof(char) * i);
			*str = _strcpy(*str, buffer);
			size = i;
			t = 1;
		}
		else
		{
			size += i;
			*str = _strcat(*str, buffer);
		}
	}

	return (size);
}

/**
 * _strdup - Duplicates a string.
 * @str: The string to duplicate.
 * Return: Pointer to the duplicated string in allocated memory.
 */
char *_strdup(char *str)
{
	char *duplicate_str;
	int i, len = 0;

	if (str == NULL)
		return (NULL);
	while (str[len])
		len++;
	len++; /* Add null terminator to length */
	duplicate_str = malloc(sizeof(char) * len);
	if (duplicate_str == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		duplicate_str[i] = str[i];
		i++;
	}
	return (duplicate_str);
}

