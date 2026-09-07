#include <stdlib.h>
#include "llist.h"

/**
 * llist_create - Create an empty linked list
 *
 * Return: Pointer to the new list, or NULL on failure
 */
llist_t *llist_create(void)
{
	llist_t *list;

	list = malloc(sizeof(*list));
	if (list == NULL)
		return (NULL);

	list->head = NULL;
	list->tail = NULL;
	list->size = 0;

	return (list);
}

/**
 * llist_add_node - Add a node to a linked list
 * @list: Linked list
 * @elem: Element to store
 * @dir: Direction
 *
 * Return: 0 on success, -1 on failure
 */
int llist_add_node(llist_t *list, void *elem, int dir)
{
	llist_node_t *node;

	if (list == NULL)
		return (-1);

	node = malloc(sizeof(*node));
	if (node == NULL)
		return (-1);

	node->elem = elem;

	if (list->head == NULL)
	{
		node->next = NULL;
		node->prev = NULL;
		list->head = node;
		list->tail = node;
	}
	else if (dir == ADD_NODE_FRONT)
	{
		node->prev = NULL;
		node->next = list->head;
		list->head->prev = node;
		list->head = node;
	}
	else
	{
		node->next = NULL;
		node->prev = list->tail;
		list->tail->next = node;
		list->tail = node;
	}

	list->size++;

	return (0);
}

/**
 * llist_get_head - Get the first element
 * @list: Linked list
 *
 * Return: First element, or NULL
 */
void *llist_get_head(llist_t const *list)
{
	if (list == NULL || list->head == NULL)
		return (NULL);

	return (list->head->elem);
}

/**
 * llist_pop - Remove and return the first element
 * @list: Linked list
 *
 * Return: First element, or NULL
 */
void *llist_pop(llist_t *list)
{
	llist_node_t *node;
	void *elem;

	if (list == NULL || list->head == NULL)
		return (NULL);

	node = list->head;
	elem = node->elem;

	list->head = node->next;
	if (list->head != NULL)
		list->head->prev = NULL;
	else
		list->tail = NULL;

	list->size--;
	free(node);

	return (elem);
}

/**
 * llist_destroy - Destroy a linked list
 * @list: Linked list
 * @free_elem: Whether to free elements
 * @dtor: Element destructor
 */
void llist_destroy(llist_t *list, size_t free_elem, node_dtor_t dtor)
{
	llist_node_t *node;
	llist_node_t *next;

	if (list == NULL)
		return;

	node = list->head;

	while (node != NULL)
	{
		next = node->next;

		if (free_elem && dtor != NULL)
			dtor(node->elem);

		free(node);
		node = next;
	}

	free(list);
}
