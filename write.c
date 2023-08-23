#include "shell.h"

/**
 * write_stdout - function that writes a message to stdout
 * @msg: The message to be written
 *
 * Return: None
 */
void write_stdout(char *msg)
{
	write(STDOUT_FILENO, msg, strlen(msg));
}
