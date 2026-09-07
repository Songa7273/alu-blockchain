#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "blockchain.h"

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
	blockchain_t *blockchain;
	block_t *genesis;
	uint8_t expected_hash[SHA256_DIGEST_LENGTH] = {
		0xc5, 0x2c, 0x26, 0xc8, 0xb5, 0x46, 0x16, 0x39,
		0x63, 0x5d, 0x8e, 0xdf, 0x2a, 0x97, 0xd4, 0x8d,
		0x0c, 0x8e, 0x00, 0x09, 0xc8, 0x17, 0xf2, 0xb1,
		0xd3, 0xd7, 0xff, 0x2f, 0x04, 0x51, 0x58, 0x03
	};
	uint8_t zero_hash[SHA256_DIGEST_LENGTH];

	memset(zero_hash, 0, SHA256_DIGEST_LENGTH);

	blockchain = blockchain_create();
	if (blockchain == NULL)
	{
		printf("blockchain_create() failed\n");
		return (EXIT_FAILURE);
	}

	genesis = (block_t *)llist_get_head(blockchain->chain);
	if (genesis == NULL)
	{
		printf("Genesis block is missing\n");
		return (EXIT_FAILURE);
	}

	printf("index: %u\n", genesis->info.index);
	printf("difficulty: %u\n", genesis->info.difficulty);
	printf("timestamp: %lu\n",
	       (unsigned long)genesis->info.timestamp);
	printf("nonce: %lu\n",
	       (unsigned long)genesis->info.nonce);
	printf("data: %s\n", genesis->data.buffer);
	printf("data length: %u\n", genesis->data.len);

	if (memcmp(genesis->info.prev_hash,
		   zero_hash,
		   SHA256_DIGEST_LENGTH) != 0)
	{
		printf("prev_hash: FAILED\n");
		return (EXIT_FAILURE);
	}

	if (memcmp(genesis->hash, expected_hash,
		   SHA256_DIGEST_LENGTH) != 0)
	{
		printf("hash: FAILED\n");
		return (EXIT_FAILURE);
	}

	printf("Genesis block: OK\n");

	llist_destroy(blockchain->chain, free);
	free(blockchain);

	return (EXIT_SUCCESS);
}


