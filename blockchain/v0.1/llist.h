#ifndef LLIST_H
#define LLIST_H

#include <stddef.h>

/**
 * struct llist_node_s - Linked list node
 * @next: Pointer to the next node
 * @prev: Pointer to the previous node
 * @elem: Element stored in the node
 */
typedef struct llist_node_s
{
	struct llist_node_s *next;
	struct llist_node_s *prev;
	void *elem;
} llist_node_t;

/**
 * struct llist_s - Linked list
 * @head: First node
 * @tail: Last node
 * @size: Number of nodes
 */
typedef struct llist_s
{
	llist_node_t *head;
	llist_node_t *tail;
	size_t size;
} llist_t;

llist_t *llist_create(void);
int llist_add_node(llist_t *list, void *elem, int dir);
void *llist_get_head(llist_t const *list);
void llist_destroy(llist_t *list, void (*free_func)(void *elem));

#define ADD_NODE_FRONT 0
#define ADD_NODE_BACK 1

#endif /* LLIST_H */
