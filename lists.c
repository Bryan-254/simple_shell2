#include "shell.h"

/**
 * add_node - This function adds a node to the list start
 * @head: This parameter is address of pointer to head node
 * @str: This is string to store
 * @num: This is the node index used by history
 * Return: The list size
 */

list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_h;

	if (head == NULL)
	{
		return (NULL);
	}
	new_h = malloc(sizeof(list_t));
	if (new_h == NULL)
	{
		return (NULL);
	}
	_memset((void *)new_h, 0, sizeof(list_t));
	new_h->num = num;
	if (str)
	{
		new_h->str = _strdup(str);
		if (!new_h->str)
		{
			free(new_h);
			return (NULL);
		}
	}
	new_h->next = *head;
	*head = new_h;
	return (new_h);
}

/**
 * add_node_end - This function adds a node to the list end
 * @head: This parameter is address of pointer to head node
 * @str: This is the string to store
 * @num: This is the node index used by history
 * Return: The list size
 */

list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_n, *node;

	if (head == NULL)
	{
		return (NULL);
	}

	node = *head;
	new_n = malloc(sizeof(list_t));
	if (new_n == NULL)
	{
		return (NULL);
	}
	_memset((void *)new_n, 0, sizeof(list_t));
	new_n->num = num;
	if (str)
	{
		new_n->str = _strdup(str);
		if (!new_n->str)
		{
			free(new_n);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
		{
			node = node->next;
		}
		node->next = new_n;
	}
	else
	{
		*head = new_n;
	}
	return (new_n);
}

/**
 * print_list_str - This function prints only str element of list_t list
 * @h: This parameter is the pointer to head og linked list
 * Return: List size
 */

size_t print_list_str(const list_t *h)
{
	size_t x = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		x++;
	}
	return (x);
}

/**
 * delete_node_at_index - This function deletes node at a given index
 * @head: This parameter is address of pointer to first node
 * @index: This parameter is node index to delete
 * Return: 1 on success, 0 on fail
 */

int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_n;
	unsigned int x = 0;

	if (head == NULL || *head == NULL)
	{
		return (0);
	}

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (x == index)
		{
			prev_n->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		x++;
		prev_n = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - This function frees all list nodes
 * @head_ptr: This parameter is address of pointer to head node
 * Return: void
 */

void free_list(list_t **head_ptr)
{
	list_t *node, *next_n, *head;

	if (head_ptr == NULL || *head_ptr == NULL)
	{
		return;
	}
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_n = node->next;
		free(node->str);
		free(node);
		node = next_n;
	}
	*head_ptr = NULL;
}
