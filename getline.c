#include "shell.h"

/**
 * input_buf - This function buffers chained commands
 * @info: This is the parameter struct
 * @buf: This is the address of buffer
 * @len:This is the  address of len var
 *
 * Return: The bytes read
 */

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t bytes_read = 0;
	size_t buffer_len = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		bytes_read = getline(buf, &buffer_len, stdin);
#else
		bytes_read = _getline(info, buf, &buffer_len);
#endif
		if (bytes_read > 0)
		{
			if ((*buf)[bytes_read - 1] == '\n')
			{
				(*buf)[bytes_read - 1] = '\0'; /* remove trailing newline */
				bytes_read--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = bytes_read;
				info->cmd_buf = buf;
			}
		}
	}
	return (bytes_read);
}

/**
 * get_input - This function gets a line minus the newline
 * @info: This is a parameter struct
 *
 * Return: The bytes read
 */

ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t x, y, len;
	ssize_t inputbuf_result = 0;
	char **buf_p = &(info->arg), *char_p;

	_putchar(BUF_FLUSH);
	inputbuf_result = input_buf(info, &buf, &len);

	if (inputbuf_result == -1)
	{
		return (-1);
	}
	if (len)
	{
		y = x;
		char_p = buf + x;

		check_chain(info, buf, &y, x, len);
		while (y < len)
		{
			if (is_chain(info, buf, &y))
			{
				break;
			}
			y++;
		}

		x = y + 1;
		if (x >= len)
		{
			x = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = char_p;
		return (_strlen(char_p));
	}

	*buf_p = buf;
	return (inputbuf_result);
}

/**
 * read_buf - This function reads a buffer
 * @info: This points to struct type info_t
 * @buf: This parameter points to a character buffer
 * @i: This parameter points to the size variable
 *
 * Return: number of bytes read
 */

ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t read_result = 0;

	if (*i)
	{
		return (0);
	}
	read_result = read(info->readfd, buf, READ_BUF_SIZE);

	if (read_result >= 0)
	{
		*i = read_result;
	}
	return (read_result);
}

/**
 * _getline - This function gets the next line of input from STDINP
 * @info: This points to struct type info_t
 * @ptr: This is address of pointer to buffer (preallocated or NULL)
 * @length: The size of preallocated ptr buffer if its not NULL
 *
 * Return: buffer size
 */

int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t x, len;
	size_t q;
	ssize_t readbuf_result = 0, buffer_size = 0;
	char *p = NULL, *new_p = NULL, *ch;

	p = *ptr;
	if (p && length)
	{
		buffer_size = *length;
	}
	if (x == len)
		x = len = 0;

	readbuf_result = read_buf(info, buf, &len);
	if (readbuf_result == -1 || (readbuf_result == 0 && len == 0))
		return (-1);

	ch = _strchr(buf + x, '\n');
	q = ch ? 1 + (unsigned int)(ch - buf) : len;
	new_p = _realloc(p, buffer_size, buffer_size ? buffer_size + q : q + 1);

	if (new_p == NULL)
		return (p ? free(p), -1 : -1);

	if (buffer_size)
		_strncat(new_p, buf + x, q - x);
	else
		_strncpy(new_p, buf + x, q - x + 1);

	buffer_size += q - x;
	x = q;
	p = new_p;

	if (length)
		*length = buffer_size;
	*ptr = p;
	return (buffer_size);
}

/**
 * sigintHandler - This function blocks ctrl-C
 * @sig_num: This parameter is the signal number
 * Return: void
 */

void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
