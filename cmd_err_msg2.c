#include "main.h"

/**
 * error_env - error message for env in get_env.
 * @datash: data relevant (counter, arguments)
 * Return: error message.
 */
char *error_env(runtime *datash)
{
	int length;
	char *error;
	char *ver_str;
	char *msg;

	ver_str = aux_itoa(datash->counter);
	msg = ": Unable to add/remove from environment\n";
	length = _strlen(datash->av[0]) + _strlen(ver_str);
	length += _strlen(datash->args[0]) + _strlen(msg) + 4;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}

	tj_strcpy(error, datash->av[0]);
	tj_strcat(error, ": ");
	tj_strcat(error, ver_str);
	tj_strcat(error, ": ");
	tj_strcat(error, datash->args[0]);
	tj_strcat(error, msg);
	tj_strcat(error, "\0");
	free(ver_str);

	return (error);
}
/**
 * error_path_126 - error message for path and failure denied permission.
 * @datash: data relevant (counter, arguments).
 *
 * Return: The error string.
 */
char *error_path_126(runtime *datash)
{
	int tj_len;
	char *tj_var_str;
	char *error;

	tj_var_str = aux_itoa(datash->counter);
	tj_len= _strlen(datash->av[0]) + _strlen(tj_var_str);
	tj_len += _strlen(datash->args[0]) + 24;
	error = malloc(sizeof(char) * (tj_len + 1));
	if (error == 0)
	{
		free(error);
		free(tj_var_str);
		return (NULL);
	}
	tj_strcpy(error, datash->av[0]);
	tj_strcat(error, ": ");
	tj_strcat(error, tj_var_str);
	tj_strcat(error, ": ");
	tj_strcat(error, datash->args[0]);
	tj_strcat(error, ": Permission denied\n");
	tj_strcat(error, "\0");
	free(tj_var_str);
	return (error);
}
