#ifndef SC25519_H
#define SC25519_H

#define sc25519                  CRYPTO_NAMESPACE(sc25519)
#define shortsc25519             CRYPTO_NAMESPACE(shortsc25519)
#define sc25519_from32bytes      CRYPTO_NAMESPACE(sc25519_from32bytes)
#define shortsc25519_from16bytes CRYPTO_NAMESPACE(shortsc25519_from16bytes)
#define sc25519_from64bytes      CRYPTO_NAMESPACE(sc25519_from64bytes)
#define sc25519_from_shortsc     CRYPTO_NAMESPACE(sc25519_from_shortsc)
#define sc25519_to32bytes        CRYPTO_NAMESPACE(sc25519_to32bytes)
#define sc25519_iszero_vartime   CRYPTO_NAMESPACE(sc25519_iszero_vartime)
#define sc25519_isshort_vartime  CRYPTO_NAMESPACE(sc25519_isshort_vartime)
#define sc25519_lt_vartime       CRYPTO_NAMESPACE(sc25519_lt_vartime)
#define sc25519_add              CRYPTO_NAMESPACE(sc25519_add)
#define sc25519_sub_nored        CRYPTO_NAMESPACE(sc25519_sub_nored)
#define sc25519_mul              CRYPTO_NAMESPACE(sc25519_mul)
#define sc25519_mul_shortsc      CRYPTO_NAMESPACE(sc25519_mul_shortsc)
#define sc25519_window3          CRYPTO_NAMESPACE(sc25519_window3)
#define sc25519_window5          CRYPTO_NAMESPACE(sc25519_window5)
#define sc25519_2interleave2     CRYPTO_NAMESPACE(sc25519_2interleave2)

typedef struct 
{
  crypto_uint32 v[32]; 
}
sc25519;

typedef struct 
{
  crypto_uint32 v[16]; 
}
shortsc25519;

void sc25519_from32bytes(sc25519 *r, const unsigned char x[32]);

void shortsc25519_from16bytes(shortsc25519 *r, const unsigned char x[16]);

void sc25519_from64bytes(sc25519 *r, const unsigned char x[64]);

void sc25519_from_shortsc(sc25519 *r, const shortsc25519 *x);

void sc25519_to32bytes(unsigned char r[32], const sc25519 *x);

int sc25519_iszero_vartime(const sc25519 *x);

int sc25519_isshort_vartime(const sc25519 *x);

int sc25519_lt_vartime(const sc25519 *x, const sc25519 *y);

void sc25519_add(sc25519 *r, const sc25519 *x, const sc25519 *y);

void sc25519_sub_nored(sc25519 *r, const sc25519 *x, const sc25519 *y);

void sc25519_mul(sc25519 *r, const sc25519 *x, const sc25519 *y);

void sc25519_mul_shortsc(sc25519 *r, const sc25519 *x, const shortsc25519 *y);

/* Convert s into a representation of the form \sum_{i=0}^{84}r[i]2^3
 * with r[i] in {-4,...,3}
 */
void sc25519_window3(signed char r[85], const sc25519 *s);

/* Convert s into a representation of the form \sum_{i=0}^{50}r[i]2^5
 * with r[i] in {-16,...,15}
 */
void sc25519_window5(signed char r[51], const sc25519 *s);

void sc25519_2interleave2(unsigned char r[127], const sc25519 *s1, const sc25519 *s2);

#endif
