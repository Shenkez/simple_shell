#include "main.h"

/**
 * exit_shell - exits the shell
 *
 * @datash: data relevant (status and args)
 * Return: 0 on success.
 */
int exit_shell(runtime *datash)
{
	unsigned int _ustatus;
	int is_digit;
	int _str_len;
	int big_num;

	if (datash->args[1] != NULL)
	{
		_ustatus = _atoi(datash->args[1]);
		is_digit = _isdigit(datash->args[1]);
		_str_len = _strlen(datash->args[1]);
		big_num = _ustatus > (unsigned int)INT_MAX;
		if (!is_digit || _str_len > 10 || big_num)
		{
			get_error(datash, 2);
			datash->status = 2;
			return (1);
		}
		datash->status = (_ustatus % 256);
	}
	return (0);
}
