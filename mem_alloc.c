#include "main.h"

/**
 * _realloc - Reallocates memory for an array of strings with additional space.
 * @ptr: Pointer to the old array of strings.
 * @size: Pointer to the current number of elements in the old array.
 *
 * This function reallocates memory to create a new array that has additional space
 * compared to the old array. Specifically, the new array will have enough space to
 * accommodate the current number of elements plus an additional 10 elements.
 * The old elements are copied to the new array, and the old array is then freed.
 *
 * Return: Pointer to the new array if successful, NULL if memory allocation fails.
 */
char **_realloc(char **ptr, size_t *size)
{
	char **new; // Pointer to the new array of strings
	size_t i;   // Loop index for copying elements

	// Allocate memory for the new array with current size + 10 extra spaces
	new = malloc(sizeof(char *) * ((*size) + 10));
	if (new == NULL)
	{
		// If allocation fails, free the old array and return NULL
		free(ptr);
		return (NULL);
	}
	
	// Copy elements from the old array to the new array
	for (i = 0; i < (*size); i++)
	{
		new[i] = ptr[i];
	}
	
	// Update the size to reflect the new capacity
	*size += 10;
	
	// Free the old array since its memory has been moved to the new array
	free(ptr);
	
	// Return the pointer to the new array
	return (new);
}

