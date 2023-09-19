#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "main.h"
/**
 * append_path - concatenates a path token with a command token
 *
 * @path: path string to append to
 * @command: command string to append
 * Return: buffer to appended path
 */


char *append_path(const char *path, const char *command)
{
	size_t path_len;
     	size_t command_len;
	char *result;
    if (path == NULL || command == NULL) {
        return NULL; 
    }

    path_len = strlen(path);
    command_len = strlen(command);

    
    result = (char *)malloc(path_len + command_len + 2); 
    if (result == NULL) 
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
  
    strcpy(result, path);

    
    if (path[path_len - 1] != '/') {
        strcat(result, "/");
    }

    
    strcat(result, command);

    return result;

}
/**
 * command_exists - searches for PATH dir containing command
 *
 * @command: the command to be searched for
 * @environ: array of strings of environment variables
 * Return: unsigned int character count
 */

char *command_exists(char *command, char *environ[])
{
	int i = 0;
	char *ret;
	char **path_array;

	if (command[0] == '/')
	{
		if (access(command, F_OK | X_OK) == 0)
		{
			return (command);
		}
	}
	else
	{
		path_array = paths(environ);

		while (path_array[i])
		{
			ret = append_path(path_array[i], command);
			if (access(ret, F_OK | X_OK) == 0)
				break;
			free(ret);
			i++;
		}

		/*free_tokens(path_array);*/

		return (ret);
	}

	return (NULL);
}
/**
 * get_command - get command from user and checks if it exists
 *
 * @command: buffer to store the command
 * @buffsize: the size of the buffer
 * @environ: array of strings of environment variables
 * Return: the command and it's arguments in an array if successful
 *         else NULL
 */
char **get_command(char **command, size_t *buffsize, char *environ[])
{
	char *full_path_to_command, **commands;

	getline(command, buffsize, stdin);
	command[0] = _lstrip(command[0]);

	commands = custom_tokenize_string(command[0], " :\r\n\t");

	full_path_to_command = command_exists(commands[0], environ);

	if (full_path_to_command == NULL)
		return (NULL);

	commands[0] = full_path_to_command;

	return (commands);
}
