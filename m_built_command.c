#include "madifort.h"

/**
 * display_history - Displays the command history list with line numbers.
 * @info: Structure containing potential arguments.
 * Return: Always (0)
 */
int display_history(info_t *info)
{
	print_integer_list(info->history);
	return (0);
}

/**
 * unset_alias - Unsets an alias for the given string.
 * @info: Parameter struct.
 * @str: The string alias.
 * Return: Always 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = find_character(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index_from_list(&(info->alias),
										  get_node_index_in_list(info->alias, find_node_starting_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - Sets an alias for the given string.
 * @info: Parameter struct.
 * @str: The string alias.
 * Return: Always 0 on success, 1 on error.
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = find_character(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_to_list_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Prints an alias string.
 * @node: The alias node.
 * Return: Always 0 on success, 1 on error.
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = find_character(node->str, '=');
		for (a = node->str; a <= p; a++)
			write_character(*a);
		write_character('\'');
		display_string(p + 1);
		display_string("'\n");
		return (0);
	}
	return (1);
}

/**
 * manage_alias - Mimics the alias builtin (man alias).
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int manage_alias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = find_character(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(find_node_starting_with(info->alias, info->argv[i], '='));
	}

	return (0);
}


