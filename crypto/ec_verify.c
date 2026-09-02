#include "hblk_crypto.h"

#include <openssl/ecdsa.h>

/**
 * ec_verify - Verifies a signature using an EC public key
 * @key: EC_KEY containing the public key
 * @msg: Message to verify
 * @msglen: Length of the message
 * @sig: Signature to verify
 *
 * Return: 1 if valid, 0 otherwise
 */
int ec_verify(EC_KEY const *key, uint8_t const *msg,
		size_t msglen, sig_t const *sig)
{
	if (key == NULL || msg == NULL || sig == NULL)
		return (0);

	return (ECDSA_verify(0, msg, msglen, sig->sig, sig->len,
			     (EC_KEY *)key) == 1);
}
