#include "main.h"

/**
 * chng_dot - make changes to the primary directory
 * @datash: real data relevant (environ)
 *
 * Return: no return
 */
void chng_dot(runtime *datash)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = tj_strdup(pwd);
	set_env("OLDPWD", cp_pwd, datash);
	dir = datash->args[1];
	if (tj_strcmp(".", dir) == 0)
	{
		set_env("PWD", cp_pwd, datash);
		free(cp_pwd);
		return;
	}
	if (tj_strcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	str_rev(cp_strtok_pwd);
	cp_strtok_pwd = tj_strtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = tj_strtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			str_rev(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		set_env("PWD", cp_strtok_pwd, datash);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", datash);
	}
	datash->status = 0;
	free(cp_pwd);
}

/**
 * chng_to - commit changes to a directory given
 * by the user
 *
 * @datash: data relevant (directories)
 * Return: no return
 */
void chng_to(runtime *datash)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = datash->args[1];
	if (chdir(dir) == -1)
	{
		get_error(datash, 2);
		return;
	}

	cp_pwd = tj_strdup(pwd);
	set_env("OLDPWD", cp_pwd, datash);

	cp_dir = tj_strdup(dir);
	set_env("PWD", cp_dir, datash);

	free(cp_pwd);
	free(cp_dir);

	datash->status = 0;

	chdir(dir);
}

/**
 * chng_previous - commit changes to the previous directory
 *
 * @datash: data relevant ie envr
 * Return: no return
 */
void chng_previous(runtime *datash)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = tj_strdup(pwd);

	p_oldpwd = _getenv("OLDPWD", datash->_environ);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = tj_strdup(p_oldpwd);

	set_env("OLDPWD", cp_pwd, datash);

	if (chdir(cp_oldpwd) == -1)
		set_env("PWD", cp_pwd, datash);
	else
		set_env("PWD", cp_oldpwd, datash);

	p_pwd = _getenv("PWD", datash->_environ);

	write(STDOUT_FILENO, p_pwd, tj_strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	datash->status = 0;

	chdir(p_pwd);
}

/**
 * chng_to_home - commit changes to the home directory
 *
 * @datash: data relevant environ
 * Return: no return
 */
void chng_to_home(runtime *datash)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = tj_strdup(pwd);

	home = _getenv("HOME", datash->_environ);

	if (home == NULL)
	{
		set_env("OLDPWD", p_pwd, datash);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		get_error(datash, 2);
		free(p_pwd);
		return;
	}

	set_env("OLDPWD", p_pwd, datash);
	set_env("PWD", home, datash);
	free(p_pwd);
	datash->status = 0;
}


/**
 * cd_shell - commit changes current directory
 *
 * @datash: data relevant
 * Return: return 1 on success
 */
int cd_shell(runtime *datash)
{
	char *dir;
	int tj_home, tj_home2, tj_dash;

	dir = datash->args[1];

	if (dir != NULL)
	{
		tj_home = tj_strcmp("$HOME", dir);
		tj_home2 = tj_strcmp("~", dir);
		tj_dash = tj_strcmp("--", dir);
	}

	if (dir == NULL || !tj_home || !tj_home2 || !tj_dash)
	{
		chng_to_home(datash);
		return (1);
	}

	if (tj_strcmp("-", dir) == 0)
	{
		chng_previous(datash);
		return (1);
	}

	if (tj_strcmp(".", dir) == 0 || tj_strcmp("..", dir) == 0)
	{
		chng_dot(datash);
		return (1);
	}

	chng_to(datash);

	return (1);
}

