#include "main.h"
/**
 * free_tokens - frees the buffer used to store a token
 *
 * @buffer: buffer used to store the token
 */
void free_tokens(char **buffer)
{
	int i = 0;

	while (buffer[i])
		free(buffer[i++]);

	free(buffer);
}



/**
 * str_equals - checks if two strings are equal
 *
 * @first_string: the first string to be checked
 * @second_string: the second string to be checked
 * Return: EXIT_SUCCESS on if both strings are equal
 *         else EXIT_FAILURE
 */
int str_equals(char *first_string, char *second_string)
{
    while (*first_string && *second_string) {
        if (*first_string != *second_string) {
            return EXIT_FAILURE;
        }
        first_string++;
        second_string++;
    }

   
    if (*first_string == '\0' && *second_string == '\0') {
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}
/**
 * isexit - checks if the given string is equals to "exit"
 *
 * @str: the string to be checked
 * Return: EXIT_SUCCESS on if str equal to "exit"
 *         else EXIT_FAILURE
 */
int isexit(char *str)
{
	char *first_string = "exit";

	return (str_equals(first_string, str));
}


/**
 * env_path - prints all environment variables
 *
 * @envp: the environment variables array
 * Return: EXIT_SUCCESS on success
 */
int env_path(char *envp[])
{
	int i;	
    if (envp == NULL) {
        return EXIT_FAILURE;
    }
    

    for (i = 0; envp[i] != NULL; i++) {
        char *env_variable = envp[i];
        printf("%s\n", env_variable);
    }

    return EXIT_SUCCESS;
}
/**
 * _lstrip - rmoves space from 
 *@str: the strin spaces would be removed from
*/

char *_lstrip(char *str)
{
	size_t i;
	size_t first_non_space;
    	if (str == NULL || *str == '\0') 
	{
        	return str; 
	}

    
    	first_non_space = 0;
    	while (str[first_non_space] != '\0' && str[first_non_space] == ' ')
       	{
        	first_non_space++;
   	 }

    for (i = 0; str[i + first_non_space] != '\0'; i++) {
        str[i] = str[i + first_non_space];
    }
    str[i] = '\0'; 

    return str;
}
