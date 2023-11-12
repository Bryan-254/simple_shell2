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
	static char *buf; /* the ';' command chain buffer */
	static size_t x, y, len;
	ssize_t inputbuf_result = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	inputbuf_result = input_buf(info, &buf, &len);

	if (inputbuf_result == -1) /* EOF */
	{
		return (-1);
	}
	if (len)	/* we have commands left in the chain buffer */
	{
		y = x; /* init new iterator to current buf position */
		p = buf + x; /* get pointer for return */

		check_chain(info, buf, &j, x, len);
		while (y < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &y))
			{
				break;
			}
			y++;
		}

		x = y + 1; /* increment past nulled ';'' */
		if (x >= len) /* reached end of buffer? */
		{
			x = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (inputbuf_result); /* return length of buffer from _getline() */
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
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t x, len;
	size_t k;
	ssize_t readbuf_result = 0, buffer_size = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		buffer_size = *length;
	if (x == len)
		x = len = 0;

	readbuf_result = read_buf(info, buf, &len);
	if (readbuf_result == -1 || (readbuf_result == 0 && len == 0))
		return (-1);

	c = _strchr(buf + x, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, buffer_size, buffer_size ? buffer_size + k : k + 1);

	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + x, k - x);
	else
		_strncpy(new_p, buf + x, k - x + 1);

	buffer_size += k - x;
	x = k;
	p = new_p;

	if (length)
		*length = buffer_size;
	*ptr = p;
	return (buffer_size);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
