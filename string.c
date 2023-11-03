#include "shell.h"

/**
 * _strlen - Function that returns the length of a string
 * @s: string to be checked
 * Return: length of string
 */

int _strlen(char *s)
{
	int x;
	int count = 0;

	for (x = 0 ; s[x] != '\0' ; x++)
	{
		count++;
	}
	return (count);
}

/**
 * _strcmp - Function that compares two strings task
 * @s1: String 1
 * @s2: String 2
 * Return: 0 or positive or negative
 */

int _strcmp(char *s1, char *s2)
{
	int x;

	for (x = 0 ; s1[x] != '\0' || s2[x] != '\0' ; x++)
	{
		if (s1[x] != s2[x])
		{
			if (s1[x] < s2[x])
			{
				return (s1[x] - s2[x]);
			}
			else if (s2[x] < s1[x])
			{
				return (s1[x] - s2[x]);
			}
		}
	}
	return (0);
}

/**
 * starts_with - This function checks whether needle starts with haystack
 * @haystack: This parameter is the string to search
 * @needle: This parameter is the substring to find
 *
 * Return: address of next char of haystack or NULL
 */

char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
	{
		if (*needle++ != *haystack++)
		{
			return (NULL);
		}
	}
	return ((char *)haystack);
}

/**
 * *_strcat - Function that concatenates two strings
 * @dest: string of the destination
 * @src: string of the source
 * Return: dest
 */

char *_strcat(char *dest, char *src)
{
	int destlength = 0;
	int srclength = 0;
	int x;

	for (x = 0 ; dest[x] != '\0' ; x++)
	{
		destlength++;
	}
	for (x = 0 ; src[x] != '\0' ; x++)
	{
		srclength++;
	}
	for (x = 0 ; x <= srclength ; x++)
	{
		dest[destlength + x] = src[x];
	}
	return (dest);
}
