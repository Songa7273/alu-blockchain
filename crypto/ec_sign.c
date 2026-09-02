#include "hblk_crypto.h"

#include <openssl/ecdsa.h>
#include <openssl/sha.h>
#include <stdlib.h>

/**
 * ec_sign - Signs a message using an EC private key
 * @key: EC_KEY containing the private key
 * @msg: Message to sign
 * @msglen: Length of the message
 * @sig: Structure where the signature is stored
 *
 * Return: Pointer to the signature buffer, or NULL upon failure
 */
uint8_t *ec_sign(EC_KEY const *key, uint8_t const *msg,
		size_t msglen, sig_t *sig)
{
	uint8_t digest[SHA256_DIGEST_LENGTH];
	unsigned int siglen;

	if (key == NULL || msg == NULL || sig == NULL)
		return (NULL);

	if (SHA256(msg, msglen, digest) == NULL)
		return (NULL);

	sig->sig = malloc(ECDSA_size(key));
	if (sig->sig == NULL)
		return (NULL);

	if (ECDSA_sign(0, digest, SHA256_DIGEST_LENGTH,
		       sig->sig, &siglen, (EC_KEY *)key) != 1)
	{
		free(sig->sig);
		sig->sig = NULL;
		return (NULL);
	}

	sig->len = siglen;
	return (sig->sig);
}
