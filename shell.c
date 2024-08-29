#include "main.h"

/* global variable for ^C handling */
unsigned int sig_flag;

/**
 * sig_handler - handles ^C signal interrupt
 * @unused_var: unused variable (required for signal function prototype)
 *
 * This signal handler function is invoked when the SIGINT signal is received.
 * It handles ^C (Ctrl+C) interrupts by printing a new line and a prompt 
 * depending on whether the prompt was already displayed or not.
 *
 * Return: void
 */
static void sig_handler(int unused_var)
{
	(void) unused_var;
	if (sig_flag == 0)
		_puts("\n$ ");
	else
		_puts("\n");
}

/**
 * main - main function for the shell
 * @argc: number of arguments passed to main (unused)
 * @argv: array of arguments passed to main
 * @environment: array of environment variables
 *
 * This function initializes the shell environment, sets up signal handling,
 * and enters the main loop to read and execute commands from standard input.
 *
 * Return: 0 on success or exit status
 */
int main(int argc __attribute__((unused)), char **argv, char **environment)
{
	size_t len_buffer = 0;
	unsigned int is_pipe = 0, i;
	vars_t vars = {NULL, NULL, NULL, NULL, NULL, 0, 0};

	// Initialize the variables struct with the command-line arguments and environment
	vars.argv = argv;
	vars.env = create_env(environment);

	// Set up the signal handler for SIGINT (^C)
	signal(SIGINT, sig_handler);

	// Check if input is coming from a pipe or is a terminal
	if (!isatty(STDIN_FILENO))
		is_pipe = 1;

	// Print the prompt if not in a pipe
	if (is_pipe == 0)
		_puts("$ ");

	// Initialize the global flag used in signal handling
	sig_flag = 0;

	// Main loop: Read commands from stdin and process them
	while (getline(&(vars.buffer), &len_buffer, stdin) != -1)
	{
		sig_flag = 1; // Indicate that we are processing commands
		vars.count++; // Increment the command count

		// Tokenize the input buffer by commands separated by ';'
		vars.commands = tokenize(vars.buffer, ";");

		// Process each command
		for (i = 0; vars.commands && vars.commands[i] != NULL; i++)
		{
			// Tokenize each command by whitespace
			vars.av = tokenize(vars.commands[i], "\n \t\r");

			// If there are tokens, check for built-in commands or execute the command
			if (vars.av && vars.av[0])
				if (check_for_builtins(&vars) == NULL)
					check_for_path(&vars);

			// Free the tokens for the current command
			free(vars.av);
		}

		// Free the buffer and commands after processing
		free(vars.buffer);
		free(vars.commands);

		// Reset the global flag and print the prompt if not in a pipe
		sig_flag = 0;
		if (is_pipe == 0)
			_puts("$ ");
		
		// Reset the buffer pointer
		vars.buffer = NULL;
	}

	// Print a newline if not in a pipe and free the environment
	if (is_pipe == 0)
		_puts("\n");

	free_env(vars.env);
	free(vars.buffer);

	// Exit with the status of the last command
	exit(vars.status);
}
