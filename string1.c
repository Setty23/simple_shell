#include "shell.h"

/**
 * my_strlen - function that prints length of a string.
 * @r:  string whose length to be printed
 *
 * Return: int length of string
 */
int my_strlen(char *r)
{
	int j = 0;

	if (!r)
		return (0);

	while (*r++)
		j++;
	return (j);
}
/**
 * starts_with - function that checks whether  the needle begins with haystack
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
	char *p = desti;

	while (*desti)
		desti++;
	while (*srce)
		*desti++ = *srce++;
	*desti = *srce;
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

