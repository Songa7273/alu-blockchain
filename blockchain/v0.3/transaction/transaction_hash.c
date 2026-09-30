#include "transaction.h"

/**
 * hash_inputs - concatenates the input transaction IDs and output indexes
 *
 * @node: current input node
 * @idx: index of the current input node
 * @data: pointer to the buffer
 */
static void hash_inputs(llist_node_t node, unsigned int idx, void *data)
{
	uint8_t **buf = data;
	tx_in_t *tx_in = node;

	(void)idx;
	memcpy(*buf, tx_in->tx_out_hash, SHA256_DIGEST_LENGTH);
	*buf += SHA256_DIGEST_LENGTH;
	memcpy(*buf, &tx_in->tx_out_index, sizeof(tx_in->tx_out_index));
	*buf += sizeof(tx_in->tx_out_index);
}

/**
 * hash_outputs - concatenates the output public key hashes and amounts
 *
 * @node: current output node
 * @idx: index of the current output node
 * @data: pointer to the buffer
 */
static void hash_outputs(llist_node_t node, unsigned int idx, void *data)
{
	uint8_t **buf = data;
	tx_out_t *tx_out = node;

	(void)idx;
	memcpy(*buf, &tx_out->amount, sizeof(tx_out->amount));
	*buf += sizeof(tx_out->amount);
	memcpy(*buf, tx_out->pub, EC_PUB_LEN);
	*buf += EC_PUB_LEN;
}

/**
 * transaction_hash - computes the hash of a transaction
 *
 * @transaction: transaction to hash
 * @hash_buf: buffer to store the hash
 *
 * Return: pointer to hash buffer, or NULL on failure
 */
uint8_t *transaction_hash(transaction_t const *transaction,
			   uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	ssize_t len;
	uint8_t *_buf, *buf;

	if (!transaction)
		return (NULL);

	len = SHA256_DIGEST_LENGTH * 3 * llist_size(transaction->inputs) +
	      SHA256_DIGEST_LENGTH * llist_size(transaction->outputs);
	_buf = buf = calloc(1, len);
	if (!_buf)
		return (NULL);
	llist_for_each(transaction->inputs, hash_inputs, &buf);
	llist_for_each(transaction->outputs, hash_outputs, &buf);
	if (!sha256((const int8_t *)_buf, len, hash_buf))
	{
		free(_buf);
		return (NULL);
	}
	free(_buf);

	return (hash_buf);
}
