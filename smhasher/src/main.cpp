#include "Platform.h"
#include "Hashes.h"
#include "KeysetTest.h"
#include "SpeedTest.h"
#include "AvalancheTest.h"
#include "DifferentialTest.h"
#include "PMurHash.h"

#include <stdio.h>
#include <time.h>

//-----------------------------------------------------------------------------
// Configuration. TODO - move these to command-line flags

bool g_testAll = false;

bool g_testSanity      = false;
bool g_testSpeed       = false;
bool g_testDiff        = false;
bool g_testDiffDist    = false;
bool g_testAvalanche   = false;
bool g_testBIC         = false;
bool g_testCyclic      = false;
bool g_testTwoBytes    = false;
bool g_testSparse      = false;
bool g_testPermutation = false;
bool g_testWindow      = false;
bool g_testText        = false;
bool g_testZeroes      = false;
bool g_testSeed        = false;

//-----------------------------------------------------------------------------
// This is the list of all hashes that SMHasher can test.

struct HashInfo
{
  pfHash hash;
  int hashbits;
  uint32_t verification;
  const char * name;
  const char * desc;
};

HashInfo g_hashes[] =
{
  { DoNothingHash,        32, 0x00000000, "donothing32", "Do-Nothing function (only valid for measuring call overhead)" },
  { DoNothingHash,        64, 0x00000000, "donothing64", "Do-Nothing function (only valid for measuring call overhead)" },
  { DoNothingHash,       128, 0x00000000, "donothing128", "Do-Nothing function (only valid for measuring call overhead)" },

  { crc32,                32, 0x3719DB20, "crc32",       "CRC-32" },

  { md5_32,               32, 0xC10C356B, "md5_32a",     "MD5, first 32 bits of result" },
  { sha1_32a,             32, 0xF9376EA7, "sha1_32a",    "SHA1, first 32 bits of result" },

  { FNV,                  32, 0xE3CBBE91, "FNV",         "Fowler-Noll-Vo hash, 32-bit" },
  { Bernstein,            32, 0xBDB4B640, "bernstein",   "Bernstein, 32-bit" },
  { lookup3_test,         32, 0x3D83917A, "lookup3",     "Bob Jenkins' lookup3" },
  { SuperFastHash,        32, 0x980ACD1D, "superfast",   "Paul Hsieh's SuperFastHash" },
  { MurmurOAAT_test,      32, 0x5363BD98, "MurmurOAAT",  "Murmur one-at-a-time" },
  { Crap8_test,           32, 0x743E97A1, "Crap8",       "Crap8" },

  { CityHash64_test,      64, 0x25A20825, "City64",      "Google CityHash64WithSeed" },
  { CityHash128_test,    128, 0x6531F54E, "City128",     "Google CityHash128WithSeed" },

  { SpookyHash32_test,    32, 0x3F798BBB, "Spooky32",    "Bob Jenkins' SpookyHash, 32-bit result" },
  { SpookyHash64_test,    64, 0xA7F955F1, "Spooky64",    "Bob Jenkins' SpookyHash, 64-bit result" },
  { SpookyHash128_test,  128, 0x8D263080, "Spooky128",   "Bob Jenkins' SpookyHash, 128-bit result" },

  // MurmurHash2

  { MurmurHash2_test,     32, 0x27864C1E, "Murmur2",     "MurmurHash2 for x86, 32-bit" },
  { MurmurHash2A_test,    32, 0x7FBD4396, "Murmur2A",    "MurmurHash2A for x86, 32-bit" },
  { MurmurHash64A_test,   64, 0x1F0D3804, "Murmur2B",    "MurmurHash2 for x64, 64-bit" },
  { MurmurHash64B_test,   64, 0xDD537C05, "Murmur2C",    "MurmurHash2 for x86, 64-bit" },

  // MurmurHash3

  { MurmurHash3_x86_32,   32, 0xB0F57EE3, "Murmur3A",    "MurmurHash3 for x86, 32-bit" },
  { MurmurHash3_x86_128, 128, 0xB3ECE62A, "Murmur3C",    "MurmurHash3 for x86, 128-bit" },
  { MurmurHash3_x64_128, 128, 0x6384BA69, "Murmur3F",    "MurmurHash3 for x64, 128-bit" },

  { PMurHash32_test,      32, 0xB0F57EE3, "PMurHash32",  "Shane Day's portable-ized MurmurHash3 for x86, 32-bit." },
  { XXH64_test,           64, 0x024B7CF4, "XXHash64",    "Cool Hash"  },
};

HashInfo * findHash ( const char * name )
{
  for(size_t i = 0; i < sizeof(g_hashes) / sizeof(HashInfo); i++)
  {
    if(_stricmp(name,g_hashes[i].name) == 0) return &g_hashes[i];
  }

  return NULL;
}

//-----------------------------------------------------------------------------
// Self-test on startup - verify that all installed hashes work correctly.

void SelfTest ( void )
{
  bool pass = true;

  for(size_t i = 0; i < sizeof(g_hashes) / sizeof(HashInfo); i++)
  {
    HashInfo * info = & g_hashes[i];

    pass &= VerificationTest(info->hash,info->hashbits,info->verification,false);
  }

  if(!pass)
  {
    printf("Self-test FAILED!\n");

    for(size_t i = 0; i < sizeof(g_hashes) / sizeof(HashInfo); i++)
    {
      HashInfo * info = & g_hashes[i];

      printf("%16s - ",info->name);
      pass &= VerificationTest(info->hash,info->hashbits,info->verification,true);
    }

    exit(1);
  }
}

//----------------------------------------------------------------------------

template < typename hashtype >
void test ( hashfunc<hashtype> hash, HashInfo * info )
{
  const int hashbits = sizeof(hashtype) * 8;

  printf("-------------------------------------------------------------------------------\n");
  printf("--- Testing %s (%s)\n\n",info->name,info->desc);

  //-----------------------------------------------------------------------------
  // Speed tests
  printf("[[[ tiny speed test from 1 to 99 with step 2 ]]]\n\n");
  {

    for(int i = 1; i < 100; i+= 2)
    {
      double cycles;

      TinySpeedTest(hashfunc<hashtype>(info->hash),sizeof(hashtype),i,info->verification,true,cycles);
    }

    printf("\n");
  }

  printf("[[[ tiny speed test from 100 to 1000 with step 50 ]]]\n\n");
  {

    for(int i = 100; i <= 1000; i+= 50)
    {
      double cycles;

      TinySpeedTest(hashfunc<hashtype>(info->hash),sizeof(hashtype),i,info->verification,true,cycles);
    }

    printf("\n");
  }

}

void test_memcpy ()
{

  printf("-------------------------------------------------------------------------------\n");
  printf("--- Testing memcpy \n\n");

  //-----------------------------------------------------------------------------
  // Speed tests
  printf("[[[ tiny speed test from 1 to 99 with step 2 ]]]\n\n");
  {

    for(int i = 1; i < 100; i+= 2)
    {
        
      TinySpeedTest_memcpy(i, 0x00000000);
    }

    printf("\n");
  }

  printf("[[[ tiny speed test from 100 to 1000 with step 50 ]]]\n\n");
  {

    for(int i = 100; i <= 1000; i+= 50)
    {
        
      TinySpeedTest_memcpy(i, 0x00000000);
    
    }
    printf("\n");
  }

}

//-----------------------------------------------------------------------------

uint32_t g_inputVCode = 1;
uint32_t g_outputVCode = 1;
uint32_t g_resultVCode = 1;

HashInfo * g_hashUnderTest = NULL;

void VerifyHash ( const void * key, int len, uint32_t seed, void * out )
{
  g_inputVCode = MurmurOAAT(key,len,g_inputVCode);
  g_inputVCode = MurmurOAAT(&seed,sizeof(uint32_t),g_inputVCode);

  g_hashUnderTest->hash(key,len,seed,out);

  g_outputVCode = MurmurOAAT(out,g_hashUnderTest->hashbits/8,g_outputVCode);
}

//-----------------------------------------------------------------------------

void testHash ( const char * name )
{
  HashInfo * pInfo = findHash(name);

  if(pInfo == NULL)
  {
    printf("Invalid hash '%s' specified\n",name);
    return;
  }
  else
  {
    g_hashUnderTest = pInfo;

    if(pInfo->hashbits == 32)
    {
      test<uint32_t>( VerifyHash, pInfo );
    }
    else if(pInfo->hashbits == 64)
    {
      test<uint64_t>( pInfo->hash, pInfo );
    }
    else if(pInfo->hashbits == 128)
    {
      test<uint128_t>( pInfo->hash, pInfo );
    }
    else if(pInfo->hashbits == 256)
    {
      test<uint256_t>( pInfo->hash, pInfo );
    }
    else
    {
      printf("Invalid hash bit width %d for hash '%s'",pInfo->hashbits,pInfo->name);
    }
  }
}
//-----------------------------------------------------------------------------

int main ( int argc, char ** argv )
{

  // Code runs on the 3rd CPU by default

  SetAffinity((1 << 2));

  SelfTest();

  int timeBegin = clock();

  g_testAll = true;

  testHash("xxhash64");

  testHash("murmur3a");

  test_memcpy();
  //----------

  int timeEnd = clock();

  printf("\n");
  printf("Input vcode 0x%08x, Output vcode 0x%08x, Result vcode 0x%08x\n",g_inputVCode,g_outputVCode,g_resultVCode);
  printf("Verification value is 0x%08x - Testing took %f seconds\n",g_verify,double(timeEnd-timeBegin)/double(CLOCKS_PER_SEC));
  printf("-------------------------------------------------------------------------------\n");
  return 0;
}
