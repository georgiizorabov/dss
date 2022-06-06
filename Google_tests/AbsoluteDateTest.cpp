#include "gtest/gtest.h"
#include "kvs.h"
//#include "KeyOffset.h"
#include <cassert>
#include <fstream>

void SetUpTest() {
    std::ofstream ofs1("outputData.json");
    std::ofstream ofs2("outputSStable.json");
    ofs1 << "";
    ofs2 << "";
}

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

TEST(AbsoluteDateTestSuite, testLog) { // 12/2/2020 -> 737761
    KeyValueStore kvs;
    SetUpTest();
    auto key1 = Key("k1", 1);
    auto value1 = Value("v1", 1);
    auto kv1 = KeyValue(key1, value1);
    auto key2 = Key("k2", 1);
    auto value2 = Value("v2", 1);
    auto kv2 = KeyValue(key2, value2);

    kvs.add(kv1);
    kvs.add(kv2);

    auto key3 = Key("k3", 1);
    auto value3 = Value("v3", 1);
    auto kv3 = KeyValue(key3, value3);

    EXPECT_STREQ(value1.getValue().c_str(), kvs.get(key1).value().getValue().getValue().c_str());
    EXPECT_STREQ(value2.getValue().c_str(), kvs.get(key2).value().getValue().getValue().c_str());
    EXPECT_EQ(std::nullopt, kvs.get(key3));

    kvs.add(kv3);
    EXPECT_STREQ(value3.getValue().c_str(), kvs.get(key3).value().getValue().getValue().c_str());

}

TEST(AbsoluteDateTestSuite, testSSTable) { // 12/2/2020 -> 737761
    KeyValueStore kvs;
    SetUpTest();
    for (int i = 0; i < 20; i++) {
        auto key = Key("k" + std::to_string(i), 1);
        auto value = Value("v" + std::to_string(i), 1);
        auto kv = KeyValue(key, value);
        kvs.add(kv);
    }
    auto key3 = Key("k3", 1);
    auto value3 = Value("v3", 1);
    auto kv3 = KeyValue(key3, value3);

    for (int i = 10; i < 20; i++) {
        std::string value = "v" + std::to_string(i);
        EXPECT_STREQ(value.c_str(),
                     kvs.get(Key("k" + std::to_string(i), 1)).value().getValue().getValue().c_str());
    }
}







