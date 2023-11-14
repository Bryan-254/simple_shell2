#include "shell.h"

/**
 * **strtow - Function splits string into words. Repeat delimiters are ignored
 * @str: This parameter is the input string
 * @d: This parameter is the delimeter string
 * Return: Pointer to an array of strings, or NULL if fail
 */

char **strtow(char *str, char *d)
{
	int x, y, a, b, inpstr_wordcount = 0;
	char **st;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (d == NULL)
		d = " ";
	for (x = 0; str[x] != '\0'; x++)
		if (!is_delim(str[x], d) && (is_delim(str[x + 1], d) || !str[x + 1]))
			inpstr_wordcount++;

	if (inpstr_wordcount == 0)
		return (NULL);
	st = malloc((1 + inpstr_wordcount) * sizeof(char *));
	if (st == NULL)
		return (NULL);
	for (x = 0, y = 0 ; y < inpstr_wordcount ; y++)
	{
		while (is_delim(str[x], d))
			x++;
		a = 0;
		while (!is_delim(str[x + a], d) && str[x + a])
			a++;
		st[y] = malloc((a + 1) * sizeof(char));
		if (st[y] == NULL)
		{
			for (a = 0; a < y; a++)
				free(st[a]);
			free(st);
			return (NULL);
		}
		for (b = 0; b < a; b++)
		{
			st[y][b] = str[x++];
		}
		st[y][b] = 0;
	}
	st[y] = NULL;
	return (st);
}

/**
 * **strtow2 - This function splits a string into words
 * @str: This parameter is the input string
 * @d: This parameter is the delimeter
 * Return: Pointer to an array of strings, or NULL if fail
 */

char **strtow2(char *str, char d)
{
	int x, y, a, b, inpstr_wordcount = 0;
	char **st;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (x = 0; str[x] != '\0'; x++)
		if ((str[x] != d && str[x + 1] == d) ||
		    (str[x] != d && !str[x + 1]) || str[x + 1] == d)
			inpstr_wordcount++;
	if (inpstr_wordcount == 0)
		return (NULL);
	st = malloc((1 + inpstr_wordcount) * sizeof(char *));
	if (st == NULL)
		return (NULL);
	for (x = 0, y = 0 ; y < inpstr_wordcount ; y++)
	{
		while (str[x] == d && str[x] != d)
			x++;
		a = 0;
		while (str[x + a] != d && str[x + a] && str[x + a] != d)
			a++;
		st[y] = malloc((a + 1) * sizeof(char));
		if (st[y] == NULL)
		{
			for (a = 0 ; a < y ; a++)
			{
				free(st[a]);
			}
			free(st);
			return (NULL);
		}
		for (b = 0; b < a; b++)
		{
			st[y][b] = str[x++];
		}
		st[y][b] = 0;
	}
	st[y] = NULL;
	return (st);
}
