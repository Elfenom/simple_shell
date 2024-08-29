#include "main.h"

/**
 * print_error - Prints error messages to standard error.
 * @vars: Pointer to the structure of variables containing context.
 * @msg: Message to print after the error code. If NULL, `perror` is used.
 *
 * Return: void
 */
void print_error(vars_t *vars, char *msg)
{
    char *count;

    // Print the name of the command or program
    _puts2(vars->argv[0]);
    _puts2(": ");
    
    // Convert the error count to a string and print it
    count = _uitoa(vars->count);
    _puts2(count);
    free(count); // Free the allocated memory for the string representation of the count
    
    _puts2(": ");
    _puts2(vars->av[0]); // Print the specific command or part of the command causing the error
    
    // Print the provided message or use perror to print the error based on errno
    if (msg)
    {
        _puts2(msg);
    }
    else
    {
        perror(""); // Print a system error message based on errno
    }
}

/**
 * _puts2 - Prints a string to standard error.
 * @str: The string to print.
 *
 * Return: void
 */
void _puts2(char *str)
{
    ssize_t num, len;

    // Get the length of the string
    num = _strlen(str);
    // Write the string to standard error (file descriptor STDERR_FILENO)
    len = write(STDERR_FILENO, str, num);
    
    // Check if the write operation was successful
    if (len != num)
    {
        perror("Fatal Error!"); // Print an error message if the write operation fails
        exit(1); // Exit with status code 1 indicating a fatal error
    }
}

/**
 * _uitoa - Converts an unsigned int to a string.
 * @count: The unsigned int to convert.
 *
 * Return: Pointer to the string representation of the number.
 */
char *_uitoa(unsigned int count)
{
    char *numstr;
    unsigned int tmp, digits;

    // Calculate the number of digits in the number
    tmp = count;
    for (digits = 0; tmp != 0; digits++)
        tmp /= 10;
    
    // Allocate memory for the string representation of the number (plus null terminator)
    numstr = malloc(sizeof(char) * (digits + 1));
    if (numstr == NULL)
    {
        perror("Fatal Error!"); // Print an error message if memory allocation fails
        exit(127); // Exit with status code 127 indicating memory allocation failure
    }
    
    numstr[digits] = '\0'; // Null-terminate the string
    for (--digits; count > 0; --digits)
    {
        numstr[digits] = (count % 10) + '0'; // Convert last digit to character and store it
        count /= 10; // Remove the last digit from the number
    }
    
    // Handle the case where the number is zero (which would not be covered in the loop)
    if (count == 0)
        numstr[0] = '0';

    return (numstr); // Return the string representation of the number
}

