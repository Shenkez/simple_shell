#include "main.h"

/**
 * main - Entrance to program
 *
 * Return: Exit code
 */
int main(void)
{
	char *lineptr = NULL;
	atexit(clean_up);
	signal(SIGINT, sig_int_handler);

	while (1)
	{
		envstruct *head = NULL;
		/** init_env_list(head); */
		char *cmd;
		char *argv[100];
		int i = 0;
label:
		if (isatty(fileno(stdin)))
			write(1, "$ ", 2);

		_getline();

		cmd = strtok(lineptr, " \t\n");

		if (cmd == NULL)
		{
			free(lineptr);
			goto label;
		}

		while (cmd != NULL)
		{
			argv[i] = cmd;
			cmd = strtok(NULL, " \t\n");
			i++;
		}
		argv[i] = NULL;

		if (is_builtin_cmd(argv[0]) == 1)
		{
			exec_builtin_cmd(argv, head);
		}
		else if (is_builtin_cmd(argv[0]) == 0)
		{
			exec_executable_cmd(argv[0], argv, environ);
		}
		else
		{
			perror(" ");
			if (lineptr != NULL)
				free(lineptr);
			exit(127);
		}
		if (lineptr != NULL)
			free(lineptr);
	}
	return (0);
}
/**
 * is_builtin_cmd - checks for lists of built-in command
 * @cmd: the command checked
 *
 * Return: 0 or 1
 */
int is_builtin_cmd(char *cmd)
{
	int i = 0;
	const char *builtins[5] = {"exit", "env", "setenv", "unsetenv", "cd"};

	while (i < 5)
	{
		if (our_strstr(cmd, builtins[i]) == cmd)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

/**
 * exec_builtin_cmd - execute builtin commands
 * @argv: argument vector - points to arguments entered
 * @head: head of lists.
 *
 * Return: void
 */
void exec_builtin_cmd(char **argv, envstruct *head)
{
	if (our_strstr(argv[0], "exit") == argv[0])
	{
		if (argv[1] != NULL)
			exit_cmd(atoi(argv[1]));
		else
			exit_cmd(0);
	}
	if (our_strstr(argv[0], "env") == argv[0])
	{
		env_cmd();
	}
	if (our_strstr(argv[0], "setenv") == argv[0])
	{
		setenv_cmd(argv, head);
	}
	if (our_strstr(argv[0], "unsetenv") == argv[0])
	{
		unsetenv_cmd(argv, head);
	}
	if (our_strstr(argv[0], "cd") == argv[0])
	{
		if (cd_cmd(argv) == -1)
		{
			perror("");
		}
	}
}

/**
 * _getline - Get line conditions
 *
 * Return: Characters from stdin
 */
char *_getline(void)
{
	char *lineptr = NULL;
	size_t numbytes = 0, newnumbytes;
	ssize_t linelen;

	linelen = getline(&lineptr, &numbytes, stdin);

	if (linelen == -1)
	{
		if (feof(stdin))
		{
			if (isatty(fileno(stdin)))
			{
				write(1, "\n", 1);
			}
			exit(0);
		}
		perror("");
		exit(1);
	}

	newnumbytes = our_strcspn(lineptr, "\n");

	if (lineptr[newnumbytes] == '\n')
		lineptr[newnumbytes] = '\0';

	return (lineptr);
}




/**
 * exec_executable_cmd - execute the executable commands
 * @cmd: command
 * @argv: argument variable
 * @envp: argument variable
 *
 * Return: void
 */
void exec_executable_cmd(char *cmd, char **argv, char **envp)
{
	char *full_path;
	pid_t child_pid;
	int status;

	full_path = check_cmd(cmd);

	if (full_path == NULL)
	{
		return;
	}

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("");
		exit(1);
	}
	else if (child_pid == 0)
	{
		execve_cmd(full_path, argv, envp);
	}
	else
	{
		wait(&status);
	}

	if ((full_path != NULL) && (full_path != cmd))
	{
		free(full_path);
		full_path = NULL;
	}
}


