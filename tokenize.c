#include "main.h"

/**
 * tokenize - tokenizes a buffer with a delimiter
 * @buffer: string buffer to tokenize
 * @delimiter: delimiter to be used for tokenization
 *
 * Return: pointer to an array of pointers to the tokens, or NULL on failure
 */
char **tokenize(char *buffer, char *delimiter)
{
    char **tokens = NULL;
    size_t i = 0, mcount = 10;

    if (buffer == NULL || delimiter == NULL)
        return (NULL);

    tokens = malloc(sizeof(char *) * mcount);
    if (tokens == NULL)
    {
        perror("Error (Fatal)");
        return (NULL);
    }

    char *token = _strtok(buffer, delimiter);
    while (token != NULL)
    {
        tokens[i] = token;
        i++;

        if (i >= mcount)
        {
            // Increase size for tokens array
            char **new_tokens = _realloc(tokens, &mcount);
            if (new_tokens == NULL)
            {
                perror("Error (Fatal)");
                // Free allocated tokens before returning
                for (size_t j = 0; j < i; j++)
                    free(tokens[j]);
                free(tokens);
                return (NULL);
            }
            tokens = new_tokens;
        }

        token = _strtok(NULL, delimiter);
    }

    // Null-terminate the tokens array
    tokens[i] = NULL;

    return (tokens);
}

