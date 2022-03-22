#define XXH_INLINE_ALL

#include "xxhash.h"
#include "XXhashTest.h"
#include <stdio.h>
void XXHash_test(const void *key, int len, uint32_t seed, [[maybe_unused]] void *out) {
    out = (void *) XXH64(key, len, seed);
}

void memCpy1(const void *key, int len, MH_UINT32 seed, void *out) {
    memcpy(dst, src, len);
}
