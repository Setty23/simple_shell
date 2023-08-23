#include "shell.h"

/**
 ** my_strncat - function that concatenates two strings
 * @dest: first string
 * @src: second string
 * @b: the no of bytes to be used
 *Return: concatenated string
 */
char *my_strncat(char *dest, char *src, int b)
{
	int i = 0;
	int j = 0;
	char *d = dest;

	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < b)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < b)
		dest[i] = '\0';
	return (d);
}

/**
 ** my_strchr - function tat Locate the first occurrence of a char in a str.
 * @str: the string to search.
 * @c: character to be located.
 *Return: (str)  ptr to  memory area
 */
char *my_strchr(char *str, char c)
{
	while (*str != '\0')
	{
		if (*str == c)
		{
			return (str);
		}
		str++;
	}
	return (NULL);
}

/**
 * my_strncpy - Custom implementation of strncpy function
 * @dest: Pointer to the destination buffer
 * @src: Pointer to the source string
 * @n: Maximum number of characters to copy
 *
 * Return: Pointer to the destination buffer (dest)
 */

char *my_strncpy(char *dest, const char *src, size_t n)
{
	char *d = dest;

    /* Copy at most n characters from src to dest */
	while (*src && n > 0)
	{
		*d++ = *src++;
		n--;
	}

    /* Fill remaining space in dest with null characters if needed */
	while (n > 0)
	{
		*d++ = '\0';
		n--;
	}
	return (dest);
}
