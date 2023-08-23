#include "shell.h"

/**
 * is_cmd - function that determines if a is executable file.
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 if not.
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - function that duplicates sets of characters.
 * @pathstr: the PATH of string
 * @start: the starting index
 * @stop: the stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0;
	int j;

	for (j = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[j++] = pathstr[i];
	buf[j] = 0;
	return (buf);
}

/**
 * find_path - function that finds this cmd in the PATH string
 * @info: the info struct containing arguments
 * @pathstr: the PATH of the string
 * @cmd: the cmd to find
 *
 * Return: cmd path
 * or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int t = 0, curr = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((my_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[t] || pathstr[t] == ':')
		{
			path = dup_chars(pathstr, curr, t);
			if (!*path)
				my_strcat(path, cmd);
			else
			{
				my_strcat(path, "/");
				my_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[t])
				break;
			curr = t;
		}
		t++;
	}
	return (NULL);
}
