#include "main.h"

/**
 * check_match - Checks if a character is present in a string.
 * @c: Character to check.
 * @str: String to check against.
 *
 * Return: 1 if the character matches any in the string, 0 otherwise.
 */
unsigned int check_match(char c, const char *str)
{
    unsigned int i;

    // Iterate through each character in the string to check for a match
    for (i = 0; str[i] != '\0'; i++)
    {
        if (c == str[i])
            return (1);  // Return 1 if a match is found
    }
    return (0);  // Return 0 if no match is found
}

/**
 * _strtok - Tokenizes a string using a delimiter.
 * @str: String to tokenize. If NULL, it continues tokenizing from the last position.
 * @delim: Delimiter string containing characters used for tokenizing.
 *
 * Return: Pointer to the next token in the string, or NULL if no more tokens.
 */
char *_strtok(char *str, const char *delim)
{
    static char *token_start;  // Start of the current token
    static char *next_token;   // Next token position
    unsigned int i;

    // If a new string is provided, set the start of the next token to it
    if (str != NULL)
        next_token = str;
    
    token_start = next_token;  // Set the start of the current token

    // If there are no tokens left, return NULL
    if (token_start == NULL)
        return (NULL);

    // Find the start of the next token by skipping delimiter characters
    for (i = 0; next_token[i] != '\0'; i++)
    {
        if (check_match(next_token[i], delim) == 0)
            break;
    }

    // If we reached the end of the string or encountered a '#', return NULL
    if (next_token[i] == '\0' || next_token[i] == '#')
    {
        next_token = NULL;
        return (NULL);
    }

    // Set the start of the current token
    token_start = next_token + i;
    next_token = token_start;

    // Find the end of the current token by looking for delimiter characters
    for (i = 0; next_token[i] != '\0'; i++)
    {
        if (check_match(next_token[i], delim) == 1)
            break;
    }

    // If the end of the string is reached, set 

