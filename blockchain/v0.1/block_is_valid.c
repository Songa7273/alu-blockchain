#include <string.h>
#include "blockchain.h"

/**
 * check_genesis - Validates if a block matches the Genesis block specification
 * @block: Pointer to the block to check
 *
 * Return: 0 if valid genesis block, 1 otherwise
 */
static int check_genesis(block_t const *block)
{
	block_t const genesis = {
		{GENESIS_INDEX, GENESIS_DIFFICULTY, GENESIS_TIMESTAMP,
		 GENESIS_NONCE, GENESIS_PREV_HASH},
		{GENESIS_DATA, GENESIS_DATA_LEN},
		GENESIS_HASH
	};

	if (block->info.index != 0)
		return (1);

	return (memcmp(block, &genesis, sizeof(genesis)) != 0);
}

/**
 * block_is_valid - Verifies that a Block is valid
 * @block: Pointer to the Block to check
 * @prev_block: Pointer to the previous Block in the Blockchain
 *
 * Return: 0 if valid, 1 otherwise
 */
int block_is_valid(block_t const *block, block_t const *prev_block)
{
	uint8_t hash[SHA256_DIGEST_LENGTH];

	if (!block || block->data.len > BLOCKCHAIN_DATA_MAX_LEN)
		return (1);

	if (!prev_block)
		return (check_genesis(block));

	if (block->info.index != prev_block->info.index + 1)
		return (1);

	if (!block_hash(prev_block, hash) ||
	    memcmp(prev_block->hash, hash, SHA256_DIGEST_LENGTH) != 0)
		return (1);

	if (memcmp(block->info.prev_hash, prev_block->hash,
		   SHA256_DIGEST_LENGTH) != 0)
		return (1);

	if (!block_hash(block, hash) ||
	    memcmp(block->hash, hash, SHA256_DIGEST_LENGTH) != 0)
		return (1);

	return (0);
}
