#include "main.h"

/**
 * cd_shell - changes current directory
 *
 * @datash: data relevant
 * Return: 1 on success
 */
int cd_shell(runtime *datash)
{
	char *dir;
	int tj_home, tj_home2, tj_dash;

	dir = datash->args[1];

	if (dir != NULL)
	{
		tj_home = _strcmp("$HOME", dir);
		tj_home2 = _strcmp("~", dir);
		tj_dash = _strcmp("--", dir);
	}

	if (dir == NULL || !tj_home || !tj_home2 || !tj_dash)
	{
		cd_to_home(datash);
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		cd_previous(datash);
		return (1);
	}

	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		cd_dot(datash);
		return (1);
	}

	cd_to(datash);

	return (1);
}
