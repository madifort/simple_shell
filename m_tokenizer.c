#include "madifort.h"

/**
 * count_words - Count the number of words in a string.
 * @str: Input string.
 * @d: The delimiter string.
 *
 * Return: Number of words.
 */
static int count_words(char *str, char *d)
{
	int m, numwords = 0;

	for (m = 0; str[m] != '\0'; ++m)
	{
		if (!is_delimiter(str[m], d) && (is_delimiter(str[m + 1], d) || !str[m + 1]))
			numwords++;
	}

	return (numwords);
}

/**
 * allocate_and_copy - Allocate memory and copy a substring.
 * @str: Input string.
 * @m: Current position in the string.
 * @f: Number of characters to copy.
 *
 * Return: Pointer to the copied substring.
 */
static char *allocate_and_copy(char *str, int m, int f)
{
	char *substring = malloc((f + 1) * sizeof(char));

	if (!substring)
		return (NULL);

	for (int x = 0; x < f; ++x)
		substring[x] = str[m++];

	substring[f] = '\0';

	return (substring);
}

/**
 * fill_token_array - Fill the token array based on inputstring and delimiters.
 * @str: Input string.
 * @d: The delimiter string.
 * @s: Array to store tokens.
 * @numwords: Number of words.
 *
 * Return: 0 on success, -1 on failure.
 */
static int fill_token_array(char *str, char *d, char **s, int numwords)
{
	int m, p, f;

	for (m = 0, p = 0; p < numwords; ++p)
	{
		while (is_delimiter(str[m], d))
			++m;

		f = 0;
		for (; !is_delimiter(str[m + f], d) && str[m + f]; ++f);

		s[p] = allocate_and_copy(str, m, f);

		if (!s[p])
		{
			for (f = 0; f < p; ++f)
				free(s[f]);
			return (-1);
		}

		m += f;
	}

	s[p] = NULL;
	return (0);
}

/**
 * tokenize_string - Splits a string into words, ignoring repeated delimiters.
 * @str: Input string.
 * @d: The delimiter string.
 *
 * Return: A pointer to an array of strings, or NULL on failure.
 */
char **tokenize_string(char *str, char *d)
{
	int numwords;
	char **s;

	if (str == NULL || str[0] == '\0')
		return (NULL);
	if (!d)
		d = " ";

	numwords = count_words(str, d);

	if (numwords == 0)
		return (NULL);

	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);

	if (fill_token_array(str, d, s, numwords) == -1)
	{
		free(s);
		return (NULL);
	}

	return (s);
}

/**
 * tokenize_string2 - Splits a string into words.
 * @str: Input string.
 * @d: The delimiter.
 *
 * Return: A pointer to an array of strings, or NULL on failure.
 */
char **tokenize_string2(char *str, char d)
{
	int numwords;
	char **s;

	if (str == NULL || str[0] == '\0')
		return (NULL);

	numwords = count_words(str, &d);

	if (numwords == 0)
		return (NULL);

	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);

	if (fill_token_array(str, &d, s, numwords) == -1)
	{
		free(s);
		return (NULL);
	}

	return (s);
}

v
