#include "madifort.h"

/**
 * convert_error_to_integer - function converts a string to an integer
 * @s: the string to be converted
 *
 * Return: if no numbers in string (0) is returned,  otherwise (-1) on error
 *
 */
int convert_error_to_integer(char *s)
{
	int m = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++; /* TODO: why does this make main return 255? */

	for (m = 0; s[m] != '\0'; m++)
	{
		if (s[m] >= '0' && s[m] <= '9')
		{
			result *= 10;
			result += (s[m] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * display_custom_error - function prints an error message
 * @estr: string containing specified error type
 * @info: the parameter & return info struct
 *
 */
void display_custom_error(info_t *info, char *estr)
{
	display_error(info->fname);
	display_error(": ");
	display_integer(info->line_count, STDERR_FILENO);
	display_error(": ");
	display_error(info->argv[0]);
	display_error(": ");
	display_error(estr);
}

/**
 * display_integer - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int display_integer(int input, int fd)
{
	int (*_write_character)(char) = write_character;
	int m, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		_write_character = display_error_character;
	if (input < 0)
	{
		_abs_ = -input;
		_write_character('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;

	for (m = 1000000000; m > 1; m /= 10)
	{
		if (_abs_ / m)
		{
			_write_character('0' + current / m);
			count++;
		}
		current %= m;
	}
	_write_character('0' + current);
	count++;

	return (count);
}

/**
 * convert_integer_to_string - converter function,
 *
 * @num: number
 * @flags: argument flags
 * @base: base
 *
 * Return: string
 */
char *convert_integer_to_string(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;

	return (ptr);
}

/**
 * remove_comments_from_string - func. replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 */
void remove_comments_from_string(char *buf)
{
	int m;

	for (m = 0; buf[m] != '\0'; m++)
		if (buf[m] == '#' && (!m || buf[m - 1] == ' '))
		{
			buf[m] = '\0';
			break;
		}
}


