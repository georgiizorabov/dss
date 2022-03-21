#pragma once
#define MH_UINT32 unsigned int
void XXHash_test(const void *key, int len, MH_UINT32 seed, void *out);
void memCpy1(const void *key, int len, MH_UINT32 seed, void *out);
