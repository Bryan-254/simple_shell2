#include "shell.h"

/**
 * list_len - This function determines length of a linked list
 * @h: This parameter is the pointer to first node
 *
 * Return: List size
 */

size_t list_len(const list_t *h)
{
	size_t nodes = 0;

	while (h != NULL)
	{
		h = h->next;
		nodes++;
	}

	return (nodes);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */

char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t x = list_len(head), y;
	char **strs;
	char *str;

	if (!head || !x)
	{
		return (NULL);
	}
	strs = malloc(sizeof(char *) * (x + 1));
	if (strs == NULL)
	{
		return (NULL);
	}
	for (x = 0; node; node = node->next, x++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (str == NULL)
		{
			for (y = 0 ; y < x ; y++)
			{
				free(strs[y]);
			}
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[x] = str;
	}
	strs[x] = NULL;
	return (strs);
}

/**
 * print_the_list - This function prints all elements of a list_t list
 * @h: This parameter is pointer to first node
 *
 * Return: List size
 */

size_t print_the_list(const list_t *h)
{
	size_t x = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		x++;
	}
	return (x);
}

/**
 * node_starts_with - Function returns node whose string starts with prefix
 * @node: This parameter is pointer to list head
 * @prefix: This parameter is string to match
 * @c: the next character after prefix to match
 *
 * Return: The match node or NULL
 */

list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *pt = NULL;

	while (node)
	{
		pt = starts_with(node->str, prefix);
		if (pt && ((c == -1) || (*pt == c)))
		{
			return (node);
		}
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - This function gets the index of a node
 * @head: This parameter is the pointer to list head
 * @node: This parameter is the pointer to the node
 *
 * Return: The node index or -1
 */

ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t x = 0;

	while (head)
	{
		if (head == node)
		{
			return (x);
		}
		head = head->next;
		x++;
	}
	return (-1);
}
