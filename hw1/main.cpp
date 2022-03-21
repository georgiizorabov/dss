#define XXH_INLINE_ALL

#include <iostream>
#include "xxhash.h"

int main() {
    int size = 10;

    int buffer[10] = {1,2,3,4,5};
    int seed = 11;
    XXH64_hash_t hash = XXH64(buffer, size, seed);
    std::cout << hash;
    return 0;
}