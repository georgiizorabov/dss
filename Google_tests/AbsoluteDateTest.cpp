#include "gtest/gtest.h"
#include "kvs.h"


TEST(AbsoluteDateTestSuite, ExampleDate){ // 12/2/2020 -> 737761
    KeyValueStore kvs;
    auto ko1 = KeyValue("k1", 1, "v1", 1);
    auto ko2 = KeyValue("k1", 1, "v1", 1);
    auto ko3 = KeyValue("k1", 1, "v1", 1);
    auto ko4 = KeyValue("k1", 1, "v1", 1);

    kvs.add(ko1);
    kvs.add(ko2);
    kvs.add(ko3);
    kvs.add(ko4);

    EXPECT_EQ(1, 1);
}

