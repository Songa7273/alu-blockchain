#include <stdlib.h>
#include <string.h>

#include "blockchain.h"

/**
 * _genesis - Create a Genesis block
 *
 * Return: Pointer to the Genesis block
 */
block_t *_genesis(void)
{
	block_t *genesis;

	genesis = malloc(sizeof(*genesis));
	if (genesis == NULL)
		return (NULL);

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

	return (genesis);
}
