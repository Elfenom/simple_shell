#include "main.h"

/**
 * path_exec - Executes a command located at a specified path.
 * @command: The full path to the command to be executed.
 * @vars: Pointer to a struct of variables used by the shell.
 *
 * This function checks if the command at the given path is executable. If so,
 * it forks a child process to execute the command using `execve`. The parent 
 * process waits for the child process to complete and updates the status of 
 * the command execution.
 *
 * Return: 0 on success, 1 on failure.
 */
int path_exec(char *command, vars_t *vars)
{
	pid_t child_pid;

	// Check if the command is executable
	if (access(command, X_OK) == 0)
	{
		child_pid = fork();  // Create a child process
		if (child_pid == -1)
			print_error(vars, NULL);  // Print error if fork fails

		if (child_pid == 0)
		{
			// Child process: execute the command
			if (execve(command, vars->av, vars->env) == -1)
				print_error(vars, NULL);  // Print error if execve fails
		}
		else
		{
			// Parent process: wait for the child to complete
			wait(&vars->status);
			if (WIFEXITED(vars->status))
				vars->status = WEXITSTATUS(vars->status);  // Get exit status
			else if (WIFSIGNALED(vars->status) && WTERMSIG(vars->status) == SIGINT)
				vars->status = 130;  // Handle interrupt signal

			return (0);  // Return success
		}
		vars->status = 127;  // Command not found
		return (1);  // Return failure
	}
	else
	{
		print_error(vars, ": Permission denied\n");  // Print permission denied error
		vars->status = 126;  // Permission denied
	}
	return (0);  // Return failure
}

/**
 * find_path - Retrieves the PATH variable from the environment.
 * @env: Array of environment variables.
 *
 * This function searches the environment variables for the PATH variable.
 *
 * Return: Pointer to the PATH variable string, or NULL if not found.
 */
char *find_path(char **env)
{
	char *path = "PATH=";
	unsigned int i, j;

	// Search for the PATH variable in the environment
	for (i = 0; env[i] != NULL; i++)
	{
		for (j = 0; j < 5; j++)
			if (path[j] != env[i][j])
				break;
		if (j == 5)
			break;
	}
	return (env[i]);  // Return pointer to the PATH variable
}

/**
 * check_for_path - Checks if the command can be found in the PATH.
 * @vars: Pointer to the struct of variables used by the shell.
 *
 * This function checks if the command is an absolute or relative path. If not,
 * it searches through the directories listed in the PATH environment variable.
 *
 * Return: void
 */
void check_for_path(vars_t *vars)
{
	char *path, *path_dup = NULL, *check = NULL;
	unsigned int i = 0, r = 0;
	char **path_tokens;
	struct stat buf;

	// Check if the command is already a path
	if (check_for_dir(vars->av[0]))
		r = execute_cwd_cmd(vars);  // Execute if it's a path
	else
	{
		// Find the PATH environment variable
		path = find_path(vars->env);
		if (path != NULL)
		{
			path_dup = _strdup(path + 5);  // Duplicate the PATH variable
			path_tokens = tokenize(path_dup, ":");  // Tokenize the PATH

			// Iterate through each directory in the PATH
			for (i = 0; path_tokens && path_tokens[i]; i++, free(check))
			{
				check = _strcat(path_tokens[i], vars->av[0]);  // Create full path to the command
				if (stat(check, &buf) == 0)
				{
					r = path_exec(check, vars);  // Execute the command
					free(check);
					break;
				}
			}

			free(path_dup);
			if (path_tokens == NULL)
			{
				vars->status = 127;  // PATH tokenization failed
				custom_exit(vars);
			}
		}
		if (path == NULL || path_tokens[i] == NULL)
		{
			print_error(vars, ": Not found\n");  // Command not found in PATH
			vars->status = 127;
		}
		free(path_tokens);
	}
	if (r == 1)
		custom_exit(vars);  // Exit if comm

