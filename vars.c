#include "shell.h"

/**
 * is_chain - function that checks if char is a chain delimeter
 * @info: the parameter struct containing arguments
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t y = *p;
	char current_char = buf[y];
	char next_char = buf[y + 1];

	if (current_char == '|' && next_char == '|')
	{
		buf[y] = '\0';
		y++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (current_char == '&' && next_char == '&')
	{
		buf[y] = '\0';
		y++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (current_char == ';')
	{
		buf[y] = '\0';
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
	{
		return (0);
	}
	*p = y;
	return (1);
}

/**
 * check_chain - function that checks chain of strings
 * @info: the parameter structure containing arguments
 * @buf: the character buffer
 * @q: address of current position in buffer
 * @i: starting position in buffer
 * @len: length of the buffer
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *q, size_t i, size_t len)
{
	size_t y = *q;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			y = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			y = len;
		}
	}

	*q = y;
}

/**
 * replace_alias - function that replaces tee aliases in the tokenized string.
 * @info: the parameter struct containing arguments.
 *
 * Return: 1 if replaced, 0 if not
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *c;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		c = my_strchr(node->str, '=');
		if (!c)
			return (0);
		c = my_strdup(c + 1);
		if (!c)
			return (0);
		info->argv[0] = c;
	}
	return (1);
}

/**
 * replace_vars - function that replaces environment vars in tokenized string
 * @info: the parameter struct that contains arguments
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!my_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
				my_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!my_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
				my_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
				my_strdup(my_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], my_strdup(""));

	}
	return (0);
}

/**
 * replace_string - function that replaces oldstring with new
 * @old: old string to replaced
 * @new: new string to replace the old string.
 *
 * Return: 1 if replaced, 0 if not.
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
