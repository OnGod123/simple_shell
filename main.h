#ifndef __MAIN_H_
#define _MAIN_H_
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
int print_string(char *str);
size_t custom_strlen(const char *str);
int in_string(char *haystack, char *needle);
char *str_copy(char *str);
int print_int(long int num);
char **get_command(char **command, size_t *buffsize, char *environ[]);
void execute_command(char **cmd, char *argv[],
                 char *envp[], int line_number);
void print_error(char *cmd, char *shell, int line_number);
int interactive_shell(char **cmd, size_t *bufsize,
                            char *argv[], char *envp[], int line_number);
int non_interactive_shell(char **cmd, size_t *bufsize, char *argv[],
                char *envp[], int line_number);
char **custom_tokenize_string(const char *str, const char *delimiters);
char **custom_tokenize_string(const char *str, const char *delimiters);
char *get_path_variable(char *environ[]);
char **paths(char *environ[]);
size_t custom_strlen(const char *str);
int str_equals(char *first_string, char *second_string);
int isexit(char *str);
char *_lstrip(char *str);
void free_tokens(char **buffer);
int env_path(char *envp[]);
char **get_command(char **command, size_t *buffsize, char *environ[]);
char *append_path(const char *path, const char *command);
char *append_path(const char *path, const char *command);
char *command_exists(char *command, char *environ[]);
int _putchar(char c);
char **paths(char *environ[]);
#endif
