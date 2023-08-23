#include "shell.h"

/**
 * my_env - function that prints the current environment
 * @info: Structure that has potential arguments.
 * Return: Always 0
 */
int my_env(info_t *info)
{
	printlist_str(info->env);
	return (0);
}

/**
 * get_env - function that gets the value of an environ variable
 * @info: Structure tht has possible arguments
 * @num: environent var name
 *
 * Return: value
 */
char *get_env(info_t *info, const char *num)
{
	list_t *node = info->env;
	char *x;

	while (node)
	{
		x = starts_with(node->str, num);
		if (x && *x)
			return (x);
		node = node->next;
	}
	return (NULL);
}

/**
 * populate_env_list - custom function that populates env. linked list.
 * @info: Pointer to the structure that holds arguments and maintains state.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		add_node_end(&node, environ[j], 0);
	info->env = node;
	return (0);
}
