#include "shell.h"

/**
 * hsh - the main shell loop function
 * @info: the parameter nd  return info structure
 * @av: the argument vector from main function.
 *
 * Return: 0 on success, 1 if it is error,
 * or NULL
 */

int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		init_info(info);
		if (interactive(info))
			_puts("$ ");
		_errputchar(BUF_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			set_info(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - function that finds the builtin command.
 * @info: the parameter and return info structure.
 *
 * Return: -1 if builtin is not found,
 *	0 if builtin executed successfully,
 *	1 if builtin found but not successful,
 *	-2 if builtin signals exit()
 */

int find_builtin(info_t *info)
{
	int x, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", my_exit},
		{"env", my_env},
		{"help", my_help},
		{"history", my_history},
		{"cd", my_cd},
		{"alias", my_alias},
		{NULL, NULL}
	};

	for (x = 0; builtintbl[x].type; x++)
		if (my_strcmp(info->argv[0], builtintbl[x].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[x].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - function that finds a command in path.
 * @info: the parameter  return info structure
 *
 * Return: void
 */

void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, j;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, j = 0; info->arg[i]; i++)
		if (!is_delimeter(info->arg[i], " \t\n"))
			j++;
	if (!j)
		return;

	path = find_path(info, get_env(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		exec_cmd(info);
	}
	else
	{
		if ((interactive(info) || get_env(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			exec_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * exec_cmd - function that forks a an exec cmd
 * @info: the parameter & return info struct containing arguments
 *
 * Return: void
 */
void exec_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
