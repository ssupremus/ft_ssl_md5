#include "../includes/ft_ssl.h"

#if defined(_MSC_VER) || defined(__WATCOMC__)
#define UL64(x) x##ui64
#else
#define UL64(x) x##ULL
#endif

#define  SHR(x,n) (x >> n)
#define ROTR(x,n) (SHR(x,n) | (x << (64 - n)))

#define S0(x) (ROTR(x, 1) ^ ROTR(x, 8) ^  SHR(x, 7))
#define S1(x) (ROTR(x,19) ^ ROTR(x,61) ^  SHR(x, 6))

#define S2(x) (ROTR(x,28) ^ ROTR(x,34) ^ ROTR(x,39))
#define S3(x) (ROTR(x,14) ^ ROTR(x,18) ^ ROTR(x,41))

#define F0(x,y,z) ((x & y) | (z & (x | y)))
#define F1(x,y,z) (z ^ (x & (y ^ z)))

#define GET_UINT64_BE(n,b,i)                            \
{                                                       \
    (n) = ( (uint64_t) (b)[(i)    ] << 56 )       \
        | ( (uint64_t) (b)[(i) + 1] << 48 )       \
        | ( (uint64_t) (b)[(i) + 2] << 40 )       \
        | ( (uint64_t) (b)[(i) + 3] << 32 )       \
        | ( (uint64_t) (b)[(i) + 4] << 24 )       \
        | ( (uint64_t) (b)[(i) + 5] << 16 )       \
        | ( (uint64_t) (b)[(i) + 6] <<  8 )       \
        | ( (uint64_t) (b)[(i) + 7]       );      \
}

#define PUT_UINT64_BE(n, b, i)                 \
  {                                            \
    (b)[(i)] = (unsigned char)((n) >> 56);     \
    (b)[(i) + 1] = (unsigned char)((n) >> 48); \
    (b)[(i) + 2] = (unsigned char)((n) >> 40); \
    (b)[(i) + 3] = (unsigned char)((n) >> 32); \
    (b)[(i) + 4] = (unsigned char)((n) >> 24); \
    (b)[(i) + 5] = (unsigned char)((n) >> 16); \
    (b)[(i) + 6] = (unsigned char)((n) >> 8);  \
    (b)[(i) + 7] = (unsigned char)((n));       \
  }

static uint64_t        g_k[] =
{
    UL64(0x428A2F98D728AE22), UL64(0x7137449123EF65CD),
    UL64(0xB5C0FBCFEC4D3B2F), UL64(0xE9B5DBA58189DBBC),
    UL64(0x3956C25BF348B538), UL64(0x59F111F1B605D019),
    UL64(0x923F82A4AF194F9B), UL64(0xAB1C5ED5DA6D8118),
    UL64(0xD807AA98A3030242), UL64(0x12835B0145706FBE),
    UL64(0x243185BE4EE4B28C), UL64(0x550C7DC3D5FFB4E2),
    UL64(0x72BE5D74F27B896F), UL64(0x80DEB1FE3B1696B1),
    UL64(0x9BDC06A725C71235), UL64(0xC19BF174CF692694),
    UL64(0xE49B69C19EF14AD2), UL64(0xEFBE4786384F25E3),
    UL64(0x0FC19DC68B8CD5B5), UL64(0x240CA1CC77AC9C65),
    UL64(0x2DE92C6F592B0275), UL64(0x4A7484AA6EA6E483),
    UL64(0x5CB0A9DCBD41FBD4), UL64(0x76F988DA831153B5),
    UL64(0x983E5152EE66DFAB), UL64(0xA831C66D2DB43210),
    UL64(0xB00327C898FB213F), UL64(0xBF597FC7BEEF0EE4),
    UL64(0xC6E00BF33DA88FC2), UL64(0xD5A79147930AA725),
    UL64(0x06CA6351E003826F), UL64(0x142929670A0E6E70),
    UL64(0x27B70A8546D22FFC), UL64(0x2E1B21385C26C926),
    UL64(0x4D2C6DFC5AC42AED), UL64(0x53380D139D95B3DF),
    UL64(0x650A73548BAF63DE), UL64(0x766A0ABB3C77B2A8),
    UL64(0x81C2C92E47EDAEE6), UL64(0x92722C851482353B),
    UL64(0xA2BFE8A14CF10364), UL64(0xA81A664BBC423001),
    UL64(0xC24B8B70D0F89791), UL64(0xC76C51A30654BE30),
    UL64(0xD192E819D6EF5218), UL64(0xD69906245565A910),
    UL64(0xF40E35855771202A), UL64(0x106AA07032BBD1B8),
    UL64(0x19A4C116B8D2D0C8), UL64(0x1E376C085141AB53),
    UL64(0x2748774CDF8EEB99), UL64(0x34B0BCB5E19B48A8),
    UL64(0x391C0CB3C5C95A63), UL64(0x4ED8AA4AE3418ACB),
    UL64(0x5B9CCA4F7763E373), UL64(0x682E6FF3D6B2B8A3),
    UL64(0x748F82EE5DEFB2FC), UL64(0x78A5636F43172F60),
    UL64(0x84C87814A1F0AB72), UL64(0x8CC702081A6439EC),
    UL64(0x90BEFFFA23631E28), UL64(0xA4506CEBDE82BDE9),
    UL64(0xBEF9A3F7B2C67915), UL64(0xC67178F2E372532B),
    UL64(0xCA273ECEEA26619C), UL64(0xD186B8C721C0C207),
    UL64(0xEADA7DD6CDE0EB1E), UL64(0xF57D4F7FEE6ED178),
    UL64(0x06F067AA72176FBA), UL64(0x0A637DC5A2C898A6),
    UL64(0x113F9804BEF90DAE), UL64(0x1B710B35131C471B),
    UL64(0x28DB77F523047D84), UL64(0x32CAAB7B40C72493),
    UL64(0x3C9EBE0A15C9BEBC), UL64(0x431D67C49C100D4C),
    UL64(0x4CC5D4BECB3E42B6), UL64(0x597F299CFC657E2A),
    UL64(0x5FCB6FAB3AD6FAEC), UL64(0x6C44198C4A475817)
};

#define P(a, b, c, d, e, f, g, h, x, K)      \
  {                                          \
    temp1 = h + S3(e) + F1(e, f, g) + K + x; \
    temp2 = S2(a) + F0(a, b, c);             \
    d += temp1;                              \
    h = temp1 + temp2;                       \
  }


static void mbedtls_sha512_process(t_ssl *ssl, const unsigned char data[128])
{
  int i;
  uint64_t temp1, temp2, W[80];
  uint64_t A, B, C, D, E, F, G, H;

  for (i = 0; i < 16; i++) {
    GET_UINT64_BE(W[i], data, i << 3);
  }

  for (; i < 80; i++) {
    W[i] = S1(W[i - 2]) + W[i - 7] + S0(W[i - 15]) + W[i - 16];
  }

  A = ssl->state[0];
  B = ssl->state[1];
  C = ssl->state[2];
  D = ssl->state[3];
  E = ssl->state[4];
  F = ssl->state[5];
  G = ssl->state[6];
  H = ssl->state[7];
  i = 0;

  do {
    P(A, B, C, D, E, F, G, H, W[i], g_k[i]);
    i++;
    P(H, A, B, C, D, E, F, G, W[i], g_k[i]);
    i++;
    P(G, H, A, B, C, D, E, F, W[i], g_k[i]);
    i++;
    P(F, G, H, A, B, C, D, E, W[i], g_k[i]);
    i++;
    P(E, F, G, H, A, B, C, D, W[i], g_k[i]);
    i++;
    P(D, E, F, G, H, A, B, C, W[i], g_k[i]);
    i++;
    P(C, D, E, F, G, H, A, B, W[i], g_k[i]);
    i++;
    P(B, C, D, E, F, G, H, A, W[i], g_k[i]);
    i++;
  } while (i < 80);

  ssl->state[0] += A;
  ssl->state[1] += B;
  ssl->state[2] += C;
  ssl->state[3] += D;
  ssl->state[4] += E;
  ssl->state[5] += F;
  ssl->state[6] += G;
  ssl->state[7] += H;
}

static void mbedtls_sha512_update(t_ssl *ssl, const unsigned char *input, size_t ilen)
{
  size_t fill;
  unsigned int left;

  if (ilen == 0) return;

  left = (unsigned int)(ssl->total[0] & 0x7F);
  fill = 128 - left;

  ssl->total[0] += (uint64_t)ilen;

  if (ssl->total[0] < (uint64_t)ilen) ssl->total[1]++;

  if (left && ilen >= fill) {
    ft_memcpy((void *)(ssl->buffer + left), input, fill);
    mbedtls_sha512_process(ssl, ssl->buffer);
    input += fill;
    ilen -= fill;
    left = 0;
  }

  while (ilen >= 128) {
    mbedtls_sha512_process(ssl, input);
    input += 128;
    ilen -= 128;
  }

  if (ilen > 0)
    ft_memcpy((void *)(ssl->buffer + left), input, ilen);
}

static void mbedtls_sha512_starts(t_ssl *ssl) {
  ssl->total[0] = 0;
  ssl->total[1] = 0;

  ssl->state[0] = UL64(0x6A09E667F3BCC908);
  ssl->state[1] = UL64(0xBB67AE8584CAA73B);
  ssl->state[2] = UL64(0x3C6EF372FE94F82B);
  ssl->state[3] = UL64(0xA54FF53A5F1D36F1);
  ssl->state[4] = UL64(0x510E527FADE682D1);
  ssl->state[5] = UL64(0x9B05688C2B3E6C1F);
  ssl->state[6] = UL64(0x1F83D9ABFB41BD6B);
  ssl->state[7] = UL64(0x5BE0CD19137E2179);
}

static const unsigned char sha512_padding[128] = {
    0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

static void mbedtls_sha512_finish(t_ssl *ssl, unsigned char output[64]) {
  size_t last, padn;
  uint64_t high, low;
  unsigned char msglen[16];

  high = (ssl->total[0] >> 61) | (ssl->total[1] << 3);
  low = (ssl->total[0] << 3);

  PUT_UINT64_BE(high, msglen, 0);
  PUT_UINT64_BE(low, msglen, 8);

  last = (size_t)(ssl->total[0] & 0x7F);
  padn = (last < 112) ? (112 - last) : (240 - last);

  mbedtls_sha512_update(ssl, sha512_padding, padn);
  mbedtls_sha512_update(ssl, msglen, 16);

  PUT_UINT64_BE(ssl->state[0], output, 0);
  PUT_UINT64_BE(ssl->state[1], output, 8);
  PUT_UINT64_BE(ssl->state[2], output, 16);
  PUT_UINT64_BE(ssl->state[3], output, 24);
  PUT_UINT64_BE(ssl->state[4], output, 32);
  PUT_UINT64_BE(ssl->state[5], output, 40);
  PUT_UINT64_BE(ssl->state[6], output, 48);
  PUT_UINT64_BE(ssl->state[7], output, 56);
}

int                 sha512(t_ssl *ssl, size_t length, uint8_t *line)
{
    uint8_t out[64];

    mbedtls_sha512_starts(ssl);
    mbedtls_sha512_update(ssl, line, length);
    mbedtls_sha512_finish(ssl, out);
    print_sha512(ssl);
    return (0);
}