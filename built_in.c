#include "shell.h"

/**
 * _myexit - This function exits the shell
 * @info: This ia a structure containing potential arguments.
 * Return: exits with a given exit status
 */

int _myexit(info_t *info)
{
	int exit_check_var;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		exit_check_var = _erratoi(info->argv[1]);
		if (exit_check_var == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - This function changes process' current directory
 * @info: This is a structure containing potential arguments.
 *  Return: 0
 */

int _mycd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_returnvalue;

	s = getcwd(buffer, 1024);
	if (s == NULL)
		_puts("TODO: >>getcwd failure msg displayed here<<\n");
	if ((info->argv[1]) == NULL)
	{
		dir = _getenv(info, "HOME=");
		if (dir == NULL)
			chdir_returnvalue = /* TODO: this should be? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_returnvalue = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if ((_getenv(info, "OLDPWD=")) == NULL)
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_returnvalue = /* TODO: this should be? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_returnvalue = chdir(info->argv[1]);
	if (chdir_returnvalue == -1)
	{
		print_error(info, "can't change directory to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - This function changes current directory of process
 * @info: This is a structure containing potential arguments.
 *  Return: 0
 */

int _myhelp(info_t *info)
{
	char **the_arg_array;

	the_arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");

	if (0)
	{
		_puts(*the_arg_array); /* temp att_unused workaround */
	}
	return (0);
}
