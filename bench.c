/*
Copyright (C) 2014 insane coder (http://insanecoding.blogspot.com/, http://chacha20.insanecoding.org/)

Permission to use, copy, modify, and distribute this software for any
purpose with or without fee is hereby granted, provided that the above
copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#define __USE_MINGW_ANSI_STDIO 1
#include <sys/time.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#ifdef __WIN32__
#include <malloc.h>
#elif defined(__linux__) || defined(__sun__)
#include <alloca.h>
#endif

#include <chacha20_simple.h> //Replace with header to another library if you want to test something else

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

void hex2byte(const char *hex, uint8_t *byte)
{
  while (*hex) { sscanf(hex, "%2hhx", byte++); hex += 2; }
}

uint8_t key[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8 };

double now() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec + tv.tv_usec / 1000000.0;
}

#define BUF_SIZE (1024*1024)

int main()
{
	srand(0);
	chacha20_ctx ctx;
	chacha20_setup(&ctx, key, sizeof(key), key);

	uint8_t buf[BUF_SIZE];

	double t1 = now();
	for (unsigned i = 0; i < 1024; i++)
		chacha20_encrypt(&ctx, buf, buf, BUF_SIZE);

	double t = now() - t1;

	printf("1G encrypt time: %0.1f, %0.1f MiB/s\n", t, 1024 / t);
}
