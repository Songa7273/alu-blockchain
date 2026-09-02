#include "hblk_crypto.h"

#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>
#include <openssl/pem.h>

/**
 * ec_save - Saves an EC key pair to disk
 * @key: EC key pair to save
 * @folder: Folder where the keys are saved
 *
 * Return: 1 upon success, 0 upon failure
 */
int ec_save(EC_KEY *key, char const *folder)
{
	FILE *file;
	char path[4096];

	if (key == NULL || folder == NULL)
		return (0);

	if (mkdir(folder, 0700) == -1)
	{
		if (errno != EEXIST)
			return (0);
	}

	snprintf(path, sizeof(path), "%s/%s", folder, PRI_FILENAME);
	file = fopen(path, "w");
	if (file == NULL)
		return (0);

	if (PEM_write_ECPrivateKey(file, key, NULL, NULL, 0, NULL, NULL) != 1)
	{
		fclose(file);
		return (0);
	}

	fclose(file);

	snprintf(path, sizeof(path), "%s/%s", folder, PUB_FILENAME);
	file = fopen(path, "w");
	if (file == NULL)
		return (0);

	if (PEM_write_EC_PUBKEY(file, key) != 1)
	{
		fclose(file);
		return (0);
	}

	fclose(file);

	return (1);
}
