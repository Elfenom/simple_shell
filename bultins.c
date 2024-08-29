#include "main.h"

/**
 * check_for_builtins - Checks if the given command is a builtin command.
 * @vars: Pointer to the structure containing variables and arguments.
 *
 * Return: Pointer to the function associated with the builtin command, or NULL if not found.
 */
void (*check_for_builtins(vars_t *vars))(vars_t *vars)
{
    unsigned int i;
    builtins_t check[] = {
        {"exit", custom_exit},
        {"env", _env},
        {"setenv", _setenv},
        {"unsetenv", _unsetenv},
        {NULL, NULL}  // End of the builtins list
    };

    // Iterate through the list of builtins to find a match
    for (i = 0; check[i].f != NULL; i++)
    {
        if (_strcmpr(vars->av[0], check[i].name) == 0)
            break;
    }
    
    // If a matching builtin is found, return its function pointer
    if (check[i].f != NULL)
        check[i].f(vars);
    return (check[i].f);
}

/**
 * custom_exit - Exits the program with a given status.
 * @vars: Pointer to the structure containing variables and arguments.
 *
 * Return: void
 */
void custom_exit(vars_t *vars)
{
    int status;

    // If the command is "exit" and an argument is provided
    if (_strcmpr(vars->av[0], "exit") == 0 && vars->av[1] != NULL)
    {
        status = _atoi(vars->av[1]);
        if (status == -1)
        {
            vars->status = 2;
            print_error(vars, ": Illegal number: ");
            _puts2(vars->av[1]);
            _puts2("\n");
            free(vars->commands);
            vars->commands = NULL;
            return;
        }
        vars->status = status;
    }
    
    // Free allocated memory and exit the program with the status code
    free(vars->buffer);
    free(vars->av);
    free(vars->commands);
    free_env(vars->env);
    exit(vars->status);
}

/**
 * _env - Prints the current environment variables.
 * @vars: Pointer to the structure containing variables and arguments.
 *
 * Return: void
 */
void _env(vars_t *vars)
{
    unsigned int i;

    // Iterate through environment variables and print each
    for (i = 0; vars->env[i]; i++)
    {
        _puts(vars->env[i]);
        _puts("\n");
    }
    vars->status = 0;
}

/**
 * _setenv - Creates or updates an environment variable.
 * @vars: Pointer to the structure containing variables and arguments.
 *
 * Return: void
 */
void _setenv(vars_t *vars)
{
    char **key;
    char *var;

    // Check if the correct number of arguments is provided
    if (vars->av[1] == NULL || vars->av[2] == NULL)
    {
        print_error(vars, ": Incorrect number of arguments\n");
        vars->status = 2;
        return;
    }
    
    // Find the key in the environment variables
    key = find_key(vars->env, vars->av[1]);
    if (key == NULL)
        add_key(vars);
    else
    {
        // Add or update the environment variable value
        var = add_value(vars->av[1], vars->av[2]);
        if (var == NULL)
        {
            print_error(vars, NULL);
            free(vars->buffer);
            free(vars->commands);
            free(vars->av);
            free_env(vars->env);
            exit(127);
        }
        free(*key);
        *key = var;
    }
    vars->status = 0;
}

/**
 * _unsetenv - Removes an environment variable.
 * @vars: Pointer to the structure containing variables and arguments.
 *
 * Return: void
 */
void _unsetenv(vars_t *vars)
{
    char **key, **newenv;

    unsigned int i, j;

    // Check if the correct number of arguments is provided
    if (vars->av[1] == NULL)
    {
        print_error(vars, ": Incorrect number of arguments

