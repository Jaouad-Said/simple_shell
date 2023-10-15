#include "shell.h"

/**
 * is_delimiter - Checks if a character is a delimiter.
 * @c: The character to check.
 * @delim: A string containing delimiters.
 * Return: 1 if 'c' is a delimiter, 0 otherwise.
 */
int is_delimiter(char c, const char *delim)
{
    while (delim && *delim)
    {
        if (c == *delim)
        {
            return 1;
        }
        ++delim;
    }
    return 0;
}

/**
 * custom_strtok - Custom implementation of strtok, which tokenizes a string.
 * @src: The string to tokenize.
 * @delim: A string containing delimiters.
 * Return: Pointer to the next token or NULL if no more tokens are found.
 */
char *custom_strtok(char *src, const char *delim)
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
            if (is_delimiter(s[i], delim))
                s[i] = '\0';
        }
    }

    if (s == NULL || *s == '\0')
        return NULL;
    result = s;
    i = string_length(s);
    if (s[i] == '\0' && string_length(s) > 0)
        is_space = 1;
    s = s + string_length(s) + is_space;
    return result;
}

/**
 * ctrl_c_handler - Handles the Ctrl+C signal.
 * @signum: The signal number received (unused in this function).
 */
void ctrl_c_handler(int signum)
{
    (void)signum;
    write(STDOUT_FILENO, "\n#cisfun$ ", 10);
}

/**
 * read_line - Reads a line from standard input and stores it in a malloced buffer.
 * @str: Pointer to the buffer where the line will be stored.
 * Return: Number of characters read or -1 on error.
 */
ssize_t read_line(char **str)
{
    ssize_t i = 0, size = 0, t = 0, t2 = 0, n = 0;
    char buffer[1024];

    while (t2 == 0 && (i = read(STDIN_FILENO, buffer, 1024 - 1)))
    {
        if (i == -1)
            return -1;

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
            *str = string_copy(*str, buffer);
            size = i;
            t = 1;
        }
        else
        {
            size += i;
            *str = string_concatenate(*str, buffer);
        }
    }
    
    return size;
}

/**
 * string_copy - Duplicates a string.
 * @str: The string to duplicate.
 * Return: Pointer to the duplicated string in allocated memory.
 */
char *string_copy(char *str)
{
    char *duplicate_str;
    int i, len = 0;

    if (str == NULL)
        return NULL;
    while (str[len])
        len++;
    len++; /* Add null terminator to length */
    duplicate_str = malloc(sizeof(char) * len);
    if (duplicate_str == NULL)
        return NULL;
    i = 0;
    while (i < len)
    {
        duplicate_str[i] = str[i];
        i++;
    }
    return duplicate_str;
}

