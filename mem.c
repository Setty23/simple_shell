#include "shell.h"

/**
 * bfree - function that frees thepointer and NULLs the address
 * @ptr: address of the pointer to free
 *
 * Return: 1 if freed, if not return 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
