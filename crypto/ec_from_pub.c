#include "hblk_crypto.h"

/**
 * ec_from_pub - Creates an EC_KEY from a public key
 * @pub: Public key to load
 *
 * Return: Pointer to EC_KEY, or NULL upon failure
 */
EC_KEY *ec_from_pub(uint8_t const pub[EC_PUB_LEN])
{
	EC_KEY *key;
	EC_GROUP const *group;
	EC_POINT *point;

	if (pub == NULL)
		return (NULL);

	key = EC_KEY_new_by_curve_name(EC_CURVE);
	if (key == NULL)
		return (NULL);

	group = EC_KEY_get0_group(key);
	point = EC_POINT_new(group);
	if (group == NULL || point == NULL)
	{
		if (point != NULL)
			EC_POINT_free(point);
		EC_KEY_free(key);
		return (NULL);
	}

	if (EC_POINT_oct2point(group, point, pub, EC_PUB_LEN, NULL) != 1 ||
	    EC_KEY_set_public_key(key, point) != 1)
	{
		EC_POINT_free(point);
		EC_KEY_free(key);
		return (NULL);
	}

	EC_POINT_free(point);
	return (key);
}
