#include "gtest/gtest.h"
#include "KVS.h"
#include <fstream>

class KVS_tester : public ::testing::Test {

protected:
public:
//    KVS_tester() {}

protected:
    virtual void SetUp() {
        std::ofstream ofs1("outputData.json");
        std::ofstream ofs2("outputSStable.json");
        ofs1 << "";
        ofs2 << "";
    }
};


TEST_F(KVS_tester, testLog) { // 12/2/2020 -> 737761
    KeyValueStore kvs;
//    SetUpTest();
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

TEST_F(KVS_tester, testSSTable) { // 12/2/2020 -> 737761
    KeyValueStore kvs;
//    SetUpTest();
    for (int i = 0; i < 20; i++) {
        auto key = Key("k" + std::to_string(i), 1);
        auto value = Value("v" + std::to_string(i), 1);
        auto kv = KeyValue(key, value);
        kvs.add(kv);
    }

    for (int i = 0; i < 20; i++) {
        std::string value = "v" + std::to_string(i);
        EXPECT_STREQ(value.c_str(),
                     kvs.get(Key("k" + std::to_string(i), 1)).value().getValue().getValue().c_str());
    }
}

TEST_F(KVS_tester, testDeleteLog) {
    KeyValueStore kvs;
    for (int i = 0; i < 20; i++) {
        auto key = Key("k" + std::to_string(i), 1);
        auto value = Value("v" + std::to_string(i), 1);
        auto kv = KeyValue(key, value);
        kvs.add(kv);
    }
    auto key = Key("k11", 1);
    auto value = Value("v1", 1);
    auto kv = KeyValue(key, value);

    kvs.del(key);

    EXPECT_EQ(std::nullopt,
                 kvs.get(key));

    kvs.add(kv);
    EXPECT_STREQ(value.getValue().c_str(),
                     kvs.get(key).value().getValue().getValue().c_str());

}

TEST_F(KVS_tester, testDeleteSSTable) {
    KeyValueStore kvs;
    for (int i = 0; i < 20; i++) {
        auto key = Key("k" + std::to_string(i), 1);
        auto value = Value("v" + std::to_string(i), 1);
        auto kv = KeyValue(key, value);
        kvs.add(kv);
    }
    auto key1 = Key("k11", 1);
    auto value1 = Value("v1", 1);
    auto kv1 = KeyValue(key1, value1);

    kvs.del(key1);

    for (int i = 21; i < 40; i++) {
        auto key = Key("k" + std::to_string(i), 1);
        auto value = Value("v" + std::to_string(i), 1);
        auto kv = KeyValue(key, value);
        kvs.add(kv);
    }

    EXPECT_EQ(std::nullopt,
              kvs.get(key1));

    kvs.add(kv1);
    EXPECT_STREQ(value1.getValue().c_str(),
                 kvs.get(key1).value().getValue().getValue().c_str());

}




