#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <wait.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>

extern char **environ;
void print_string(char *str);
void prompt(void);
char *read_line(void);
int string_length(char *s);
char *string_concatenate(char *dest, char *src);
char **string_tokenize(char *str);
int run(char **tokens, char *args);
void print_environment(void);
int _putchar(char c);
int _strcmp(char *s1, char *s2);
int execute_builtin(char **tokens);
int is_builtIn(char *str);
int c_atoi(char *s);
void _kill(char *lineptr, char *tmp, char **tok);
void exit_simple_shell(char **tokens, char *line);
void ctrl_c_handler(int signum);
int is_delimiter(char c, const char *delim);
char *custom_strtok(char *src, const char *delim);
char *string_copy(char *dest, char *src);
ssize_t get_line(char **str);
int handle_path(char **tokens);
int check_file_exists(char *s);
char *build_executable_path(char **tokens);
int execute_with_path(char **tokens, char *path, char *args);
char *build_variable(char *var_name, char *var_value);
int setenv(char *var_name, char *var_value);
int unsetenv(char *var_name);
char *string_duplicate(char *str);

#endif

