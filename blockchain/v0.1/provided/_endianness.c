#include <stdint.h>
#include <unistd.h>

/**
 * get_endianness - Get system endianness
 *
 * Return: 1 for little endian, 2 for big endian
 */
uint8_t get_endianness(void)
{
	uint32_t num = 0x01020304;
	uint8_t *byte = (uint8_t *)&num;

	if (*byte == 0x04)
		return (1); /* Little endian */
	else
		return (2); /* Big endian */
}
