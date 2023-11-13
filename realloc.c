#include "shell.h"

/**
 * _memset - This function fills memory with a constant byte
 * @s: This parameter is the pointer to the memory area
 * @b: This parameter is the byte to fill *s with
 * @n: This is the amount of bytes to be filled
 * Return: pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int x;

	for (x = 0; x < n; x++)
	{
		s[x] = b;
	}
	return (s);
}

/**
 * ffree - This function frees a string of strings
 * @point_p: This parameter is the string of strings
 */

void ffree(char **point_p)
{
	char **x = point_p;

	if (point_p == NULL)
	{
		return;
	}
	while (*point_p)
	{
		free(*point_p++);
	}
	free(x);
}

/**
 * _realloc - This function reallocates a block of memory
 * @ptr: This parameter is pointer to the memory previously mallocated
 * @old_size: This parameter is the byte size of previous block
 * @new_size: This parameter is the byte size of new block
 * Return: Pointer to newly allocated memory
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *x;

	if (ptr == NULL)
	{
		return (malloc(new_size));
	}
	if (new_size == NULL)
	{
		free(ptr)
		return (NULL);
	}
	if (new_size == old_size)
	{
		return (ptr);
	}

	x = malloc(new_size);

	if (x == NULL)
	{
		return (NULL);
	}

	old_size = old_size < new_size ? old_size : new_size;

	while (old_size--)
	{
		x[old_size] = ((char *)ptr)[old_size];
	}
	free(ptr);
	return (x);
}
