#include "main.h"
/**
 * remove_comment - removes comments from an input string
 *
 * str: input string
 * Return: input string with no comments
 */
char *remove_comment(char *str)
{
	int i, next;

	next = 0;
	for (i = 0; str[i]; i++)
	{
		if (str[i] == '#')
		{
			if (i == 0)
			{
				free(str);
				return (NULL);
			}

			if (str[i - 1] == ' ' || str[i - 1] == '\t' || str[i - 1] == ';')
				next = i;
		}
	}

	if (next != 0)
	{
		str = _realloc(str, i, next + 1);
		str[next] = '\0';
	}

	return (str);
}


/**
 * inf_loop - prompt or shell loop
 * @datash: data relevant (av, input, args)
 *
 * Return: no return.
 */
void inf_loop(runtime *datash)
{
	int loop, i_eof;
	char *in;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "$ ", 2);
		in = read_line(&i_eof);
		if (i_eof != -1)
		{
			in = remove_comment(in);
			if (in == NULL)
				continue;

			if (check_syntax_error(datash, in) == 1)
			{
				datash->status = 2;
				free(in);
				continue;
			}
			in = rep_var(in, datash);
			loop = split_commands(datash, in);
			datash->counter += 1;
			free(in);
		}
		else
		{
			loop = 0;
			free(in);
		}
	}
}
