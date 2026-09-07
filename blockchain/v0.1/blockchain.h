#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <stdint.h>
#include <stddef.h>
#include <llist.h>

#define SHA256_DIGEST_LENGTH 32
#define BLOCKCHAIN_DATA_MAX 1024

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
block_t *block_create(block_t const *prev, int8_t const *data,
	uint32_t data_len);
void block_destroy(block_t *block);
void blockchain_destroy(blockchain_t *blockchain);
uint8_t *block_hash(block_t const *block, uint8_t hash_buf[SHA256_DIGEST_LENGTH]);
int blockchain_serialize(blockchain_t const *blockchain, char const *path);
blockchain_t *blockchain_deserialize(char const *path);
int block_is_valid(block_t const *block, block_t const *prev_block);

#endif /* BLOCKCHAIN_H */
