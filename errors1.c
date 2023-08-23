#include "shell.h"


/**
 * write_stderr - function that writes the character c to stderr
 * @c: The character to be written
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is printed.
 */
void write_stderr(char *c)
{
	write(STDERR_FILENO, c, my_strlen(c));
}

/**
 * _errputchar - custom function that writes the char c to stderr.
 * @c: The char to written
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno    printed.
 */
int _errputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *_errputs - function that prints an input string
 * @str: the string that will be printed.
 *
 */
void _errputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_errputchar(str[i]);
		i++;
	}
}

/**
 * fd_put - custom function that writes the character c to  fd  file descripto.
 * @c:  character to be printed
 * @fd:  file descriptor
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is returned.
 */
int fd_put(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *fd_puts - custom function print input str.
 * @str: the string to  print
 * @fd:  filedescriptor to write or modify
 *
 * Return: the number of chars put
 */
int fd_puts(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += fd_put(*str++, fd);
	}
	return (i);
}
