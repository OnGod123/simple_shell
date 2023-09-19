#include "main.h"

/**
 * main - Entry point of the program
 *
 * @argc: The number of arguments passed to the program
 * @argv: Array of arguments passed to the program
 * @envp: Array of environment variables
 * Return: Always EXIT_SUCCESS
 */
#define BUFFSIZE 1024
int main(int __attribute__((__unused__)) argc, char *argv[], char *envp[])
{
    char **cmd;
    int interactive_mode;
    size_t bufsize = BUFFSIZE;
    int line_number = 1; /* Line number for error messages */

    cmd = malloc(sizeof(char) * BUFFSIZE);
    if (cmd == NULL)
        return (EXIT_FAILURE);

    interactive_mode = isatty(STDIN_FILENO);

    if (interactive_mode == 1)
        interactive_shell(cmd, &bufsize, argv, envp, line_number);
    else
        non_interactive_shell(cmd, &bufsize, argv, envp, line_number);

    return (EXIT_SUCCESS);
}

/**
 * interactive_shell - Starts the shell in interactive mode
 *
 * @cmd: Pointer to store commands entered by users
 * @bufsize: Size of "cmd" in bytes
 * @argv: Array of arguments passed to the program
 * @envp: Array of environment variables
 * @line_number: Integer representing the lines of commands processed by the shell
 * Return: EXIT_SUCCESS
 */
int interactive_shell(char **cmd, size_t *bufsize,
                            char *argv[], char *envp[], int line_number)
{
    pid_t pid; /* Process ID of the child process */
    int status; /* Status of the child process */
    char **commands;

    print_string("-> "); /* Prompt */

    commands = get_command(cmd, bufsize, envp);

    if (custom_strlen(cmd[0]) > 0)
    {
        if (isexit(cmd[0]) == EXIT_SUCCESS ||
            *cmd[0] == -1 || *cmd[0] == EOF)
            return (0);
        if (str_equals(cmd[0], "env\n") == EXIT_SUCCESS)
            env_path(envp);
        else if (commands != NULL)
        {
            pid = fork();
            if (pid == -1)
                print_string("Failed to fork\n");
            else if (pid > 0)
                waitpid(pid, &status, 0);
            else
            {
                execute_command(commands, argv, envp, line_number);
                exit(98);
            }
        }
        else
            print_error(cmd[0], argv[0], line_number);
    }

    line_number += 1;
    interactive_shell(cmd, bufsize, argv, envp, line_number);
    return (EXIT_SUCCESS);
}

/**
 * non_interactive_shell - Starts the shell in non-interactive mode
 *
 * @cmd: Pointer to store commands entered by users
 * @bufsize: Size of "cmd" in bytes
 * @argv: Array of arguments passed to the program
 * @envp: Array of environment variables
 * @line_number: Integer representing the lines of commands processed by the shell
 * Return: 98 if there's an error, otherwise EXIT_SUCCESS
 */
int non_interactive_shell(char **cmd, size_t *bufsize, char *argv[],
                char *envp[], int line_number)
{
    char **commands;

    commands = get_command(cmd, bufsize, envp);

    if (*cmd[0] != -1 || *cmd[0] != EOF)
    {
        if (str_equals(cmd[0], "env\n") == EXIT_SUCCESS)
        {
            env_path(envp);
            return (EXIT_SUCCESS);
        }
        else if (commands != NULL)
            execute_command(commands, argv, envp, line_number);
        else
            print_error(cmd[0], argv[0], line_number);
    }

    return (98);
}

/**
 * execute_command - Executes a command using the execve function
 *
 * @cmd: The command to be run
 * @argv: Extra arguments passed to the program
 * @envp: Array of environment variables the program can access
 * @line_number: Integer representing the lines of commands processed by the shell
 */
void execute_command(char **cmd, char *argv[],
                 char *envp[], int line_number)
{
    execve(cmd[0], cmd, envp);
    print_error(cmd[0], argv[0], line_number);
}

/**
 * print_error - Standard format for shell error messages
 *           Prints the error message to the screen
 *
 * @cmd: The command that generated the error
 * @shell: Name of the shell
 * @line_number: Integer representing the lines of commands processed by the shell
 */
void print_error(char *cmd, char *shell, int line_number)
{
    	print_string(shell);
    	print_string(": ");
	print_int(line_number);
	 perror(cmd);
}
