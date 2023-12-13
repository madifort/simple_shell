#include "madifort.h"

/**
 * is_variable_chain - funct. test if the curr. char.in buff is a chain delimi.
 * @info: The parameter struct.
 * @buf: The character buffer.
 * @p: Address of the current position in buf.
 *
 * Return: 1 if a chain delimiter, 0 otherwise.
 */
int is_variable_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* Found end of this command */
	{
		buf[j] = 0; /* Replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);

	*p = j;
	return (1);
}

/**
 * check_variable_chain - func.Check if we cont. chaining based on last status.
 * @info: The parameter struct.
 * @buf: The character buffer.
 * @p: Address of the current position in buf.
 * @i: Starting position in buf.
 * @len: Length of buf.
 *
 * Return: Void.
 */
void check_variable_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * alias_replaced - Replaces aliases in the tokenized string.
 * @info: The parameter struct.
 *
 * Return: if replaced (1) is returned, (0) otherwise.
 */
int alias_replaced(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = find_node_starting_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = find_character(node->str, '=');
		if (!p)
			return (0);
		p = duplicate_string(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * variables_replaced - Replaces variables in the tokenized string.
 * @info: The parameter struct.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int variables_replaced(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!compare_strings(info->argv[i], "$?"))
		{
			replace_string_in_array(&(info->argv[i]),
				duplicate_string(convert_integer_to_string(info->status, 10, 0)));
			continue;
		}
		if (!compare_strings(info->argv[i], "$$"))
		{
			replace_string_in_array(&(info->argv[i]),
				duplicate_string(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = find_node_starting_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string_in_array(&(info->argv[i]),
				duplicate_string(find_character(node->str, '=') + 1));
			continue;
		}
		replace_string_in_array(&info->argv[i], duplicate_string(""));
	}
	return (0);
}

/**
 * replace_string_in_array - Replaces a string.
 * @old: Address of the old string.
 * @new: New string.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_string_in_array(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}


