#include "shell.h"

/**
 * unset_alias - custom function tht sets alias to string.
 * @info: it is a parameter struct.
 * @str: it is the string alias
 *
 * Return: Always 0 on success, or 1 if not
 */
int unset_alias(info_t *info, char *str)
{
	char *x, c;
	int re;

	x = my_strchr(str, '=');
	if (!x)
		return (1);
	c = *x;
	*x = 0;
	re = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*x = c;
	return (re);
}

/**
 * set_alias - function that sets alias to string
 * @info: is the parameter struct
 * @str1: is the string alias
 *
 * Return: Always 0 on success, 1 upon  error
 */
int set_alias(info_t *info, char *str1)
{
	char *x;

	x = my_strchr(str1, '=');
	if (!x)
		return (1);
	if (!*++x)
		return (unset_alias(info, str1));

	unset_alias(info, str1);
	return (add_node_end(&(info->alias), str1, 0) == NULL);
}

/**
 * print_alias - custom function that prints an alias string.
 * @node1: is the alias node
 *
 * Return: Always 0 on success, 1 upon error
 */
int print_alias(list_t *node1)
{
	char *x = NULL, *a = NULL;

	if (node1)
	{
		x = my_strchr(node1->str, '=');
		for (a = node1->str; a <= x; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(x + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * my_alias - custom function that copies the alias in the builtin.
 * @info: Structure potential arguments maintains function prototype.
 *  Return: Always 0
 */
int my_alias(info_t *info)
{
	int i = 0;
	char *x = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		x = my_strchr(info->argv[i], '=');
		if (x)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
