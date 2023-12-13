#include "madifort.h"

/**
 * copy_n_characters - Function copies a string.
 * @dest: The destination string to be copied to.
 * @src: The source string.
 * @n: The number of characters to be copied.
 *
 * Return: The concatenated string.
 */
char *copy_n_characters(char *dest, char *src, int n)
{
	int m, j;
	char *str = dest;

	for (m = 0, j = 0; src[m] != '\0' && m < n - 1; m++)
	{
		dest[m] = src[m];
		j = m;
	}

	for (j = j + 1; j < n; j++)
		dest[j] = '\0';

	return (str);
}

/**
 * concatenate_n_characters - Concatenates two strings.
 * @dest: The first string.
 * @src: The second string.
 * @n: The number of bytes to be maximally used.
 *
 * Return: The concatenated string.
 */
char *concatenate_n_characters(char *dest, char *src, int n)
{
	char *str = dest;
	int j, m;

	for (m = 0, j = 0; dest[m] != '\0'; m++)
		j = m;

	for (m = 0, j = j + 1; src[m] != '\0' && m < n; m++, j++)
		dest[j] = src[m];

	if (j < n)
		dest[j] = '\0';

	return (str);
}

/**
 * find_character - Function locates a character in a string.
 * @str: String to be parsed.
 * @c: Character to be looked for.
 *
 * Return: A pointer to the memory area str.
 */
char *find_character(char *str, char c)
{
	char *start = str;

	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}


