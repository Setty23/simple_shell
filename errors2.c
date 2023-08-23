#include "shell.h"


/**
 * print_error - custom function that prints an error message
 * @info:  parameter info struct
 * @est: string containing  error
 *
 * Return: 0 if no numbers in string, converted number if worked
 *        -1 on error
 */
void print_error(info_t *info, char *est)
{
	_errputs(info->fname);
	_errputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_errputs(": ");
	_errputs(info->argv[0]);
	_errputs(": ");
	_errputs(est);
}

/**
 * print_d - function tht  prints base 10.
 * @input: input value
 * @fd: filedescriptor to write or modify
 *
 * Return: no of char printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _errputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - a function that converts number.
 * @num: the number
 * @base:  the base
 * @flag: the argument flags
 *
 * Return: the string
 */
char *convert_number(long int num, int base, int flag)
{
	static char *arr;
	static char buffer[50];
	char sign = 0;
	char *pt;
	unsigned long m  = num;

	if (!(flag & CONVERT_UNSIGNED) && num < 0)
	{
		m = -num;
		sign = '-';

	}
	arr = flag & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pt = &buffer[49];
	*pt = '\0';

	do	{
		*--pt = arr[m % base];
		m /= base;
	} while (m != 0);

	if (sign)
		*--pt = sign;
	return (pt);
}

/**
 * remove_comments - function that replaces the first instance of '#' with null
 * @buff: address of the string that will be modified
 *
 * Return: Always 0;
 */
void remove_comments(char *buff)
{
	int j;

	for (j = 0; buff[j] != '\0'; j++)
		if (buff[j] == '#' && (!j || buff[j - 1] == ' '))
		{
			buff[j] = '\0';
			break;
		}
}
