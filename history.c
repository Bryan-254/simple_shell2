#include "shell.h"

/**
 * get_history_file - This function gets the history file
 * @info: This is the parameter struct
 *
 * Return: The allocated string containing history file
 */

char *get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (dir == NULL)
	{
		return (NULL);
	}

	buf = malloc(sizeof(char) * (_strlen(HIST_FILE) + _strlen(dir) + 2));

	if (buf == NULL)
	{
		return (NULL);
	}
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - This function creates a file, or appends to existing file
 * @info: This is the parameter struct
 *
 * Return: 1 if successful, else -1
 */

int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (filename == NULL)
	{
		return (-1);
	}

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
	{
		return (-1);
	}
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - This function reads history from file
 * @info: This is the parameter struct
 *
 * Return: The histcount on success, else 0
 */

int read_history(info_t *info)
{
	int x, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (filename == NULL)
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (buf == NULL)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (x = 0; x < fsize; x++)
		if (buf[x] == '\n')
		{
			buf[x] = 0;
			build_history_list(info, buf + last, linecount++);
			last = x + 1;
		}
	if (last != x)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - This function adds entry to history linked list
 * @info: This is the Structure containing potential arguments.
 * @buf: This parameter is the buffer
 * @linecount: This is the history linecount
 *
 * Return: Always 0
 */

int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
	{
		node = info->history;
	}
	add_node_end(&node, buf, linecount);

	if ((info->history) == NULL)
	{
		info->history = node;
	}
	return (0);
}

/**
 * renumber_history - This function renumbers history linked list after changes
 * @info: This is the structure containing potential arguments
 *
 * Return: the new linecount/histcount
 */

int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int x = 0;

	while (node)
	{
		node->num = x++;
		node = node->next;
	}
	return (info->histcount = x);
}
