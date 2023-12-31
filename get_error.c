#include "main.h"

/**
 * get_error - calls the error according the builtin, syntax or permission
 * @datash: data structure that contains arguments
 * @er_val: error value
 * Return: error
 */
int get_error(runtime *datash, int er_val)
{
	char *error;

	switch (er_val)
	{
	case -1:
		error = error_env(datash);
		break;
	case 126:
		error = error_path_126(datash);
		break;
	case 127:
		error = error_not_found(datash);
		break;
	case 2:
		if (tj_strcmp("exit", datash->args[0]) == 0)
			error = error_exit_shell(datash);
		else if (tj_strcmp("cd", datash->args[0]) == 0)
			error = error_get_cd(datash);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, tj_strlen(error));
		free(error);
	}

	datash->status = er_val;
	return (er_val);
}
