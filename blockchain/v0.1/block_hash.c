#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "blockchain.h"
#include "../crypto/hblk_crypto.h"

/**
 * block_hash - Compute the hash of a Block
 * @block: Pointer to the Block to be hashed
 * @hash_buf: Buffer to store the hash result
 *
 * Return: Pointer to hash_buf
 */
uint8_t *block_hash(block_t const *block, uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	int8_t *buffer;
	uint32_t len;
	uint32_t offset;

	if (block == NULL || hash_buf == NULL)
		return (NULL);

	/* Calculate total buffer size */
	len = 4 + 4 + 8 + 8 + SHA256_DIGEST_LENGTH + 4 + block->data.len;

	buffer = malloc(len);
	if (buffer == NULL)
		return (NULL);

	offset = 0;

	/* Copy index */
	memcpy(buffer + offset, &block->info.index, 4);
	offset += 4;

	/* Copy difficulty */
	memcpy(buffer + offset, &block->info.difficulty, 4);
	offset += 4;

	/* Copy timestamp */
	memcpy(buffer + offset, &block->info.timestamp, 8);
	offset += 8;

	/* Copy nonce */
	memcpy(buffer + offset, &block->info.nonce, 8);
	offset += 8;

	/* Copy prev_hash */
	memcpy(buffer + offset, block->info.prev_hash, SHA256_DIGEST_LENGTH);
	offset += SHA256_DIGEST_LENGTH;

	/* Copy data length */
	memcpy(buffer + offset, &block->data.len, 4);
	offset += 4;

	/* Copy data */
	if (block->data.len > 0)
	{
		memcpy(buffer + offset, block->data.buffer, block->data.len);
	}

	/* Compute SHA256 hash */
	sha256(buffer, len, hash_buf);

	free(buffer);

	return (hash_buf);
}
