#include "hblk_crypto.h"

#include <openssl/pem.h>
#include <stdio.h>

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
	file = fopen(path, "r");
	if (file == NULL)
	{
		EC_KEY_free(key);
		return (NULL);
	}

	if (PEM_read_EC_PUBKEY(file, &key, NULL, NULL) == NULL)
	{
		fclose(file);
		EC_KEY_free(key);
		return (NULL);
	}

	fclose(file);
	return (key);
}
