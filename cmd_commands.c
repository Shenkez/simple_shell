#include "main.h"

/**
 * cd_cmd - change directory
 * @argv: argument vector
 *
 * Return: void
 */
int cd_cmd(char **argv)
{
	int stat;

	stat = chdir(argv[1]);

	if (stat == -1)
	{
		perror("");
		return (-1);
	}
	return (0);

}

/**
 * check_cmd - check cmd whether inbuilt or executable
 * @cmd: commands (tokens)
 *
 * Return: void
 */
char *check_cmd(char *cmd)
{
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (access(cmd, X_OK) == 0)
		{
			return (cmd);
		}
		else
		{
			perror("");
			exit(1);
		}
	}
	else
	{
		int dir_len, cmd_len;
		char *dir;
		char *path_dup;
		char *path = getenv("PATH");
		char *full_path = NULL;

		if (path == NULL)
			return (NULL);


		path_dup = our_strdup(path);
		dir = strtok(path_dup, ":");

		while (dir)
		{
			dir_len = our_strlen(dir);
			cmd_len = our_strlen(cmd);

			full_path = malloc((dir_len + cmd_len + 2) * sizeof(char));

			if (full_path == NULL)
			{
				free(full_path);
				free(path_dup);
				return (NULL);
			}

			strcpy(full_path, dir);
			strcat(full_path, "/");
			strcat(full_path, cmd);

			if (access(full_path, X_OK) == 0)
			{
				free(path_dup);
				return (full_path);
			}

			free(full_path);
			full_path = NULL;
			dir = strtok(NULL, ":");
		}
		free(full_path);
		free(path_dup);
		path_dup = NULL;
	}

	return (NULL);
}

/**
 * execve_cmd - execute the commands
 * @cmd: command
 * @argv: argument variable
 * @envp: argument variable
 *
 * Return: void
 */
void execve_cmd(char *cmd, char **argv, char **envp)
{
	if (execve(cmd, argv, envp) == -1)
	{
		perror("");
		exit(1);
	}
}


/**
 * sig_int_handler - handles the exit signal
 * @signum: the signal passed
 *
 * Return: void
 */

void sig_int_handler(int signum __attribute__((unused)))
{
	if (isatty(fileno(stdin)))
		printf("\n");
	exit(0);
}
