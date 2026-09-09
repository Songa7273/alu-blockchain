#include <string.h>
#include "blockchain.h"

/**
 * check_genesis - Checks if a given block matches the static Genesis block
 * @block: Pointer to the block to check
 *
 * Return: 0 if block is valid Genesis block, 1 otherwise
 */
static int check_genesis(block_t const *block)
{
	block_t genesis;

	if (!block || block->info.index != 0)
		return (1);

	memset(&genesis, 0, sizeof(genesis));
	genesis.info.index = 0;
	genesis.info.difficulty = 0;
	genesis.info.timestamp = 1537578000;
	genesis.info.nonce = 0;
	memset(genesis.info.prev_hash, 0, SHA256_DIGEST_LENGTH);

	memcpy(genesis.data.buffer, "Holberton School", 16);
	genesis.data.len = 16;

	memcpy(genesis.hash,
	       "\xc5\x2c\x26\xc8\xb5\x46\x16\x39\x63\x5d\x8e\xdf\x2a\x97\xd4\x8d"
	       "\x0c\x8e\x00\x09\xc8\x17\xf2\xb1\xd3\xd7\xff\x2f\x04\x51\x58\x03",
	       SHA256_DIGEST_LENGTH);

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
