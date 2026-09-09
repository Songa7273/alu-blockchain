#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <stddef.h>
#include <stdint.h>
#include <llist.h>

#define SHA256_DIGEST_LENGTH 32
#define BLOCKCHAIN_DATA_MAX_LEN 1024

#define GENESIS_INDEX 0
#define GENESIS_DIFFICULTY 0
#define GENESIS_TIMESTAMP 1537578000
#define GENESIS_NONCE 0
#define GENESIS_PREV_HASH "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
#define GENESIS_DATA "Holberton School"
#define GENESIS_DATA_LEN 16
#define GENESIS_HASH "\xc5\x2c\x26\xc8\xb5\x46\x16\x39\x63\x5d\x8e\xdf\x2a\x97\xd4\x8d\x0c\x8e\x00\x09\xc8\x17\xf2\xb1\xd3\xd7\xff\x2f\x04\x51\x58\x03"

/**
 * struct block_info_s - Block info structure
 *
 * @index:      Index of the Block in the Blockchain
 * @difficulty: Difficulty of the Proof-of-Work
 * @timestamp:  Time at which the Block was created
 * @nonce:      Salt used to alter the hash
 * @prev_hash:  Hash the previous Block in the Blockchain
 */
typedef struct block_info_s
{
	uint32_t index;
	uint32_t difficulty;
	uint64_t timestamp;
	uint64_t nonce;
	uint8_t prev_hash[SHA256_DIGEST_LENGTH];
} block_info_t;

/**
 * struct block_data_s - Block data structure
 *
 * @buffer: Data buffer
 * @len:    Data length
 */
typedef struct block_data_s
{
	int8_t buffer[BLOCKCHAIN_DATA_MAX_LEN];
	uint32_t len;
} block_data_t;

/**
 * struct block_s - Block structure
 *
 * @info: Block information
 * @data: Block data
 * @hash: Block hash
 */
typedef struct block_s
{
	block_info_t info;
	block_data_t data;
	uint8_t hash[SHA256_DIGEST_LENGTH];
} block_t;

/**
 * struct blockchain_s - Blockchain structure
 *
 * @chain: Pointer to the head of the linked list containing blocks
 */
typedef struct blockchain_s
{
	llist_t *chain;
} blockchain_t;

/* Function prototypes */
blockchain_t *blockchain_create(void);

#endif /* BLOCKCHAIN_H */
