#include "blockchain.h"

/**
 * _blockchain_destroy - Destroy a blockchain (provided helper)
 * @blockchain: Pointer to the blockchain to destroy
 */
void _blockchain_destroy(blockchain_t *blockchain)
{
	blockchain_destroy(blockchain);
}
