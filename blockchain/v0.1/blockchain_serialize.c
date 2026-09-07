#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "blockchain.h"

/**
 * blockchain_serialize - Serialize a Blockchain into a file
 * @blockchain: Pointer to the Blockchain to serialize
 * @path: Path to the file to serialize into
 *
 * Return: 0 on success, -1 on failure
 */
int blockchain_serialize(blockchain_t const *blockchain, char const *path)
{
	FILE *file;
	block_t *block;
	llist_node_t *node;
	uint32_t block_count;
	uint8_t endianness = 1; /* Little endian */
	char version[] = "0.1";

	if (blockchain == NULL || path == NULL)
		return (-1);

	file = fopen(path, "wb");
	if (file == NULL)
		return (-1);

	/* Write magic number */
	if (fwrite("HBLK", 1, 4, file) != 4)
	{
		fclose(file);
		return (-1);
	}

	/* Write version */
	if (fwrite(version, 1, 3, file) != 3)
	{
		fclose(file);
		return (-1);
	}

	/* Write endianness */
	if (fwrite(&endianness, 1, 1, file) != 1)
	{
		fclose(file);
		return (-1);
	}

	/* Count blocks */
	block_count = blockchain->chain->size;

	/* Write block count */
	if (fwrite(&block_count, sizeof(uint32_t), 1, file) != 1)
	{
		fclose(file);
		return (-1);
	}

	/* Write each block */
	node = blockchain->chain->head;
	while (node != NULL)
	{
		block = (block_t *)node->elem;

		/* Write block info */
		if (fwrite(&block->info.index, sizeof(uint32_t), 1, file) != 1)
		{
			fclose(file);
			return (-1);
		}

		if (fwrite(&block->info.difficulty, sizeof(uint32_t), 1, file) != 1)
		{
			fclose(file);
			return (-1);
		}

		if (fwrite(&block->info.timestamp, sizeof(uint64_t), 1, file) != 1)
		{
			fclose(file);
			return (-1);
		}

		if (fwrite(&block->info.nonce, sizeof(uint64_t), 1, file) != 1)
		{
			fclose(file);
			return (-1);
		}

		if (fwrite(block->info.prev_hash, 1, SHA256_DIGEST_LENGTH, file)
			!= SHA256_DIGEST_LENGTH)
		{
			fclose(file);
			return (-1);
		}

		/* Write data length and data */
		if (fwrite(&block->data.len, sizeof(uint32_t), 1, file) != 1)
		{
			fclose(file);
			return (-1);
		}

		if (block->data.len > 0)
		{
			if (fwrite(block->data.buffer, 1, block->data.len, file)
				!= block->data.len)
			{
				fclose(file);
				return (-1);
			}
		}

		/* Write hash */
		if (fwrite(block->hash, 1, SHA256_DIGEST_LENGTH, file)
			!= SHA256_DIGEST_LENGTH)
		{
			fclose(file);
			return (-1);
		}

		node = node->next;
	}

	fclose(file);
	return (0);
}
