#include "shell.h"

/**
 * my_strlen - function that prints length of a string.
 * @c:  string whose length to be printed
 *
 * Return: int length of string
 */
int my_strlen(char *c)
{
	int x = 0;

	if (!c)
		return (0);

	while (*c++)
		x++;
	return (x);
}
/**
 * starts_with - function that checks whether the needle begins with haystack
 * @haystack: string to be searched for.
 * @needle: the sub string to be sought.
 *
 * Return: address of next of haystack or NULL if otherwise
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}
/**
 * my_strcat - function that concatenates dest and src
 * @dest: destination b uffer.
 * @src:  source bu ffer
 *
 * Return: ptr to dest buffer
 */
char *my_strcat(char *dest, char *src)
{
	char *p = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (p);
}
/**
 * my_strcmp -  function that compares of two strangs.
 * @str1:  first string
 * @str2:  second string
 *
 * Return: negative if str1 < str2,
 *	positive if str1 > str2,
 *	zero if str1 == str2
 */
int my_strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

