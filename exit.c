#include "shell.h"

/**
 * _strncpy - This function copies a string
 * @dest: This parameter is the destination string
 * @src: This parameter is the source string
 * @n: the amount of characters to be copied
 * Return: the concatenated string
 */

char *_strncpy(char *dest, char *src, int n)
{
	int x, y;
	char *d = dest;

	x = 0;

	while (src[x] != '\0' && x < n - 1)
	{
		dest[x] = src[x];
		x++;
	}
	if (x < n)
	{
		y = x;
		while (y < n)
		{
			dest[y] = '\0';
			y++;
		}
	}
	return (d);
}

/**
 * _strncat - This function concatenates two strings
 * @dest: This parameter is the first string
 * @src: This parameter is the second string
 * @n: This is the amount of bytes to be max used
 * Return: returns the concatenated string
 */

char *_strncat(char *dest, char *src, int n)
{
	int x, y;
	char *d = dest;

	x = 0;
	y = 0;

	while (dest[x] != '\0')
	{
		x++;
	}
	while (src[y] != '\0' && y < n)
	{
		dest[x] = src[y];
		x++;
		y++;
	}
	if (y < n)
	{
		dest[x] = '\0';
	}
	return (d);
}

/**
 * _strchr - This function locates a character in a string
 * @s: This parameter is the string to be parsed
 * @c: This parmaremter is the character to search for
 * Return: (s) a pointer to the memory area s
 */

char *_strchr(char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return (s);
		s++;
	}

	if (*s == c)
		return (s);

	return (NULL);
}
