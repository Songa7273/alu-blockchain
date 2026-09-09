#include <stdlib.h>
#include <string.h>
#include "blockchain.h"

/**
 * create_genesis_block - Helper function to allocate and initialize
 *                        the static Genesis block
 *
 * Return: Pointer to the created genesis block, or NULL on failure
 */
static block_t *create_genesis_block(void)
{
	block_t *genesis = calloc(1, sizeof(block_t));

	if (!genesis)
		return (NULL);

	genesis->info.index = GENESIS_INDEX;
	genesis->info.difficulty = GENESIS_DIFFICULTY;
	genesis->info.timestamp = GENESIS_TIMESTAMP;
	genesis->info.nonce = GENESIS_NONCE;
	memset(genesis->info.prev_hash, 0, SHA256_DIGEST_LENGTH);

	memcpy(genesis->data.buffer, GENESIS_DATA, GENESIS_DATA_LEN);
	genesis->data.len = GENESIS_DATA_LEN;

	memcpy(genesis->hash, GENESIS_HASH, SHA256_DIGEST_LENGTH);

	return (genesis);
}

/**
 * blockchain_create - Creates a new Blockchain structure and initializes it
 *                     with the Genesis block
 *
 * Return: Pointer to the created blockchain_t structure, or NULL on failure
 */
blockchain_t *blockchain_create(void)
{
	blockchain_t *blockchain = NULL;
	block_t *genesis = NULL;

	blockchain = malloc(sizeof(blockchain_t));
	if (!blockchain)
		return (NULL);

	blockchain->chain = llist_create();
	if (!blockchain->chain)
	{
		free(blockchain);
		return (NULL);
	}

	genesis = create_genesis_block();
	if (!genesis)
	{
		llist_destroy(blockchain->chain, 1, NULL);
		free(blockchain);
		return (NULL);
	}

	if (llist_add_node(blockchain->chain, genesis, ADD_NODE_FRONT) != 0)
	{
		free(genesis);
		llist_destroy(blockchain->chain, 1, NULL);
		free(blockchain);
		return (NULL);
	}

	return (blockchain);
}
