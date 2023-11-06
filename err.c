#include "shell.h"

/**
 * _eputs - This function prints an input string
 * @str: This parameter is the string to be printed
 *
 * Return: void
 */

void _eputs(char *str)
{
	int x = 0;

	if (str == NULL)
	{
		return;
	}
	while (str[x] != '\0')
	{
		_eputchar(str[x]);
		x++;
	}
}

/**
 * _eputchar - This function writes the character c to stderr
 * @c: This parameter is the character to print
 *
 * Return: On success 1, on error -1, & errno is set appropriately
 */

int _eputchar(char c)
{
	static int x;
	static char buf[WRITE_BUFF_SIZE];

	if (c == BUFF_FLUSH || x >= WRITE_BUFF_SIZE)
	{
		write(2, buff, x);
		x = 0;
	}
	if (c != BUFF_FLUSH)
	{
		buff[x++] = c;
	}
	return (1);
}

/**
 * _putfd - This function writes the character c to given fd
 * @c: This parameter is the character to print
 * @fd: This is the filedescriptor to write to
 *
 * Return: On success 1, on error -1, & errno is set appropriately
 */

int _putfd(char c, int fd)
{
	static int x;
	static char buff[WRITE_BUFF_SIZE];

	if (c == BUFF_FLUSH || x >= WRITE_BUFF_SIZE)
	{
		write(fd, buff, x);
		x = 0;
	}
	if (c != BUFF_FLUSH)
	{
		buff[x++] = c;
	}
	return (1);
}

/**
 * _putsfd - This function prints an input string
 * @str: This parameter is the string to be printed
 * @fd: This is the filedescriptor to write to
 *
 * Return: the number of characters put
 */

int _putsfd(char *str, int fd)
{
	int x = 0;

	if (str == NULL)
	{
		return (0);
	}
	while (*str)
	{
		x += _putfd(*str++, fd);
	}
	return (x);
}
