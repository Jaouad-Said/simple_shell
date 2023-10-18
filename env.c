#include "shell.h"

/**
 * setenv - Updates or adds an environment variable.
 * @var_name: Variable name.
 * @var_value: Variable value.
 * Return: 0 on success, -1 on failure.
 */
int setenv(char *var_name, char *var_value)
{
	int i = 0;
	size_t name_len;
	char *new_var;

	name_len = string_length(var_name);
	i = 0;

	/* Update an existing variable if it exists */
	while (environ[i])
	{
		if (strncmp(environ[i], var_name, name_len) == 0)
		{
			new_var = build_variable(var_name, var_value);

			/* Clear the memory before writing */
			environ[i] = NULL;
			environ[i] = string_duplicate(new_var);

			free(environ[i]);
			environ[i] = string_duplicate(new_var);

			free(new_var);
			return (0);
		}
		i++;
	}

	/* Add a new variable if it doesn't exist */
	new_var = build_variable(var_name, var_value);
	free(environ[i]);
	environ[i] = string_duplicate(new_var);
	i++;
	environ[i] = NULL;
	new_var = NULL;

	return (0);
}

/**
 * build_variable - Builds an environment variable from its name and value.
 * @var_name: Variable name.
 * @var_value: Variable value.
 * Return: String containing the full environment variable.
 */
char *build_variable(char *var_name, char *var_value)
{
	char *new_var;
	size_t var_len;

	var_len = string_length(var_name) + string_length(var_value) + 2;
	new_var = malloc(sizeof(char) * var_len);

	if (new_var == NULL)
	{
		perror("Error: Insufficient memory\n");
		return (NULL);
	}

	memset(new_var, 0, var_len);

	/* Data in the form: var_name=var_value */
	new_var = string_concatenate(new_var, var_name);
	new_var = string_concatenate(new_var, "=");
	new_var = string_concatenate(new_var, var_value);

	return (new_var);
}

/**
 * unsetenv - Removes an environment variable.
 * @var_name: Variable name.
 * Return: 0 if successful, -1 on failure.
 */
int unsetenv(char *var_name)
{
	int i = 0;
	char **env_temp;
	size_t name_len;

	name_len = string_length(var_name);

	while (environ[i])
	{
		if (strncmp(environ[i], var_name, name_len) == 0)
		{
			env_temp = environ;
			free(env_temp[0]);

			do {
				env_temp[0] = env_temp[1];
				env_temp++;
			} while (*env_temp);
		}
		i++;
	}

	return (0);
}

