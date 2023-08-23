#include "shell.h"

/**
 * is_delimeter - checks if character is a delimeter
 * @c: character to checked
 * @delim: delimeter string
 * Return: 1 if true, 0 if not
 */
int is_delimeter(char c, char *delim)
{
	size_t i;
	size_t delim_len = my_strlen(delim);

	for (i = 0; i < delim_len; i++)
	{
		if (c == delim[i])
			return (1);
	}
	return (0);
}

/**
 * my_isalpha - looks for alphabetic character
 * @c: The character to be checked.
 *Return: 1 if d is alphabetic, 0 if not
 */

int my_isalpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * my_atoi - converts string to an integer.
 * @str: The input string to be converted.
 *
 * Return: 0 if it is still string, if converted number
 */

int my_atoi(char *str)
{
	int i;
	int flag = 0, output;
	int sign = 1;
	unsigned int result = 0;

	for (i = 0;  str[i] != '\0' && flag != 2; i++)
	{
		if (str[i] == '-')
		{
			sign *= -1;
		}

		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			result = result * 10 + (str[i] - '0');
		if (result > INT_MAX)
			return (-1);
		}
		else if (flag == 1)
		{
			flag = 2;
		}
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
