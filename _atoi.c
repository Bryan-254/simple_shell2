#include "shell.h"

/**
 * interactive - This function returns true if shell is interactive mode
 * @info: This is the struct address
 * Return: 1 if interactive mode, else 0
 */

int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - This function checks whether character is a delimeter
 * @c: This parameter is the char to check
 * @delim: This parameter is the delimeter string
 * Return: 1 if its true, 0 if its false
 */

int is_delim(char c, char *delim)
{
	while (*delim)
	{
		if (*delim++ == c)
		{
			return (1);
		}
	}
	return (0);
}

/**
 *_isalpha - This function checks for alphabetic character
 *@c: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int c)
{
	if (c >= 'A' && c <= 'Z')
	{
		return (1);
	}
	if (c >= 'a' && c <= 'z')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 * _atoi - This fucntion converts a string to an integer
 * @s: This parameter is the string to be converted
 * Return: 0 if no numbers in string, else converted number
 */

int _atoi(char *s)
{
	int x = 0;
	unsigned int num_int = 0;
	int negative_handle = 1;
	int is_int = 0;

	while (s[x])
	{
		if (s[x] == 45)
		{
			negative_handle *= -1;
		}

		while (s[x] >= 48 && s[x] <= 57)
		{
			is_int = 1;
			num_int = (num_int * 10) + (s[x] - '0');
			x++;
		}

		if (is_int == 1)
		{
			break;
		}

		x++;
	}

	num_int *= negative_handle;
	return (num_int);
}
