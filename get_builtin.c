#include "main.h"

/**
 * get_builtin - builtin that pais the cmd in the arg
 * @cmd: command for  given fnct
 * Return: function pointer of the builtin command
 */
int (*get_builtin(char *cmd))(runtime *)
{
	builtin_c builtin[] = {
		{ "env", _env },
		{ "exit", exit_shell },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", cd_shell },
		{ "help", get_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; builtin[i].name; i++)
	{
		if (tj_strcmp(builtin[i].name, cmd) == 0)
			break;
	}

	return (builtin[i].f);
}
