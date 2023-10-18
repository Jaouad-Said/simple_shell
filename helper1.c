#include "shell.h"

/**
 * _strlen - Returns the length of a string.
 * @s: Pointer to the string.
 *
 * Return: Length of s.
 */
int _strlen(char *s)
{
	int index = 0;

	while (s[index] != '\0')
	{
		index++;
	}

	return (index);
}

/**
 * _strcat - Concatenates two strings.
 * @dest: Pointer to the destination string.
 * @src: Pointer to the source string to append to dest.
 *
 * Return: Pointer to dest.
 */
char *_strcat(char *dest, char *src)
{
	char *destAddress = dest;
	int destLen = _strlen(dest);

	destAddress = destAddress + destLen;

	while (*src != '\0')
	{
		*destAddress = *src;
		src++;
		destAddress++;
	}

	*destAddress = '\0';

	return (dest);
}

/**
 * count_white_space - Counts white space characters in a string.
 * @s: Pointer to the string to check.
 *
 * Return: The number of white space characters.
 */
unsigned int count_white_space(char *s)
{
	int i, count = 0;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		count++;
	}

	return (count);
}

/**
 * _strtotokens - Splits a string into words.
 * @str: Pointer to the string.
 *
 * Return: Pointer to an array of words.
 */
char **_strtotokens(char *str)
{
	int i = 0;
	const char delimiter[] = " \t\n";
	int space = count_white_space(str);
	char **tokens = malloc(sizeof(char *) * (space + 1));
	char *token;

	if (!tokens)
	{
		free(tokens);
		fprintf(stderr, "sh: allocation error\n");
		exit(1);
	}

	token = strtok(str, delimiter);

	while (token != NULL)
	{
		tokens[i] = token;
		token = strtok(NULL, delimiter);
		i++;
	}

	tokens[i] = NULL;

	return (tokens);
}

/**
 * print_string - Prints a string, followed by a new line, to stdout.
 * @str: The string to print.
 */
void print_string(char *str)
{
	unsigned long i = 0;

	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}

	_putchar('\n');
}

