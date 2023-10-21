#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>
#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* Points to an array of pointers to strings called the "environment" */
extern char **environ;


/**
 * struct data - struct that contains all relevant data on runtime
 * @av: argument vector
 * @input: command line written by the user
 * @args: tokens of the command line
 * @status: last status of the shell
 * @counter: lines counter
 * @_environ: environment variable
 * @pid: process ID of the shell
 */
typedef struct data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} runtime;

/**
 * struct sep_list_s - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */
typedef struct sep_list_s
{
	char separate;
	struct sep_list_s *next;
} seperator;

/**
 * struct line_list_s - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} cmd_line;

/**
 * struct r_var_list - single linked list
 * @len_var: length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} var_list;

/**
 * struct builtin_s - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(runtime *datash);
} builtin_c;

/* aux_lists.c */
seperator *add_sep_node_end(seperator **head, char sep);
void free_sep_list(seperator **head);
cmd_line *add_line_node_end(cmd_line **head, char *line);
void free_line_list(cmd_line **head);

/* aux_lists2.c */
var_list *add_rvar_node(var_list **head, int lvar, char *var, int lval);
void free_rvar_list(var_list **head);


char *tj_strcat(char *destination, const char *sc);
char *tj_strcpy(char *dest_str, char *src_str);
int tj_strcmp(char *s1, char *s2);
char *tj_strchr(char *s, char ch);
int tj_strspn(char *str, char *accept);


/* aux_mem.c */
void _memcpy(void *newptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);


int tj_isdigit(const char *str);
char *tj_strtok(char strn[], const char *del);
int tj_cmp_chars(char strn[], const char *del);
char *tj_strdup(const char *str1);
int tj_strlen(const char *str);

void str_rev(char *str);

/* check_syntax_error.c */
int repeated_char(char *input, int i);
int error_sep_op(char *input, int i, char last);
int first_char(char *input, int *i);
void print_syntax_error(runtime *datash, char *input, int i, int bool);
int check_syntax_error(runtime *datash, char *input);

char *remove_comment(char *str);
void inf_loop(runtime *datash);

/* read_line.c */
char *read_line(int *i_eof);

/* split.c */
char *swap_chr(char *input, int bool);
void add_nodes(seperator **head_s, cmd_line **head_l, char *input);
void go_next(seperator **list_s, cmd_line **list_l, runtime *datash);
int split_commands(runtime *datash, char *input);
char **split_line(char *input);


void checks_env(var_list **h, char *in_str, runtime *data);
int _check_vars(var_list **h, char *in_str, char *s, runtime *data);
char *rep_input(var_list **head, char *inp, char *new_inp, int n_len);
char *repl_var(char *inp, runtime *datash);



/* get_line.c */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);

/* exec_line */
int exec_line(runtime *datash);

/* cmd_exec.c */
int is_cdir(char *path, int *i);
char *_which(char *cmd, char **_environ);
int is_executable(runtime *datash);
int check_error_cmd(char *dir, runtime *datash);
int cmd_exec(runtime *datash);

/* env1.c */
char *_getenv(const char *name, char **_environ);
int _env(runtime *datash);

/* env2.c */
char *copy_info(char *name, char *value);
void set_env(char *name, char *value, runtime *datash);
int _setenv(runtime *datash);
int _unsetenv(runtime *datash);

/* cd.c */
void chng_dot(runtime *datash);
void chng_to(runtime *datash);
void chng_previous(runtime *datash);
void chng_to_home(runtime *datash);

/* cd_shell.c */
int cd_shell(runtime *datash);

/* get_builtin */
int (*get_builtin(char *cmd))(runtime *datash);

/* _exit.c */
int exit_shell(runtime *datash);

/* aux_stdlib.c */
int get_len(int n);
char *aux_itoa(int n);
int _atoi(char *s);

/* aux_error1.c */
char *strcat_click(runtime *, char *, char *, char *);
char *error_get_cd(runtime *datash);
char *error_not_found(runtime *datash);
char *error_exit_shell(runtime *datash);

/* aux_error2.c */
char *error_get_alias(char **args);
char *error_env(runtime *datash);
char *error_syntax(char **args);
char *error_permission(char **args);
char *error_path_126(runtime *datash);


/* get_error.c */
int get_error(runtime *datash, int eval);

/* get_sigint.c */
void get_sigint(int sig);

/* aux_help.c */
void aux_help_env(void);
void aux_help_setenv(void);
void aux_help_unsetenv(void);
void aux_help_general(void);
void aux_help_exit(void);

/* aux_help2.c */
void aux_help(void);
void aux_help_alias(void);
void aux_help_cd(void);

/* get_help.c */
int get_help(runtime *datash);

#endif
