#include "main.h"

/**
 * add_key - Creates a new environment variable or updates an existing one.
 * @vars: Pointer to the structure containing environment variables and other data.
 *
 * This function allocates space for a new environment variable entry in the `vars->env` array. 
 * It adds a new environment variable or updates an existing one with the key-value pair provided 
 * in `vars->av`. After adding the new variable, the old environment array is freed.
 *
 * Return: void
 */
void add_key(vars_t *vars)
{
	unsigned int i;
	char **newenv;

	// Count the number of existing environment variables
	for (i = 0; vars->env[i] != NULL; i++)
		;

	// Allocate space for the new environment array (one additional slot for the new variable)
	newenv = malloc(sizeof(char *) * (i + 2));
	if (newenv == NULL)
	{
		// Handle memory allocation failure
		print_error(vars, NULL);
		vars->status = 127;
		custom_exit(vars);
	}

	// Copy existing environment variables to the new array
	for (i = 0; vars->env[i] != NULL; i++)
		newenv[i] = vars->env[i];

	// Add the new key-value pair to the new environment array
	newenv[i] = add_value(vars->av[1], vars->av[2]);
	if (newenv[i] == NULL)
	{
		// Handle failure to create the new environment variable
		print_error(vars, NULL);
		free(vars->buffer);
		free(vars->commands);
		free(vars->av);
		free_env(vars->env);
		free(newenv);
		exit(127);
	}
	newenv[i + 1] = NULL;

	// Replace old environment array with the new one
	free(vars->env);
	vars->env = newenv;
}

/**
 * find_key - Searches for an environment variable in the environment array.
 * @env: Array of environment variables.
 * @key: Name of the environment variable to find.
 *
 * This function searches through the environment array to find the environment variable with the 
 * specified key. It returns a pointer to the address of the environment variable if found.
 *
 * Return: Pointer to the address of the environment variable, or NULL if not found.
 */
char **find_key(char **env, char *key)
{
	unsigned int i, j, len;

	// Get the length of the key to search for
	len = _strlen(key);
	for (i = 0; env[i] != NULL; i++)
	{
		// Check if the beginning of the environment variable matches the key
		for (j = 0; j < len; j++)
			if (key[j] != env[i][j])
				break;

		// If the full key matches and the next character is '=', return the address
		if (j == len && env[i][j] == '=')
			return (&env[i]);
	}
	return (NULL);
}

/**
 * add_value - Constructs a new environment variable string.
 * @key: Name of the environment variable.
 * @value: Value of the environment variable.
 *
 * This function creates a new string that represents an environment variable in the format 
 * "key=value". It allocates sufficient memory for the new string and copies the key and value 
 * into the string.
 *
 * Return: Pointer to the new string, or NULL if memory allocation fails.
 */
char *add_value(char *key, char *value)
{
	unsigned int len1, len2, i, j;
	char *new;

	// Get the lengths of the key and value
	len1 = _strlen(key);
	len2 = _strlen(value);

	// Allocate memory for the new string (key + '=' + value + '\0')
	new = malloc(sizeof(char) * (len1 + len2 + 2));
	if (new == NULL)
		return (NULL);

	// Copy the key into the new string
	for (i = 0; key[i] != '\0'; i++)
		new[i] = key[i];
	new[i] = '=';

	// Copy the value into the new string
	for (j = 0; value[j] != '\0'; j++)
		new[i + 1 + j] = value[j];
	new[i + 1 + j] = '\0';

	return (new);
}

/**
 * _atoi - Converts a string to an integer.
 * @str: String to convert.
 *
 * This function converts a string representation of an integer to its integer value. It performs
 * validation to ensure the string represents a valid integer within the range of `int`. 
 * If the string is not a valid integer or exceeds the range, it returns -1.
 *
 * Return: The integer value of the string, or -1 if the conversion fails.
 */
int _atoi(char *str)
{
	unsigned int i, digits;
	int num = 0, num_test;

	// Calculate the number of digits in the maximum int value
	num_test = INT_MAX;
	for (digits = 0; num_test != 0; digits++)
		num_test /= 10;

	// Convert the string to an integer with validation
	for (i = 0; str[i] != '\0' && i < digits; i++)
	{
		num *= 10;
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		if ((i == digits - 1) && (str[i] - '0' > INT_MAX % 10))
			return (-1);
		num += str[i] - '0';
		if ((i == digits - 2) && (str[i + 1] != '\0') && (num > INT_MAX / 10))
			return (-1);
	}
	if (i > digits)
		return (-1);
	return (num);
}

