#include "shell.h"

/**
 * get_environ - This function returns string array copy of our environ
 * @info: This is a structure containing potential arguments.
 * Return: 0
 */

char **get_environ(info_t *info)
{
	if (info->environ == NULL || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - This function removes an environment variable
 * @info: This is a structure containing potential arguments
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */

int _unsetenv(info_t *info, char *var)
{
	list_t *node_h = info->env;
	size_t x = 0;
	char *char_p;

	if (node_h == NULL || var == NULL)
	{
		return (0);
	}

	while (node_h)
	{
		char_p = starts_with(node->str, var);
		if (char_p && *char_p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), x);
			x = 0;
			node_h = info->env;
			continue;
		}
		node_h = node_h->next;
		x++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initialize new environment variable or modify existing one
 * @info: This is a structure containing potential arguments
 * @var: This parameter is the string env var property
 * @value: This parameter is the string env var value
 *  Return: 0
 */

int _setenv(info_t *info, char *var, char *value)
{
	char *buff = NULL;
	list_t *node_h;
	char *char_p;

	if (var == NULL || value == NULL)
	{
		return (0);
	}

	buff = malloc(_strlen(var) + _strlen(value) + 2);

	if (buff == NULL)
	{
		return (1);
	}
	_strcpy(buff, var);
	_strcat(buff, "=");
	_strcat(buff, value);
	node_h = info->env;

	while (node_h)
	{
		char_p = starts_with(node_h->str, var);
		if (char_p && *char_p == '=')
		{
			free(node_h->str);
			node_h->str = buff;
			info->env_changed = 1;
			return (0);
		}
		node_h = node_h->next;
	}
	add_node_end(&(info->env), buff, 0);
	free(buff);
	info->env_changed = 1;
	return (0);
}
