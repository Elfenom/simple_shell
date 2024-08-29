#include "main.h"

/**
 * create_env - Creates a copy of the shell environment.
 * @env: The environment variables passed to the main function.
 *
 * This function allocates memory for a new environment array and duplicates
 * each string from the provided environment array into this new array.
 *
 * Return: A pointer to the newly created environment array.
 */
char **create_env(char **env)
{
	char **newenv = NULL;  // Pointer to the new environment array
	size_t i;

	// Count the number of environment variables
	for (i = 0; env[i] != NULL; i++)
		;

	// Allocate memory for the new environment array
	newenv = malloc(sizeof(char *) * (i + 1));
	if (newenv == NULL)
	{
		perror("Fatal Error");  // Print an error message if memory allocation fails
		exit(1);  // Exit the program with an error code
	}

	// Duplicate each environment variable into the new array
	for (i = 0; env[i] != NULL; i++)
		newenv[i] = _strdup(env[i]);

	// Null-terminate the new environment array
	newenv[i] = NULL;

	return (newenv);  // Return the pointer to the new environment array
}

/**
 * free_env - Frees the memory allocated for the shell environment.
 * @env: The environment array to free.
 *
 * This function deallocates the memory used by the environment array and
 * its individual strings.
 *
 * Return: void
 */
void free_env(char **env)
{
	unsigned int i;

	// Free each string in the environment array
	for (i = 0; env[i] != NULL; i++)
		free(env[i]);

	// Free the array itself
	free(env);
}

