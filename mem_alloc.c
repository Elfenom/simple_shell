#include "main.h"


/**
 * _realloc - reallocates a pointer to double the spaces
 * @ptr: the pointer to the old array
 * @size: the  pointer to number of elements in the old array
 *
 * Return: the pointer to the new array
 */


char **_realloc(char **ptr, size_t *size)
{
	char **new;
	size_t i;

	new = malloc(sizeof(char *) * ((*size) + 10));
	if (new == NULL)
	{
		free(ptr);
		return (NULL);
	}
	for (i = 0; i < (*size); i++)
	{
		new[i] = ptr[i];
	}
	*size += 10;
	free(ptr);
	return (new);
}
