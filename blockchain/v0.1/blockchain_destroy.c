#include <stdlib.h>

#include "blockchain.h"

/**
 * blockchain_destroy - Delete a Blockchain and all its Blocks
 * @blockchain: Pointer to the Blockchain structure to delete
 */
void blockchain_destroy(blockchain_t *blockchain)
{
	block_t *block;

	if (blockchain == NULL)
		return;

	if (blockchain->chain != NULL)
	{
		/* Destroy all blocks in the chain */
		while ((block = (block_t *)llist_pop(blockchain->chain)) != NULL)
		{
			block_destroy(block);
		}

		llist_destroy(blockchain->chain, 0, NULL);
	}

	free(blockchain);
}
