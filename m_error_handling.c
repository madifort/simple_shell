#include "madifort.h"

/**
 * display_error- Prints a string to stderr.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void display_error(char *str)
{
	int m = 0;

	if (!str)
		return;

	while (str[m] != '\0')
	{
		display_error_character(str[m]);
		m++;
	}
}

/**
 * display_error_character - Writes a character to stderr.
 * @c: The character to print.
 *
 * Return: On success (1), On error (-1) is returned and errno is set approp.
 */
int display_error_character(char c)
{
	static int m;
	static char buf[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || m >= WRITE_BUFFER_SIZE)
	{
		write(2, buf, m);
		m = 0;
	}
	if (c != BUFFER_FLUSH)
		buf[m++] = c;

	return (1);
}

/**
 * write_to_fd - Writes a character to a given file descriptor.
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 *
 * Return: On success (1), On error (-1) is returned, and errno is set approp.
 */
int write_to_fd(char c, int fd)
{
	static int m;
	static char buf[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || m >= WRITE_BUFFER_SIZE)
	{
		write(fd, buf, m);
		m = 0;
	}
	if (c != BUFFER_FLUSH)
		buf[m++] = c;

	return (1);
}

/**
 * write_string_to_fd - Prints a string to a given file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters put.
 */
int write_string_to_fd(char *str, int fd)
{
	int m = 0;

	if (!str)
		return (0);

	while (*str)
	{
		m += write_to_fd(*str++, fd);
	}

	return (m);
}

