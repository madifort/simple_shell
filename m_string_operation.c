#include "madifort.h"

/**
 * display_string - Print an input string.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void display_string(char *str)
{
	int m;

	if (!str)
		return;

	for (m = 0; str[m] != '\0'; m++)
		write_character(str[m]);
}


/**
 * copy_string - functio to copy a string.
 * @dest: string destination.
 * @src: string source.
 *
 * Return: Pointer to the destination.
 */
char *copy_string(char *dest, char *src)
{
	int m;

	if (dest == src || src == 0)
		return (dest);

	for (m = 0; src[m]; m++)
		dest[m] = src[m];

	dest[m] = 0;
	return (dest);
}

/**
 * duplicate_string - function to duplicate a string.
 * @str: string to be duplicated.
 *
 * Return: Pointer to the duplicated string.
 */
char *duplicate_string(const char *str)
{
	int length = 0;
	char *ret;
	int m;

	if (str == NULL)
		return (NULL);

	for (m = 0; str[m]; m++)
		length++;

	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);

	for (length++, m = 0; length--; m++)
		ret[m] = str[m];

	return (ret);
}


/**
 * write_character - function that write the character c to stdout.
 * @c: The character to print.
 *
 * Return: On success (1).
 * On error (-1) is returned and errno is set appropriately.
 */
int write_character(char c)
{
	static int m;
	static char buf[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || m >= WRITE_BUFFER_SIZE)
	{
		write(1, buf, m);
		m = 0;
	}

	if (c != BUFFER_FLUSH)
		buf[m++] = c;

	return (1);
}

