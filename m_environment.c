#include "madifort.h"

/**
 * display_environment - Function prints the current environment.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int display_environment(info_t *info)
{
	print_string_list(info->env);
	return (0);
}

/**
 * get_environment_var - Function gets the value of an environment variable.
 * @info: Structure containing potential arguments.
 * @name: Env variable name.
 *
 * Return: The value of the variable or NULL if not found.
 */
char *get_environment_var(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with_substring(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * set_environment_var - Initial. a new environ. var or modify an existing one.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int set_environment_var(info_t *info)
{
	if (info->argc != 3)
	{
		display_error("Incorrect number of arguments\n");
		return (1);
	}
	if (set_variable_environment(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * unset_environment_var - Removes an environment variable.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int unset_environment_var(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		display_error("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		unset_variable_environment(info, info->argv[i]);

	return (0);
}

/**
 * populate_environment_list - Populates the environment linked list.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int populate_environment_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_to_list_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}


