#include "main.h"
/**
 
 * get_path_variable - Get the value of the PATH environment variable.
 * @environ: The environment variable array.
 *
 * Return: A dynamically allocated copy of the PATH value, or NULL if not found.
 */
char *get_path_variable(char *environ[]) {
    char *path = NULL;
    char *search_prefix = "PATH=";
    int i;
    size_t path_length;
    char *path_copy;

    for  (i = 0; environ[i] != NULL; i++) {
        if (strncmp(environ[i], search_prefix, custom_strlen(search_prefix)) == 0) {
            path = environ[i] + custom_strlen(search_prefix);
            break;
        }
    }

    if (path == NULL) {
        return NULL; 
    }

    path_length = custom_strlen(path);
    path_copy = malloc(path_length + 1);

    if (path_copy == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }

    strcpy(path_copy, path);
    return path_copy;
}
/**
 * paths - returns an array of directories in PATH
 *
 * @environ: array of strings of environment variables
 * Return: an array of directories in path
 */
char **paths(char *environ[])
{
	char *path = get_path_variable(environ);
	char **path_array = custom_tokenize_string(path, ":");

	free(path);

	return (path_array);
}

size_t custom_strlen(const char *str);
int custom_char_exists(const char *str, char c);
char **custom_tokenize_string(const char *str, const char *delimiters);

size_t custom_strlen(const char *str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

int custom_char_exists(const char *str, char c) {
    while (*str != '\0') {
        if (*str == c) {
            return 1;
        }
        str++;
    }
    return 0;
}

char **custom_tokenize_string(const char *str, const char *delimiters) {
    size_t len = custom_strlen(str);
    char **tokens = NULL;
    int token_count = 0;
    const char *start = str;
    size_t i;
    
    for (i = 0; i <= len; i++) {
        if (custom_char_exists(delimiters, str[i]) || str[i] == '\0') {
            if (i > 0 && str[i - 1] != '\0' && !custom_char_exists(delimiters, str[i - 1])) {
                token_count++;
            }
        }
    }
    
    if (token_count == 0) {
        return NULL;
    }
    
    tokens = (char **)malloc(sizeof(char *) * (token_count + 1));
    
    if (tokens == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    
    token_count = 0;
    
    for (i = 0; i <= len; i++) {
        if (custom_char_exists(delimiters, str[i]) || str[i] == '\0') {
            if (i > 0 && str[i - 1] != '\0') {
                size_t token_length = i - (start - str);
                tokens[token_count] = (char *)malloc(token_length + 1);
                
                if (tokens[token_count] == NULL) {
                    perror("Memory allocation failed");
                    exit(EXIT_FAILURE);
                }
                
                strncpy(tokens[token_count], start, token_length);
                tokens[token_count][token_length] = '\0';
                token_count++;
            }
            start = str + i + 1;
        }
    }
    
    tokens[token_count] = NULL;
    
    return tokens;
}


