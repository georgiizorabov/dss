#include "Platform.h"
#include "Hashes.h"
#include "KeysetTest.h"
#include "SpeedTest.h"
#include "AvalancheTest.h"
#include "DifferentialTest.h"
#include "PMurHash.h"
#include "XXhashTest.h"
#include <stdio.h>
#include <time.h>

//-----------------------------------------------------------------------------
// Configuration. TODO - move these to command-line flags

bool g_testAll = false;

bool g_testSanity = false;
bool g_testSpeed = false;
bool g_testDiff = false;
bool g_testDiffDist = false;
bool g_testAvalanche = false;
bool g_testBIC = false;
bool g_testCyclic = false;
bool g_testTwoBytes = false;
bool g_testSparse = false;
bool g_testPermutation = false;
bool g_testWindow = false;
bool g_testText = false;
bool g_testZeroes = false;
bool g_testSeed = false;

//-----------------------------------------------------------------------------
// This is the list of all hashes that SMHasher can test.

struct HashInfo {
    pfHash hash;
    int hashbits;
    uint32_t verification;
    const char *name;
    const char *desc;
};

HashInfo g_hashes[] =
        {
                {MurmurHash3_x86_32, 32, 0xB0F57EE3, "Murmur3A", "MurmurHash3 for x86, 32-bit"},
                {XXHash_test,        64, 0x00000000, "XXHash",   "XXHash"},
                {memCpy1,        32, 0x00000000, "MemCpy",   "MemCpy"},

        };

HashInfo *findHash(const char *name) {
    for (size_t i = 0; i < sizeof(g_hashes) / sizeof(HashInfo); i++) {
        if (_stricmp(name, g_hashes[i].name) == 0) return &g_hashes[i];
    }

    return NULL;
}

//-----------------------------------------------------------------------------
// Self-test on startup - verify that all installed hashes work correctly.

void SelfTest(void) {
    bool pass = true;

    for (size_t i = 0; i < sizeof(g_hashes) / sizeof(HashInfo); i++) {
        HashInfo *info = &g_hashes[i];

        pass &= VerificationTest(info->hash, info->hashbits, info->verification, false);
//        pass = true;
    }

    if (!pass) {
        printf("Self-test FAILED!\n");

        for (size_t i = 0; i < sizeof(g_hashes) / sizeof(HashInfo); i++) {
            HashInfo *info = &g_hashes[i];

            printf("%16s - ", info->name);
            pass &= VerificationTest(info->hash, info->hashbits, info->verification, true);
        }

        exit(1);
    }
}

//----------------------------------------------------------------------------

template<typename hashtype>
void test(hashfunc<hashtype> hash, HashInfo *info) {
    const int hashbits = sizeof(hashtype) * 8;

    printf("-------------------------------------------------------------------------------\n");
    printf("--- Testing %s (%s)\n\n", info->name, info->desc);

    //-----------------------------------------------------------------------------
    // Sanity tests

//    if (g_testSanity || g_testAll) {
//        printf("[[[ Sanity Tests ]]]\n\n");
//
//        VerificationTest(hash, hashbits, info->verification, true);
//        SanityTest(hash, hashbits);
//        AppendedZeroesTest(hash, hashbits);
//        printf("\n");
//    }

    //-----------------------------------------------------------------------------
    // Speed tests

    if (g_testSpeed || g_testAll) {
        printf("[[[ Speed Tests ]]]\n\n");

//        BulkSpeedTest(info->hash, info->verification);
//        printf("\n");

        printf("FIRST:\n");
        for (int i = 1; i <= 100; i += 2) {
            double cycles;
            TinySpeedTest(hashfunc<hashtype>(info->hash), sizeof(hashtype), i, info->verification, true, cycles);
        }
        printf("SECOND:\n");
        for (int i = 100; i <= 1000; i += 50) {
            double cycles;
            TinySpeedTest(hashfunc<hashtype>(info->hash), sizeof(hashtype), i, info->verification, true, cycles);
        }

        printf("\n");
    }

}

//-----------------------------------------------------------------------------

uint32_t g_inputVCode = 1;
uint32_t g_outputVCode = 1;
uint32_t g_resultVCode = 1;

HashInfo *g_hashUnderTest = NULL;

void VerifyHash(const void *key, int len, uint32_t seed, void *out) {
    g_inputVCode = MurmurOAAT(key, len, g_inputVCode);
    g_inputVCode = MurmurOAAT(&seed, sizeof(uint32_t), g_inputVCode);

    g_hashUnderTest->hash(key, len, seed, out);

    g_outputVCode = MurmurOAAT(out, g_hashUnderTest->hashbits / 8, g_outputVCode);
}

//-----------------------------------------------------------------------------

void testHash(const char *name) {
    HashInfo *pInfo = findHash(name);

    if (pInfo == NULL) {
//        printf("Invalid hash '%s' specified\n", name);
        return;
    } else {
        g_hashUnderTest = pInfo;

        if (pInfo->hashbits == 32) {
            test<uint32_t>(VerifyHash, pInfo);
        } else if (pInfo->hashbits == 64) {
            test<uint64_t>(pInfo->hash, pInfo);
        } else if (pInfo->hashbits == 128) {
            test<uint128_t>(pInfo->hash, pInfo);
        } else if (pInfo->hashbits == 256) {
            test<uint256_t>(pInfo->hash, pInfo);
        } else {
//            printf("Invalid hash bit width %d for hash '%s'", pInfo->hashbits, pInfo->name);
        }
    }
}
//-----------------------------------------------------------------------------

int main(int argc, char **argv) {
    const char *hashToTest = "XXHash";

    if (argc < 2) {
        printf("(No test hash given on command line, testing Murmur3_x86_32.)\n");
    } else {
        hashToTest = argv[1];
    }

    // Code runs on the 3rd CPU by default

    SetAffinity((1 << 2));

    SelfTest();

    int timeBegin = clock();

    g_testAll = true;

    //g_testSanity = true;
    //g_testSpeed = true;
    //g_testAvalanche = true;
    //g_testBIC = true;
    //g_testCyclic = true;
    //g_testTwoBytes = true;
    //g_testDiff = true;
    //g_testDiffDist = true;
    //g_testSparse = true;
    //g_testPermutation = true;
    //g_testWindow = true;
    //g_testZeroes = true;

    testHash("XXHash");
    testHash("Murmur3A");
    testHash("MemCpy");

    //----------

    int timeEnd = clock();

    printf("\n");
    printf("Input vcode 0x%08x, Output vcode 0x%08x, Result vcode 0x%08x\n", g_inputVCode, g_outputVCode,
           g_resultVCode);
    printf("Verification value is 0x%08x - Testing took %f seconds\n", g_verify,
           double(timeEnd - timeBegin) / double(CLOCKS_PER_SEC));
    printf("-------------------------------------------------------------------------------\n");
    return 0;
}
