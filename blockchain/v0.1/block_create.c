#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "blockchain.h"

/**
 * block_create - Create a new Block
 * @prev: Pointer to the previous Block
 * @data: Pointer to data to duplicate in the Block
 * @data_len: Number of bytes to duplicate
 *
 * Return: Pointer to the allocated Block, or NULL on failure
 */
block_t *block_create(block_t const *prev, int8_t const *data,
	uint32_t data_len)
{
	block_t *block;
	uint32_t copy_len;

	block = malloc(sizeof(*block));
	if (block == NULL)
		return (NULL);

	/* Set index */
	block->info.index = prev->info.index + 1;

	/* Set difficulty and nonce */
	block->info.difficulty = 0;
	block->info.nonce = 0;

	/* Set timestamp */
	block->info.timestamp = time(NULL);

	/* Set previous hash */
	memcpy(block->info.prev_hash, prev->hash, SHA256_DIGEST_LENGTH);

	/* Set data */
	copy_len = data_len > BLOCKCHAIN_DATA_MAX ? BLOCKCHAIN_DATA_MAX : data_len;
	block->data.buffer = malloc(copy_len);
	if (block->data.buffer == NULL)
	{
		free(block);
		return (NULL);
	}
	memcpy(block->data.buffer, data, copy_len);
	block->data.len = copy_len;

	/* Zero out hash */
	memset(block->hash, 0, SHA256_DIGEST_LENGTH);

	return (block);
}
