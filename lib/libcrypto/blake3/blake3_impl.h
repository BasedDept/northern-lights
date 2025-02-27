#ifndef BLAKE3_IMPL_H
#define BLAKE3_IMPL_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "blake3.h"

// internal flags
enum blake3_flags {
    CHUNK_START = 1 << 0,
    CHUNK_END = 1 << 1,
    PARENT = 1 << 2,
    ROOT = 1 << 3,
    KEYED_HASH = 1 << 4,
    DERIVE_KEY_CONTEXT = 1 << 5,
    DERIVE_KEY_MATERIAL = 1 << 6,
};

#define MAX_SIMD_DEGREE 1

// There are some places where we want a static size that's equal to the
// MAX_SIMD_DEGREE, but also at least 2.
#define MAX_SIMD_DEGREE_OR_2 (MAX_SIMD_DEGREE > 2 ? MAX_SIMD_DEGREE : 2)

static const uint32_t IV[8] =
{
    0x6A09E667UL,
    0xBB67AE85UL,
    0x3C6EF372UL,
    0xA54FF53AUL,
    0x510E527FUL,
    0x9B05688CUL,
    0x1F83D9ABUL,
    0x5BE0CD19UL
};

static const uint8_t MSG_SCHEDULE[7][16] = {
    {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15},
    {  2,  6,  3, 10,  7,  0,  4, 13,  1, 11, 12,  5,  9, 14, 15,  8},
    {  3,  4, 10, 12, 13,  2,  7, 14,  6,  5,  9,  0, 11, 15,  8,  1},
    { 10,  7, 12,  9, 14,  3, 13, 15,  4,  0, 11,  2,  5,  8,  1,  6},
    { 12, 13,  9, 11, 15, 10, 14,  8,  7,  2,  5,  3,  0,  1,  6,  4},
    {  9, 14, 11,  5,  8, 12, 15,  1, 13,  3,  0, 10,  2,  6,  4,  7},
    { 11, 15,  5,  0,  1,  9,  8,  6, 14, 10,  2, 12,  3,  4,  7, 13}
};

/* Find index of the highest set bit */
/* x is assumed to be nonzero.       */
static unsigned int highest_one(uint64_t x)
{

    // return 63 ^ __builtin_clzll(x);
    unsigned int c = 0;
    if (x & 0xffffffff00000000ULL) {
        x >>= 32;
        c += 32;
    }
    if (x & 0x00000000ffff0000ULL) {
        x >>= 16;
        c += 16;
    }
    if (x & 0x000000000000ff00ULL) {
        x >>= 8;
        c += 8;
    }
    if (x & 0x00000000000000f0ULL) {
        x >>= 4;
        c += 4;
    }
    if (x & 0x000000000000000cULL) {
        x >>= 2;
        c += 2;
    }
    if (x & 0x0000000000000002ULL) {
        c += 1;
    }
    return c;
}

// Count the number of 1 bits.
static inline unsigned int popcnt(uint64_t x)
{
    // return __builtin_popcountll(x);
    unsigned int count = 0;
    while (x != 0) {
        count += 1;
        x &= x - 1;
    }
    return count;
#endif
}

// Largest power of two less than or equal to x. As a special case, returns 1
// when x is 0.
static inline uint64_t round_down_to_power_of_2(uint64_t x) { return 1ULL << highest_one(x | 1); }

static inline uint32_t counter_low(uint64_t counter) { return (uint32_t)counter; }

static inline uint32_t counter_high(uint64_t counter) { return (uint32_t)(counter >> 32); }

static inline uint32_t load32(const void* src)
{
    const uint8_t* p = (const uint8_t*)src;
    return ((uint32_t)(p[0]) << 0) | ((uint32_t)(p[1]) << 8) | ((uint32_t)(p[2]) << 16) | ((uint32_t)(p[3]) << 24);
}

static inline void load_key_words(const uint8_t key[BLAKE3_KEY_LEN], uint32_t key_words[8])
{
    key_words[0] = load32(&key[0 * 4]);
    key_words[1] = load32(&key[1 * 4]);
    key_words[2] = load32(&key[2 * 4]);
    key_words[3] = load32(&key[3 * 4]);
    key_words[4] = load32(&key[4 * 4]);
    key_words[5] = load32(&key[5 * 4]);
    key_words[6] = load32(&key[6 * 4]);
    key_words[7] = load32(&key[7 * 4]);
}

void blake3_compress_in_place(
    uint32_t cv[8], const uint8_t block[BLAKE3_BLOCK_LEN], uint8_t block_len, uint64_t counter, uint8_t flags);

void blake3_compress_xof(const uint32_t cv[8], const uint8_t block[BLAKE3_BLOCK_LEN], uint8_t block_len, uint64_t counter,
    uint8_t flags, uint8_t out[64]);

void blake3_hash_many(const uint8_t* const* inputs, size_t num_inputs, size_t blocks, const uint32_t key[8], uint64_t counter,
    bool increment_counter, uint8_t flags, uint8_t flags_start, uint8_t flags_end, uint8_t* out);

size_t blake3_simd_degree();

#endif /* BLAKE3_IMPL_H */

