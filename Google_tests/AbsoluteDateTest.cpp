#include "gtest/gtest.h"
#include "kvs.h"
//#include "KeyOffset.h"

TEST(AbsoluteDateTestSuite, ExampleDate) { // 12/2/2020 -> 737761
    KeyValueStore kvs;
    auto ko1 = KeyValue("k1", 1, "v1", 1);
    auto ko2 = KeyValue("k1", 1, "v1", 1);
    auto ko3 = KeyValue("k1", 1, "v1", 1);
    auto ko4 = KeyValue("k1", 1, "v1", 1);

    kvs.add(ko1);
    kvs.add(ko2);
    kvs.add(ko3);
    kvs.add(ko4);

//    EXPECT_EQ(1, 1);
}

TEST(AbsoluteDateTestSuite, simple_test) { // 12/2/2020 -> 737761
    KeyValueStore kvs;
    auto key1 = Key("k1", 1);
    auto value1 = Value("v1", 1);
    auto ko1 = KeyValue(key1, value1);
    auto key2 = Key("k2", 1);
    auto value2 = Value("v2", 1);
    auto ko2 = KeyValue(key2, value1);

    kvs.add(ko1);
    kvs.add(ko2);

    EXPECT_EQ(kvs.get(key1).value().getValue().getValue(), value1.getValue());
}







