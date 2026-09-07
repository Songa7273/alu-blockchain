#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "blockchain.h"

/**
 * genesis_init - Initialize the Genesis block
 * @genesis: Genesis block to initialize
 */
static void genesis_init(block_t *genesis)
{
	genesis->info.index = 0;
	genesis->info.difficulty = 0;
	genesis->info.timestamp = 1537578000;
	genesis->info.nonce = 0;

	memset(genesis->info.prev_hash, 0, SHA256_DIGEST_LENGTH);

	genesis->data.buffer = (int8_t *)"Holberton School";
	genesis->data.len = 16;

	memcpy(genesis->hash,
	       "\xc5\x2c\x26\xc8\xb5\x46\x16\x39"
	       "\x63\x5d\x8e\xdf\x2a\x97\xd4\x8d"
	       "\x0c\x8e\x00\x09\xc8\x17\xf2\xb1"
	       "\xd3\xd7\xff\x2f\x04\x51\x58\x03",
	       SHA256_DIGEST_LENGTH);
}

/**
 * blockchain_create - Create and initialize a blockchain
 *
 * Return: Pointer to the new blockchain, or NULL on failure
 */
blockchain_t *blockchain_create(void)
{
	blockchain_t *blockchain;
	block_t *genesis;

	blockchain = malloc(sizeof(*blockchain));
	if (blockchain == NULL)
		return (NULL);

	blockchain->chain = llist_create();
	if (blockchain->chain == NULL)
	{
		free(blockchain);
		return (NULL);
	}

	genesis = malloc(sizeof(*genesis));
	if (genesis == NULL)
	{
		llist_destroy(blockchain->chain, 0, NULL);
		free(blockchain);
		return (NULL);
	}

	genesis_init(genesis);

	if (llist_add_node(blockchain->chain, genesis, ADD_NODE_BACK) != 0)
	{
		free(genesis);
		llist_destroy(blockchain->chain, 0, NULL);
		free(blockchain);
		return (NULL);
	}

	return (blockchain);
}

