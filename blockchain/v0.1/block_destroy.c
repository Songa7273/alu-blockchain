#include <stdlib.h>

#include "blockchain.h"

/**
 * block_destroy - Delete a Block
 * @block: Pointer to the Block to delete
 */
void block_destroy(block_t *block)
{
	if (block == NULL)
		return;

	if (block->data.buffer != NULL)
		free(block->data.buffer);

	free(block);
}
