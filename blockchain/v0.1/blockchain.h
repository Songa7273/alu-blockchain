#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <stdint.h>
#include <stddef.h>
#include <llist.h>

#define SHA256_DIGEST_LENGTH 32

/**
 * struct block_s - Block structure
 * @info: Block information
 * @data: Block data
 * @hash: Block hash
 */
typedef struct block_s
{
	struct
	{
		uint32_t index;
		uint32_t difficulty;
		uint64_t timestamp;
		uint64_t nonce;
		uint8_t prev_hash[SHA256_DIGEST_LENGTH];
	} info;

	struct
	{
		int8_t *buffer;
		uint32_t len;
	} data;

	uint8_t hash[SHA256_DIGEST_LENGTH];
} block_t;

/**
 * struct blockchain_s - Blockchain structure
 * @chain: Linked list containing the blocks
 */
typedef struct blockchain_s
{
	llist_t *chain;
} blockchain_t;

blockchain_t *blockchain_create(void);

#endif /* BLOCKCHAIN_H */
