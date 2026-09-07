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

	if (blockchain == NULL || blockchain->chain == NULL)
		return;

	printf("Blockchain: {\n");
	printf("\tchain [%zu]: [\n", blockchain->chain->size);

	node = blockchain->chain->head;
	while (node != NULL)
	{
		block = (block_t *)node->elem;

		printf("\t\tBlock: {\n");
		printf("\t\t\tinfo: {\n");
		printf("\t\t\t\tindex: %u,\n", block->info.index);
		printf("\t\t\t\tdifficulty: %u,\n", block->info.difficulty);
		printf("\t\t\t\ttimestamp: %lu,\n",
		       (unsigned long)block->info.timestamp);
		printf("\t\t\t\tnonce: %lu,\n",
		       (unsigned long)block->info.nonce);
		printf("\t\t\t\tprev_hash: ");
		_print_hex_buffer(block->info.prev_hash, SHA256_DIGEST_LENGTH);
		printf("\n");
		printf("\t\t\t},\n");

		printf("\t\t\tdata: {\n");
		printf("\t\t\t\tbuffer: \"");
		if (block->data.buffer != NULL && block->data.len > 0)
			fwrite(block->data.buffer, 1, block->data.len, stdout);
		printf("\",\n");
		printf("\t\t\t\tlen: %u\n", block->data.len);
		printf("\t\t\t},\n");

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

