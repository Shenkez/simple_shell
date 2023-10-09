#include "main.h"

/**
 * env_cmd - lists all environment variables
 *
 * Return: void
 */
void env_cmd(void)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
}

/**
 * init_env_list - Intialise environment variables
 * @head: head node
 */
void init_env_list(envstruct *head)
{
	while (environ != NULL)
	{
		char *key = strtok(*environ, "="), *val = strtok(NULL, "=");

		head = insert_end(head, key, val);
		environ++;
	}
}

/**
 * setenv_cmd - sets environment variable
 * @argv: argument vector
 * @head: head node
 */
void setenv_cmd(char **argv, envstruct *head)
{
	if (argv != NULL)
	{
		if ((*(argv + 1) != NULL) && (*(argv + 2) != NULL))
		{
			head = insert_end(head, *(argv + 1), *(argv + 2));
			print_all(head);
		}
		else
			perror("setenv_cmd insert Error");
	}
}

/**
 * unsetenv_cmd - remove environment variable set
 * @argv: argument vector
 * @head: head node
 */
void unsetenv_cmd(char **argv, envstruct *head)
{
	if (argv != NULL)
	{
		if ((*(argv + 1) != NULL))
		{
			remove_value(&head, *(argv + 1));
			print_all(head);
		}
		else
			perror("setenv_cmd remove Error");
	}
}
