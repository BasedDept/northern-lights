#include "blake3.h"

int crypto_hash(unsigned char* out, const unsigned char* in, unsigned long long inlen)
{
    blake3_default_hash(in, inlen, out);
    return 0;
}

