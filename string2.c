#include "shell.h"

/**
 * *_strcpy - function that copies the string pointed to by src
 * @dest: The destination
 * @src: The source
 * Return: the pointer to dest
 */

char *_strcpy(char *dest, char *src)
{
	int x;

	for (x = 0 ; src[x] != '\0' ; x++)
	{
		dest[x] = src[x];
	}
	dest[x] = '\0';
	return (dest);
}

/**
 * _strdup - This function duplicates a string
 * @str: This is the string to duplicate
 *
 * Return: pointer to the duplicated string
 */

char *_strdup(const char *str)
{
	int leng = 0;
	char *dup;

	if (str == NULL)
	{
		return (NULL);
	}
	while (*str++)
	{
		leng++;
	}
	dup = malloc(sizeof(char) * (leng + 1));

	if (!dup)
	{
		return (NULL);
	}
	for (leng++; leng--;)
	{
		dup[leng] = *--str;
	}
	return (dup);
}

/**
 *_puts - This function prints an input string
 *@str: This is the string to be printed
 *
 * Return: void
 */

void _puts(char *str)
{
	int x = 0;

	if (!str)
	{
		return;
	}
	while (str[x] != '\0')
	{
		_putchar(str[x]);
		x++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _putchar(char c)
{
	return (write(1, &c, 1));
}
