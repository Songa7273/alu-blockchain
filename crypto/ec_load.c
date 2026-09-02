#include "hblk_crypto.h"

#include <openssl/pem.h>
#include <stdio.h>

/**
 * ec_load_pub - Loads the public key from disk
 * @path: Path to the public key file
 *
 * Return: Pointer to EC_KEY, or NULL upon failure
 */
static EC_KEY *ec_load_pub(char const *path)
{
	FILE *file;
	EC_KEY *key;

	file = fopen(path, "r");
	if (file == NULL)
		return (NULL);

	key = PEM_read_EC_PUBKEY(file, NULL, NULL, NULL);
	fclose(file);

	return (key);
}

/**
 * ec_load - Loads an EC key pair from disk
 * @folder: Folder containing the key files
 *
 * Return: Pointer to EC_KEY, or NULL upon failure
 */
EC_KEY *ec_load(char const *folder)
{
	FILE *file;
	char path[4096];
	EC_KEY *key;
	EC_KEY *pubkey;

	if (folder == NULL)
		return (NULL);

	snprintf(path, sizeof(path), "%s/%s", folder, PRI_FILENAME);
	file = fopen(path, "r");
	if (file == NULL)
		return (NULL);

	key = PEM_read_ECPrivateKey(file, NULL, NULL, NULL);
	fclose(file);
	if (key == NULL)
		return (NULL);

	snprintf(path, sizeof(path), "%s/%s", folder, PUB_FILENAME);
	pubkey = ec_load_pub(path);
	if (pubkey == NULL)
	{
		EC_KEY_free(key);
		return (NULL);
	}

	if (EC_KEY_set_public_key(key, EC_KEY_get0_public_key(pubkey)) != 1)
	{
		EC_KEY_free(pubkey);
		EC_KEY_free(key);
		return (NULL);
	}

	EC_KEY_free(pubkey);
	return (key);
}
