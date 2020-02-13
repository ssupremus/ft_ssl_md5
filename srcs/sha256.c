#include "../includes/ft_ssl.h"

static uint32_t k[] = {
 0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
 0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
 0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
 0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

static uint32_t rotate(uint32_t x, uint32_t n)
{
	return ((((unsigned int)x >> n)) | (x << (32 - n)));
}

static void	    sha256_loop(t_ssl *ssl, int i)
{
  uint32_t s1;
  uint32_t s0;
  uint32_t ch;
  uint32_t maj;

	s1 = rotate(ssl->e, 6) ^ rotate(ssl->e, 11) ^ rotate(ssl->e, 25);
	ch = (ssl->e & ssl->f) ^ ((~ssl->e) & ssl->g);
	ssl->tmp = ssl->h + s1 + ch + k[i] + ssl->w[i];
	s0 = rotate(ssl->a, 2) ^ rotate(ssl->a, 13) ^ rotate(ssl->a, 22);
	maj = (ssl->a & ssl->b) ^ (ssl->a & ssl->c) ^ (ssl->b & ssl->c);
	ssl->tmp2 = s0 + maj;
	ssl->h = ssl->g;
	ssl->g = ssl->f;
	ssl->f = ssl->e;
	ssl->e = ssl->d + ssl->tmp;
	ssl->d = ssl->c;
	ssl->c = ssl->b;
	ssl->b = ssl->a;
	ssl->a = ssl->tmp + ssl->tmp2;
}

static void    schedule(t_ssl *ssl, int i)
{
  int j;

	ssl->w = malloc(512);
	ft_bzero(ssl->w, 512);
	ft_memcpy(ssl->w, &ssl->msg_32[i * 16], 16 * 32);
	j = 16;
	while (j < 64)
	{
		ssl->tmp2 = rotate(ssl->w[j - 15], 7) ^
		rotate(ssl->w[j - 15], 18) ^ (ssl->w[j - 15] >> 3);
		ssl->tmp = rotate(ssl->w[j - 2], 17) ^
		rotate(ssl->w[j - 2], 19) ^ (ssl->w[j - 2] >> 10);
		ssl->w[j] = ssl->w[j - 16] + ssl->tmp2 + ssl->w[j - 7] + ssl->tmp;
		j++;
	}
	ssl->a = ssl->a0;
	ssl->b = ssl->b0;
	ssl->c = ssl->c0;
	ssl->d = ssl->d0;
	ssl->e = ssl->e0;
	ssl->f = ssl->f0;
	ssl->g = ssl->g0;
	ssl->h = ssl->h0;
}

static int	 set_variables(unsigned char *line, size_t length, t_ssl *ssl)
{
  int i;

  ssl->a0 = 0x6a09e667;
  ssl->b0 = 0xbb67ae85;
  ssl->c0 = 0x3c6ef372;
  ssl->d0 = 0xa54ff53a;
  ssl->e0 = 0x510e527f;
  ssl->f0 = 0x9b05688c;
  ssl->g0 = 0x1f83d9ab;
  ssl->h0 = 0x5be0cd19;
  ssl->len = length * 8;
  ssl->chunk = 1 + ((ssl->len + 16 + 64) / 512);
  if (!(ssl->msg_32 = malloc(16 * ssl->chunk * 4)))
		return (-1);
	ft_bzero(ssl->msg_32, 16 * ssl->chunk * 4);
	ft_memcpy((char *)ssl->msg_32, line, length);
  ((char*)ssl->msg_32)[length] = 0x80;
	i = -1;
	while (++i < (ssl->chunk * 16) - 1)
		ssl->msg_32[i] = reverse_number(ssl->msg_32[i]);
	ssl->msg_32[((ssl->chunk * 512 - 64) / 32) + 1] = ssl->len;
	return (0);
}

int		      sha256(t_ssl *ssl, size_t length, uint8_t *line)
{
  int i;
  int j;

  i = 0;
  set_variables(line, length, ssl);
  while (i < ssl->chunk)
  {
    schedule(ssl, i);
    j = 0;
    while (j < 64)
      sha256_loop(ssl, j++);
    ssl->a0 += ssl->a;
    ssl->b0 += ssl->b;
    ssl->c0 += ssl->c;
    ssl->d0 += ssl->d;
    ssl->e0 += ssl->e;
    ssl->f0 += ssl->f;
    ssl->g0 += ssl->g;
    ssl->h0 += ssl->h;
    free(ssl->w);
    i++;
  }
  print_sha256(ssl);
  free(ssl->msg_32);
  return (0);
}
