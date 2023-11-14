#include "shell.h"

/**
 * hsh - This function is the main shell loop
 * @info: This is the parameter & return info struct
 * @av: This is the argument vector from main() function
 * Return: 0 if successful, 1 if error, or error code
 */

int hsh(info_t *info, char **av)
{
	ssize_t ret_val = 0;
	int builtin_retval = 0;

	while (builtin_retval != -2 && ret_val != -1)
	{
		clear_info(info);
		if (interactive(info))
		{
			_puts("$ ");
		}
		_eputchar(BUF_FLUSH);
		ret_val = get_input(info);
		if (ret_val != -1)
		{
			set_info(info, av);
			builtin_retval = find_builtin(info);
			if (builtin_retval == -1)
			{
				find_cmd(info);
			}
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
	{
		exit(info->status);
	}
	if (builtin_retval == -2)
	{
		if (info->err_num == -1)
		{
			exit(info->status);
		}
		exit(info->err_num);
	}
	return (builtin_retval);
}

/**
 * find_builtin - This function finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *		-2 if builtin signals exit(),
 *		0 if builtin execution is successful,
 *		1 if builtin is found but is not successful
 */

int find_builtin(info_t *info)
{
	int x, built_in_retval = -1;
	builtin_table builtintble[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (x = 0; builtintble[x].type; x++)
	{
		if (_strcmp(info->argv[0], builtintble[x].type) == 0)
		{
			info->line_count++;
			built_in_retval = builtintble[x].func(info);
			break;
		}
	}
	return (built_in_retval);
}

/**
 * find_cmd - This function finds a command in the PATH
 * @info: This parameter is the parameter & return info struct
 * Return: void
 */

void find_cmd(info_t *info)
{
	char *path = NULL;
	int x, y;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (x = 0, y = 0; info->arg[x]; x++)
	{
		if (!is_delim(info->arg[x], " \t\n"))
		{
			y++;
		}
	}
	if (!y)
	{
		return;
	}

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);

	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - This function forks a an exec thread to run cmd
 * @info: This is the parameter & return info struct
 * Return: void
 */

void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
			{
				exit(126);
			}
			exit(1);
		}
		perror("Error:");
		return;
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
			{
				print_error(info, "Permission denied\n");
			}
		}
	}
}
