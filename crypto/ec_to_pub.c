#include "hblk_crypto.h"

/**
 * ec_to_pub - Extracts the public key from an EC_KEY
 * @key: EC_KEY containing the public key
 * @pub: Buffer where the public key is stored
 *
 * Return: Pointer to pub, or NULL upon failure
 */
uint8_t *ec_to_pub(EC_KEY const *key, uint8_t pub[EC_PUB_LEN])
{
EC_GROUP const *group;
EC_POINT const *point;
size_t len;

if (key == NULL || pub == NULL)
return (NULL);

group = EC_KEY_get0_group(key);
point = EC_KEY_get0_public_key(key);

if (group == NULL || point == NULL)
return (NULL);

len = EC_POINT_point2oct(group, point,
 POINT_CONVERSION_UNCOMPRESSED,
 pub, EC_PUB_LEN, NULL);

if (len != EC_PUB_LEN)
return (NULL);

return (pub);
}
