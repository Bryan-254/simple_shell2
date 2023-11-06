#include "shell.h"

/**
 * _erratoi - This function converts a string to an integer
 * @s: This parameter the string to be converted
 * Return: returns the integer value if input valid or -1 if error.
 */

int _erratoi(char *s)
{
	int x = 0;
	unsigned long int converted_integer = 0;

	if (*s == '+')
	{
		s++;  /* TODO: why does this make main return 255? */
	}
	for (x = 0;  s[x] != '\0'; x++)
	{
		if (s[x] >= '0' && s[x] <= '9')
		{
			converted_integer *= 10;
			converted_integer += (s[x] - '0');
			if (converted_integer > INT_MAX)
			{
				return (-1);
			}
		}
		else
			return (-1);
	}
	return (converted_integer);
}

/**
 * print_error - This function prints an error message
 * @info: This refers to the parameter & return info struct
 * @estr: This is the string containing specified error type
 * Return: 0 if no numbers in string, -1 on error
 */

void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - This function prints a decimal, integer, number
 * @input: This parameter is the input
 * @fd: This parameter is the filedescriptor to write to
 *
 * Return: returns the number of characters printed
 */

int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int x, char_count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
	{
		__putchar = _eputchar;
	}
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		char_count++;
	}
	else
	{
		_abs_ = input;
	}
	current = _abs_;
	for (x = 1000000000; x > 1; x /= 10)
	{
		if (_abs_ / x)
		{
			__putchar('0' + current / x);
			char_count++;
		}
		current %= x;
	}
	__putchar('0' + current);
	char_count++;

	return (char_count);
}

/**
 * convert_number - This function is a converter function, a clone of itoa
 * @num: This parameter is the number
 * @base: This parameter is the base
 * @flags: This parameter is argument flags
 *
 * Return: The string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char signage = 0;
	char *p;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		signage = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &buffer[49];
	*p = '\0';

	do	{
		*--p = array[n % base];
		n /= base;
	} while (n != 0);

	if (signage)
	{
		*--p = signage;
	}
	return (p);
}

/**
 * remove_comments - This function replaces first instance of '#' with '\0'
 * @buf: This parameter is the address of the string to modify
 *
 * Return: Always 0;
 */

void remove_comments(char *buf)
{
	int x;

	for (x = 0; buf[x] != '\0'; x++)
	{
		if (buf[x] == '#' && (!x || buf[x - 1] == ' '))
		{
			buf[x] = '\0';
			break;
		}
	}
}
