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
 * _blockchain_print - Print blockchain content
 * @blockchain: Pointer to the blockchain to print
 */
void _blockchain_print(blockchain_t const *blockchain)
{
	llist_node_t *node;
	block_t *block;
	size_t i = 0;

	printf("Blockchain: {\n");
	printf("    chain [%lu]: [\n", blockchain->chain->size);

	node = blockchain->chain->head;
	while (node != NULL)
	{
		block = (block_t *)node->elem;

		printf("        Block: {\n");
		printf("            info: {\n");
		printf("                index: %u,\n", block->info.index);
		printf("                difficulty: %u,\n", block->info.difficulty);
		printf("                timestamp: %lu,\n",
		       (unsigned long)block->info.timestamp);
		printf("                nonce: %lu,\n",
		       (unsigned long)block->info.nonce);
		printf("                prev_hash: ");
		_print_hex_buffer(block->info.prev_hash, SHA256_DIGEST_LENGTH);
		printf("\n");
		printf("            },\n");

		printf("            data: {\n");
		printf("                buffer: \"");
		fwrite(block->data.buffer, 1, block->data.len, stdout);
		printf("\",\n");
		printf("                len: %u\n", block->data.len);
		printf("            },\n");

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
