#include "blockchain.h"

/**
 * hash_matches_difficulty - Checks if a hash matches a given difficulty
 *
 * @hash: Hash to check
 * @difficulty: Minimum difficulty the hash should match
 *
 * Return: 1 if the hash matches the difficulty, 0 otherwise
 */
int hash_matches_difficulty(uint8_t const hash[SHA256_DIGEST_LENGTH],
			    uint32_t difficulty)
{
	uint32_t i;
	uint32_t bits;

	if (difficulty > SHA256_DIGEST_LENGTH * 8)
		return (0);

	bits = 0;

	for (i = 0; i < SHA256_DIGEST_LENGTH; i++)
	{
		if (hash[i] == 0)
			bits += 8;
		else
		{
			while ((hash[i] & (1 << (7 - (bits % 8)))) == 0)
				bits++;

			break;
		}

		if (bits >= difficulty)
			return (1);
	}

	return (bits >= difficulty);
}
