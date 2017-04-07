#include "Hash.h"

uint32_t hash_str(char *str, uint32_t hval)
{
	/* unsigned string */
	unsigned char *s = (unsigned char *)str;
	//hash each octet
	while (*s)
	{
		/* xor the bottom with the current octet */
		hval ^= (uint32_t)*s++;

		/* multiply by the 32 bit FNV magic prime mod 2^32 */
#if defined(NO_FNV_GCC_OPTIMIZATION)
		hval *= FNV_32_PRIME;
#else
		hval += (hval << 1) + (hval << 4) + (hval << 7) + (hval << 8) + (hval << 24);
#endif
	}
	return hval;
}
