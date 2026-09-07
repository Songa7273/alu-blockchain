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

	if (blockchain == NULL || blockchain->chain == NULL)
		return;

	printf("Blockchain: {\n");
	printf("\tchain [%zu]: [\n", blockchain->chain->size);

	node = blockchain->chain->head;
	while (node != NULL)
	{
		block = (block_t *)node->elem;

		printf("\t\tBlock: {\n");
		printf("\t\t\tinfo: { %u, %u, %lu, %lu, ",
		       block->info.index,
		       block->info.difficulty,
		       (unsigned long)block->info.timestamp,
		       (unsigned long)block->info.nonce);
		_print_hex_buffer(block->info.prev_hash, SHA256_DIGEST_LENGTH);
		printf(" },\n");

		printf("\t\t\tdata: { \"");
		if (block->data.buffer != NULL && block->data.len > 0)
			fwrite(block->data.buffer, 1, block->data.len, stdout);
		printf("\", %u },\n", block->data.len);

		printf("\t\t\thash: ");
		_print_hex_buffer(block->hash, SHA256_DIGEST_LENGTH);
		printf("\n");

		printf("\t\t}");
		if (node->next != NULL)
			printf("\n");
		else
			printf("\n\t]\n}\n");

		node = node->next;
	}
}

