#include "shell.h"

/**
 * get_environ - a function that returns the string copy of the environ.
 * @info: Structure tht has potential arguments.
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}


