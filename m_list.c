#include "madifort.h"

/**
 * add_node_to_list - function adds a node to the start of the list.
 * @head: Address of pointer to head node.
 * @str: Str field of the node.
 * @num: Node index used by history.
 *
 * Return: Pointer to the new head.
 */
list_t *add_node_to_list(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);

	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);

	set_memory((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;

	if (str)
	{
		new_head->str = duplicate_string(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}

	new_head->next = *head;
	*head = new_head;

	return (new_head);
}

/**
 * add_node_to_list_end - function adds a node to the end of the list.
 * @head: Address of pointer to head node.
 * @str: Str field of the node.
 * @num: Node index used by history.
 *
 * Return: Pointer to the new node.
 */
list_t *add_node_to_list_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	set_memory((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;

	if (str)
	{
		new_node->str = duplicate_string(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}

/**
 * print_string_list - function prints only the str ele. of list_t linked list.
 * @h: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t print_string_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		display_string(h->str ? h->str : "(nil)");
		display_string("\n");
		h = h->next;
		i++;
	}

	return (i);
}

/**
 * delete_node_at_index_from_list - Deletes a node at the given index.
 * @head: Address of pointer to the first node.
 * @index: Index of the node to delete.
 *
 * Return: on success (1) is returned, (0) on failure.
 */
int delete_node_at_index_from_list(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);

		return (1);
	}

	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);

			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}

	return (0);
}

/**
 * free_string_list - Function frees all nodes of a list.
 * @head_ptr: Address of pointer to head node.
 *
 * Return: void
 */
void free_string_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;

	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}

	*head_ptr = NULL;
}

