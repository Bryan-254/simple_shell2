#include "shell.h"

/**
 * _myhistory - This function displays history list, one command by line
 * @info: This is a structure containing potential arguments.
 *  Return: 0
 */

int _myhistory(info_t *info)
{
	print_the_list(info->history);
	return (0);
}

/**
 * unset_alias - This function sets the alias to string
 * @info: This is a parameter struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */

int unset_alias(info_t *info, char *str)
{
	char *char_point, c;
	int ret_value;

	char_point = _strchr(str, '=');

	if (char_point == NULL)
	{
		return (1);
	}
	c = *char_point;
	*char_point = 0;
	ret_value = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*char_point = c;
	return (ret_value);
}

/**
 * set_alias - This function sets alias to string
 * @info: This is a parameter struct
 * @str: This is the string alias
 *
 * Return: 0 if successful, 1 if error
 */

int set_alias(info_t *info, char *str)
{
	char *char_p;

	char_p = _strchr(str, '=');
	if (char_p == NULL)
	{
		return (1);
	}
	if (!*++char_p)
	{
		return (unset_alias(info, str));
	}

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - This function prints an alias string
 * @node: This is the alias node
 *
 * Return: 0 if successful, 1 if error
 */

int print_alias(list_t *node)
{
	char *char_p = NULL, *x = NULL;

	if (node)
	{
		char_p = _strchr(node->str, '=');

		for (x = node->str; x <= char_p; x++)
		{
			_putchar(*x);
		}
		_putchar('\'');
		_puts(char_p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - This function mimics the alias builtin, man alias
 * @info: This is a structure containing potential arguments.
 *  Return: 0
 */

int _myalias(info_t *info)
{
	int x = 0;
	char *char_p = NULL;
	list_t *list_node = NULL;

	if (info->argc == 1)
	{
		list_node = info->alias;
		while (list_node)
		{
			print_alias(list_node);
			list_node = list_node->next;
		}
		return (0);
	}
	for (x = 1; info->argv[x]; x++)
	{
		char_p = _strchr(info->argv[x], '=');
		if (char_p)
		{
			set_alias(info, info->argv[x]);
		}
		else
		{
			print_alias(node_starts_with(info->alias, info->argv[x], '='));
		}
	}

	return (0);
}
