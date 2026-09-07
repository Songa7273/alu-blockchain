#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "blockchain.h"

/**
 * blockchain_deserialize - Deserialize a Blockchain from a file
 * @path: Path to the file to load the Blockchain from
 *
 * Return: Pointer to the deserialized Blockchain, or NULL on failure
 */
blockchain_t *blockchain_deserialize(char const *path)
{
	FILE *file;
	blockchain_t *blockchain;
	block_t *block;
	char magic[4];
	char version[3];
	uint8_t endianness;
	uint32_t block_count;
	uint32_t i;
	int8_t *data_buffer;
	uint32_t data_len;

	if (path == NULL)
		return (NULL);

	file = fopen(path, "rb");
	if (file == NULL)
		return (NULL);

	/* Read and validate magic number */
	if (fread(magic, 1, 4, file) != 4)
	{
		fclose(file);
		return (NULL);
	}

	if (strncmp(magic, "HBLK", 4) != 0)
	{
		fclose(file);
		return (NULL);
	}

	/* Read and validate version */
	if (fread(version, 1, 3, file) != 3)
	{
		fclose(file);
		return (NULL);
	}

	if (strncmp(version, "0.1", 3) != 0)
	{
		fclose(file);
		return (NULL);
	}

	/* Read endianness */
	if (fread(&endianness, 1, 1, file) != 1)
	{
		fclose(file);
		return (NULL);
	}

	if (endianness != 1 && endianness != 2)
	{
		fclose(file);
		return (NULL);
	}

	/* Read block count */
	if (fread(&block_count, sizeof(uint32_t), 1, file) != 1)
	{
		fclose(file);
		return (NULL);
	}

	/* Create blockchain */
	blockchain = malloc(sizeof(*blockchain));
	if (blockchain == NULL)
	{
		fclose(file);
		return (NULL);
	}

	blockchain->chain = llist_create();
	if (blockchain->chain == NULL)
	{
		free(blockchain);
		fclose(file);
		return (NULL);
	}

	/* Read blocks */
	for (i = 0; i < block_count; i++)
	{
		block = malloc(sizeof(*block));
		if (block == NULL)
		{
			blockchain_destroy(blockchain);
			fclose(file);
			return (NULL);
		}

		/* Read block info */
		if (fread(&block->info.index, sizeof(uint32_t), 1, file) != 1)
		{
			free(block);
			blockchain_destroy(blockchain);
			fclose(file);
			return (NULL);
		}

		if (fread(&block->info.difficulty, sizeof(uint32_t), 1, file) != 1)
		{
			free(block);
			blockchain_destroy(blockchain);
			fclose(file);
			return (NULL);
		}

		if (fread(&block->info.timestamp, sizeof(uint64_t), 1, file) != 1)
		{
			free(block);
			blockchain_destroy(blockchain);
			fclose(file);
			return (NULL);
		}

		if (fread(&block->info.nonce, sizeof(uint64_t), 1, file) != 1)
		{
			free(block);
			blockchain_destroy(blockchain);
			fclose(file);
			return (NULL);
		}

		if (fread(block->info.prev_hash, 1, SHA256_DIGEST_LENGTH, file)
			!= SHA256_DIGEST_LENGTH)
		{
			free(block);
			blockchain_destroy(blockchain);
			fclose(file);
			return (NULL);
		}

		/* Read data length */
		if (fread(&data_len, sizeof(uint32_t), 1, file) != 1)
		{
			free(block);
			blockchain_destroy(blockchain);
			fclose(file);
			return (NULL);
		}

		block->data.len = data_len;

		/* Read data */
		if (data_len > 0)
		{
			data_buffer = malloc(data_len);
			if (data_buffer == NULL)
			{
				free(block);
				blockchain_destroy(blockchain);
				fclose(file);
				return (NULL);
			}

			if (fread(data_buffer, 1, data_len, file) != data_len)
			{
				free(data_buffer);
				free(block);
				blockchain_destroy(blockchain);
				fclose(file);
				return (NULL);
			}

			block->data.buffer = data_buffer;
		}
		else
		{
			block->data.buffer = NULL;
		}

		/* Read hash */
		if (fread(block->hash, 1, SHA256_DIGEST_LENGTH, file)
			!= SHA256_DIGEST_LENGTH)
		{
			block_destroy(block);
			blockchain_destroy(blockchain);
			fclose(file);
			return (NULL);
		}

		/* Add block to blockchain */
		if (llist_add_node(blockchain->chain, block, ADD_NODE_BACK) != 0)
		{
			block_destroy(block);
			blockchain_destroy(blockchain);
			fclose(file);
			return (NULL);
		}
	}

	fclose(file);
	return (blockchain);
}
