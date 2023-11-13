#include "shell.h"

/**
 * _myenv - This function prints the current environment
 * @info: This is a structure containing potential arguments
 * Return: 0
 */

int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - This function gets the value of an environ variable
 * @info: This is a structure containing potential arguments
 * @name: env variable name
 *
 * Return: the value of environ variable
 */

char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *char_p;

	while (node)
	{
		char_p = starts_with(node->str, name);
		if (char_p && *char_p)
		{
			return (char_p);
		}
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize new environment variable or modify existing one
 * @info: This is a structure containing potential arguments
 *  Return: 0
 */

int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("There is incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
	{
		return (0);
	}
	return (1);
}

/**
 * _myunsetenv - This function removes an environment variable
 * @info: This is a structure containing potential arguments.
 * Return: 0
 */

int _myunsetenv(info_t *info)
{
	int x;

	if (info->argc == 1)
	{
		_eputs("There is too few arguements.\n");
		return (1);
	}
	for (x = 1; x <= info->argc; x++)
	{
		_unsetenv(info, info->argv[x]);
	}

	return (0);
}

/**
 * populate_env_list - This function populates the env linked list
 * @info: This is a structure containing potential arguments
 * Return: 0
 */

int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t x;

	for (x = 0; environ[x]; x++)
	{
		add_node_end(&node, environ[x], 0);
	}
	info->env = node;
	return (0);
}
