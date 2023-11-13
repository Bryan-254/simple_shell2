#include "shell.h"

/**
 * bfree - This function frees a pointer and will NULL the address
 * @ptr: This parameter is address of the pointer to free
 * Return: 1 if freed, else 0
 */

int bfree(void **ptr)
{
	if (*ptr && ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
