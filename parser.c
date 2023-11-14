#include "shell.h"

/**
 * is_cmd - This function determines if file is executable command
 * @info: This parameter is the info struct
 * @path: This parameter is the path to the file
 * Return: 1 if true, else 0
 */

int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;

	if (path == NULL || stat(path, &st))
	{
		return (0);
	}

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - This function duplicates characters
 * @pathstr: This parameter is the PATH string
 * @start: This parameter is the starting index
 * @stop: This parameter is the stopping index
 * Return: The pointer to the new buffer
 */

char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int x = 0, y = 0;

	for (y = 0, x = start; x < stop; x++)
	{
		if (pathstr[x] != ':')
		{
			buf[y++] = pathstr[x];
		}
	}
	buf[y] = 0;
	return (buf);
}

/**
 * find__path - This function finds this cmd in the PATH string
 * @info: This parameter is the info struct
 * @pathstr: This parameter is the PATH string
 * @cmd: This parameter is the cmd to find
 * Return: returns the full path of cmd if found or NULL
 */

char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int x = 0, current_pos = 0;
	char *path_point;

	if (pathstr == NULL)
	{
		return (NULL);
	}
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[x] || pathstr[x] == ':')
		{
			path_point = dup_chars(pathstr, current_pos, x);
			if (!*path_point)
			{
				_strcat(path_point, cmd);
			}
			else
			{
				_strcat(path_point, "/");
				_strcat(path_point, cmd);
			}
			if (is_cmd(info, path_point))
			{
				return (path_point);
			}
			if (!pathstr[x])
			{
				break;
			}
			current_pos = x;
		}
		x++;
	}
	return (NULL);
}
