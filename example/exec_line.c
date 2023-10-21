#include "main.h"

/**
 * exec_line - finds cmd builtins funcs
 *
 * @datash: data relevant (args)
 * Return: 1 on success.
 */
int exec_line(runtime *datash)
{
	int (*builtin)(runtime *datash);

	if (datash->args[0] == NULL)
		return (1);

	builtin = get_builtin(datash->args[0]);

	if (builtin != NULL)
		return (builtin(datash));

	return (cmd_exec(datash));
}
