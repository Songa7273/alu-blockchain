#include <stdio.h>
#include <string.h>

#include "blockchain.h"

/**
 * _print_hex_buffer - Print a buffer in hex
 * @buf: Buffer to print
 * @len: Length of buffer
 */
static void _print_hex_buffer(uint8_t const *buf, size_t len)
{
	size_t i;

	for (i = 0; i < len; i++)
		printf("%02x", buf[i]);
}

/**
 * _blockchain_print_brief - Print blockchain in brief format
 * @blockchain: Pointer to the blockchain to print
 */
void _blockchain_print_brief(blockchain_t const *blockchain)
{
	llist_node_t *node;
	block_t *block;

	printf("Blockchain: {\n");
	printf("    chain [%lu]: [\n", blockchain->chain->size);

	node = blockchain->chain->head;
	while (node != NULL)
	{
		block = (block_t *)node->elem;

		printf("        Block: {\n");
		printf("            info: { %u, %u, %lu, %lu, ",
		       block->info.index,
		       block->info.difficulty,
		       (unsigned long)block->info.timestamp,
		       (unsigned long)block->info.nonce);
		_print_hex_buffer(block->info.prev_hash, SHA256_DIGEST_LENGTH);
		printf(" },\n");

		printf("            data: { \"");
		fwrite(block->data.buffer, 1, block->data.len, stdout);
		printf("\", %u },\n", block->data.len);

		printf("            hash: ");
		_print_hex_buffer(block->hash, SHA256_DIGEST_LENGTH);
		printf("\n");

		printf("        }");
		if (node->next != NULL)
			printf("\n");
		else
			printf("\n    ]\n}\n");

		node = node->next;
	}
}
