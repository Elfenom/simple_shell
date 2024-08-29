#include "main.h"

/**
 * _puts - writes a string to standard output
 * @str: string to write
 *
 * Return: number of chars printed or -1 on failure
 */
ssize_t _puts(char *str)
{
    ssize_t len;

    len = _strlen(str);
    if (write(STDOUT_FILENO, str, len) != len)
    {
        perror("Fatal Error");
        return (-1);
    }
    return (len);
}

/**
 * _strdup - returns a pointer to a new memory allocation which contains a copy
 * @strtodup: string to be duplicated
 *
 * Return: pointer to the new duplicated string, or NULL if allocation fails
 */
char *_strdup(const char *strtodup)
{
    char *copy;
    int len, i;

    if (strtodup == NULL)
        return (NULL);

    len = _strlen((char *)strtodup);
    copy = malloc((len + 1) * sizeof(char));
    if (copy == NULL)
        return (NULL);

    for (i = 0; i <= len; i++)
        copy[i] = strtodup[i];

    return (copy);
}

/**
 * _strcmpr - compares two strings
 * @strcmp1: first string to be compared
 * @strcmp2: second string to be compared
 *
 * Return: 0 if strings are equal, negative if strcmp1 < strcmp2, positive otherwise
 */
int _strcmpr(const char *strcmp1, const char *strcmp2)
{
    while (*strcmp1 && (*strcmp1 == *strcmp2))
    {
        strcmp1++;
        strcmp2++;
    }
    return (*(unsigned char *)strcmp1 - *(unsigned char *)strcmp2);
}

/**
 * _strcat - concatenates two strings
 * @strc1: first string
 * @strc2: second string
 *
 * Return: pointer to the newly allocated concatenated string, or NULL if allocation fails
 */
char *_strcat(const char *strc1, const char *strc2)
{
    char *newstring;
    unsigned int len1, len2, newlen, i, j;

    if (strc1 == NULL)
        len1 = 0;
    else
        len1 = _strlen((char *)strc1);

    if (strc2 == NULL)
        len2 = 0;
    else
        len2 = _strlen((char *)strc2);

    newlen = len1 + len2 + 1;
    newstring = malloc(newlen * sizeof(char));
    if (newstring == NULL)
        return (NULL);

    for (i = 0; i < len1; i++)
        newstring[i] = strc1[i];
    
    for (j = 0; j < len2; j++)
        newstring[i + j] = strc2[j];
    
    newstring[len1 + len2] = '\0';

    return (newstring);
}

/**
 * _strlen - returns the length of a string
 * @str: string to be measured
 *
 * Return: length of string
 */
unsigned int _strlen(const char *str)
{
    unsigned int len = 0;

    while (str[len])
        len++;

    return (len);
}

