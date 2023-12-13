#include "madifort.h"

/**
 * string_length - Returns the length of a string.
 * @str: The string whose length is to be determined.
 *
 * Return: The integer length of the string.
 */
int string_length(char *str)
{
	int m = 0;

	if (!str)
		return (0);

	for (; *str; str++)
		m++;

	return (m);
}

/**
 * compare_strings - Performs lexicographic comparison of two strings.
 * @str1: Defines the first string.
 * @str2: Defines the second string.
 *
 * Return: Negative if str1 < str2, +ive if str1 > str2, zero if str1 == str2.
 */
int compare_strings(char *str1, char *str2)
{
	for (; *str1 && *str2; str1++, str2++)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
	}

	return (*str1 - *str2);
}

/**
 * starts_with_substring - Checks if the madi starts with the fortstack.
 * @fortstack: String to search.
 * @madi: The substring to find
 *
 * Return: Address of the next character of fortstack or NULL.
 */
char *starts_with_substring(const char *fortstack, const char *madi)
{
	for (; *madi; madi++, fortstack++)
		if (*madi != *fortstack)
			return (NULL);

	return ((char *)fortstack);
}

/**
 * concatenate_strings - Concatenates two strings.
 * @dest: The destination buffer.
 * @src: The source buffer.
 *
 * Return: Pointer to the destination buffer.
 */
char *concatenate_strings(char *dest, char *src)
{
	char *ret = dest;

	for (; *dest; dest++)
		;

	for (; *src; src++, dest++)
		*dest = *src;

	*dest = *src;

	return (ret);
}


