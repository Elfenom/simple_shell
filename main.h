#ifndef _MAIN_H_
#define _MAIN_H_

#include <unistd.h>    // Provides access to the POSIX operating system API
#include <stdio.h>     // Standard input/output functions
#include <stdlib.h>    // Standard library functions (e.g., memory allocation)
#include <string.h>    // String manipulation functions
#include <sys/types.h> // Definitions for data types used in system calls
#include <sys/wait.h>  // Declarations for process control
#include <sys/stat.h>  // Definitions for file status
#include <limits.h>    // Limits of integer types
#include <signal.h>    // Definitions for signal handling

/**
 * struct variables - A structure to hold various variables for shell operations
 * @av: Array of command line arguments (e.g., from a user command)
 * @buffer: Buffer to hold the input command
 * @env: Array of environment variables
 * @count: Count of commands entered (used for error messages)
 * @argv: Arguments used at the shell's opening
 * @status: Exit status of the last executed command
 * @commands: Array of commands parsed from the input
 */
typedef struct variables
{
	char **av;        // Command line arguments
	char **argv;      // Arguments at the opening of the shell
	char *buffer;     // Input command buffer
	char **commands; // Array of parsed commands
	char **env;       // Environment variables
	size_t count;     // Command count (for error reporting)
	int status;       // Exit status of the last command
} vars_t;

/**
 * struct builtins - A structure to map built-in commands to their handler functions
 * @name: Name of the built-in command (e.g., "exit", "env")
 * @f: Function pointer to the handler for the built-in command
 */
typedef struct builtins
{
	char *name;       // Built-in command name
	void (*f)(vars_t *); // Pointer to the function handling the built-in command
} builtins_t;

/* Environment variable management functions */
char **create_env(char **env);    // Creates a copy of the environment
void free_env(char **env);        // Frees the environment variables array

/* Utility functions */
ssize_t _puts(char *str);         // Custom function to write a string
char *_strdup(char *strtodup);    // Duplicates a string
int _strcmpr(char *strcmp1, char *strcmp2); // Compares two strings
char *_strcat(char *strc1, char *strc2);     // Concatenates two strings
unsigned int _strlen(char *str); // Gets the length of a string

/* Tokenization functions */
char **tokenize(char *buf, char *delimiter); // Tokenizes a string
char **_realloc(char **ptr, size_t *size);    // Reallocates memory for an array of strings
char *_strtok(char *str, const char *delim);  // Custom string tokenizer

/* Path handling functions */
void check_for_path(vars_t *vars);  // Checks and executes command found in PATH
char *find_path(char **env);        // Finds the PATH environment variable
int path_exec(char *command, vars_t *vars); // Executes a command located in PATH
int execute_cwd_cmd(vars_t *vars); // Executes a command in the current working directory
int check_for_dir(char *str);      // Checks if a command includes a directory

/* Environment handlers */
void (*check_for_builtins(vars_t *vars))(vars_t *vars); // Checks and returns a built-in command function
void custom_exit(vars_t *vars); // Handles the exit built-in command
void _env(vars_t *vars);        // Handles the env built-in command
void _setenv(vars_t *vars);     // Handles the setenv built-in command
void _unsetenv(vars_t *vars);   // Handles the unsetenv built-in command

/* File Finder functions */
void add_key(vars_t *vars);     // Adds a key to the environment
char **find_key(char **env, char *key); // Finds a key in the environment
char *add_value(char *key, char *value); // Adds a value for a key in the environment
int _atoi(char *str);           // Converts a string to an integer

/* Error handling functions */
void print_error(vars_t *vars, char *msg); // Prints error messages
void _puts2(char *str); // Custom function to write a string to standard error
char *_uitoa(unsigned int count); // Converts an unsigned integer to a string

#endif // _MAIN_H_

