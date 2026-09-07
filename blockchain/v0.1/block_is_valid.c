#include <string.h>
#include <stdint.h>

#include "blockchain.h"
#include "../crypto/hblk_crypto.h"

/**
 * block_is_valid - Verify that a Block is valid
 * @block: Pointer to the Block to check
 * @prev_block: Pointer to the previous Block in the Blockchain
 *
 * Return: 0 if valid, 1 if invalid
 */
int block_is_valid(block_t const *block, block_t const *prev_block)
{
	uint8_t computed_hash[SHA256_DIGEST_LENGTH];
	uint8_t computed_prev_hash[SHA256_DIGEST_LENGTH];
	uint8_t zero_hash[SHA256_DIGEST_LENGTH];

	/* Block should not be NULL */
	if (block == NULL)
		return (1);

	/* Check data length */
	if (block->data.len > BLOCKCHAIN_DATA_MAX)
		return (1);

	memset(zero_hash, 0, SHA256_DIGEST_LENGTH);

	/* Check index and prev_block relationship */
	if (block->info.index == 0)
	{
		/* First block (Genesis) - prev_block should be NULL */
		if (prev_block != NULL)
			return (1);

		/* Check if it matches Genesis block */
		if (block->info.difficulty != 0 || block->info.nonce != 0 ||
			block->info.timestamp != 1537578000 ||
			block->data.len != 16 ||
			strncmp((char *)block->data.buffer, "Holberton School", 16) != 0)
		{
			return (1);
		}

		/* Check if prev_hash is all zeros */
		if (memcmp(block->info.prev_hash, zero_hash, SHA256_DIGEST_LENGTH) != 0)
			return (1);
	}
	else
	{
		/* Not the first block - prev_block should not be NULL */
		if (prev_block == NULL)
			return (1);

		/* Check index */
		if (block->info.index != prev_block->info.index + 1)
			return (1);

		/* Compute hash of previous block */
		block_hash(prev_block, computed_prev_hash);

		/* Check if computed hash matches stored hash */
		if (memcmp(computed_prev_hash, prev_block->hash, SHA256_DIGEST_LENGTH) != 0)
			return (1);

		/* Check if prev_hash in block matches computed hash */
		if (memcmp(block->info.prev_hash, computed_prev_hash, SHA256_DIGEST_LENGTH) != 0)
			return (1);
	}

	/* Compute hash of current block */
	block_hash(block, computed_hash);

	/* Check if computed hash matches stored hash */
	if (memcmp(computed_hash, block->hash, SHA256_DIGEST_LENGTH) != 0)
		return (1);

	return (0);
}
