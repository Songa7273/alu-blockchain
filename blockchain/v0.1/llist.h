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
 * node_dtor_t - Node destructor function
 */
typedef void (*node_dtor_t)(void *);

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

#define ADD_NODE_FRONT 0
#define ADD_NODE_BACK 1
#define ADD_NODE_REAR ADD_NODE_BACK

llist_t *llist_create(void);
int llist_add_node(llist_t *list, void *elem, int dir);
void *llist_get_head(llist_t const *list);
void *llist_pop(llist_t *list);
void llist_destroy(llist_t *list, size_t free_elem, node_dtor_t dtor);

#endif /* LLIST_H */
