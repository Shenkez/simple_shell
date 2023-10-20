#include "main.h"

/**
 * strcat_click - function that concatenates the message for click error
 *
 * @datash: data relevant (directory)
 * @pr_msg: message to print
 * @output_msg: output message
 * @line_count: counter lines
 * Return: output message
 */
char *strcat_click(runtime *datash, char *pr_msg, char *output_msg, char *line_count)
{
	char *flag;

	_strcpy(output_msg, datash->av[0]);
	_strcat(output_msg, ": ");
	_strcat(output_msg, line_count);
	_strcat(output_msg, ": ");
	_strcat(output_msg, datash->args[0]);
	_strcat(output_msg,pr_msg);
	if (datash->args[1][0] == '-')
	{
		flag = malloc(3);
		flag[0] = '-';
		flag[1] = datash->args[1][1];
		flag[2] = '\0';
		_strcat(output_msg, flag);
		free(flag);
	}
	else
	{
		_strcat(output_msg, datash->args[1]);
	}

	_strcat(output_msg, "\n");
	_strcat(output_msg, "\0");
	return (output_msg);
}

/**
 * error_get_cd - error message for cd command in get_cd
 * @datash: data relevant (directory)
 * Return: Error message
 */
char *error_get_cd(runtime *datash)
{
	int length, len_id;
	char *error, *ver_str, *msg;

	ver_str = aux_itoa(datash->counter);
	if (datash->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _strlen(datash->args[1]);
	}

	length = _strlen(datash->av[0]) + _strlen(datash->args[0]);
	length += _strlen(ver_str) + _strlen(msg) + len_id + 5;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}

	error = strcat_click(datash, msg, error, ver_str);

	free(ver_str);

	return (error);
}

/**
 * error_not_found - generic error message for command not found
 * @datash: data relevant (counter, arguments)
 * Return: Error message
 */
char *error_not_found(runtime *datash)
{
	int len_;
	char *error;
	char *_var_str;

	_var_str = aux_itoa(datash->counter);
	len_ = _strlen(datash->av[0]) + _strlen(_var_str);
	len_ += _strlen(datash->args[0]) + 16;
	error = malloc(sizeof(char) * (len_ + 1));
	if (error == 0)
	{
		free(error);
		free(_var_str);
		return (NULL);
	}
	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, _var_str);
	_strcat(error, ": ");
	_strcat(error, datash->args[0]);
	_strcat(error, ": not found\n");
	_strcat(error, "\0");
	free(_var_str);
	return (error);
}

/**
 * error_exit_shell - generic error message for exit in get_exit
 * @datash: data relevant (counter, arguments)
 *
 * Return: Error message
 */
char *error_exit_shell(runtime *datash)
{
	int _length;
	char *error;
	char *var_str;

	var_str = aux_itoa(datash->counter);
	_length = _strlen(datash->av[0]) + _strlen(var_str);
	_length += _strlen(datash->args[0]) + _strlen(datash->args[1]) + 23;
	error = malloc(sizeof(char) * (_length + 1));
	if (error == 0)
	{
		free(var_str);
		return (NULL);
	}
	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, var_str);
	_strcat(error, ": ");
	_strcat(error, datash->args[0]);
	_strcat(error, ": Illegal number: ");
	_strcat(error, datash->args[1]);
	_strcat(error, "\n\0");
	free(var_str);

	return (error);
}
