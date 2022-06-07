#include "gtest/gtest.h"
#include "KVS.h"
#include <fstream>

class KVS_tester : public ::testing::Test {

protected:
public:

protected:
    virtual void SetUp() {
        std::ofstream ofs1("outputData.json");
        std::ofstream ofs2("outputSStable.json");
        ofs1 << "";
        ofs2 << "";
    }
};


TEST_F(KVS_tester, testLog) {
    KeyValueStore kvs;
    auto key1 = Key("k1");
    auto value1 = Value("v1");
    auto kv1 = KeyValue(key1, value1);
    auto key2 = Key("k2");
    auto value2 = Value("v2");
    auto kv2 = KeyValue(key2, value2);

    kvs.add(kv1);
    kvs.add(kv2);

    auto key3 = Key("k3");
    auto value3 = Value("v3");
    auto kv3 = KeyValue(key3, value3);

    EXPECT_STREQ(value1.getValue().c_str(), kvs.get(key1).value().getValue().getValue().c_str());
    EXPECT_STREQ(value2.getValue().c_str(), kvs.get(key2).value().getValue().getValue().c_str());
    EXPECT_EQ(std::nullopt, kvs.get(key3));

    kvs.add(kv3);
    EXPECT_STREQ(value3.getValue().c_str(), kvs.get(key3).value().getValue().getValue().c_str());

}

TEST_F(KVS_tester, testSSTable) {
    KeyValueStore kvs;
    for (int i = 0; i < 20; i++) {
        auto key = Key("k" + std::to_string(i));
        auto value = Value("v" + std::to_string(i));
        auto kv = KeyValue(key, value);
        kvs.add(kv);
    }

    for (int i = 0; i < 20; i++) {
        std::string value = "v" + std::to_string(i);
        EXPECT_STREQ(value.c_str(),
                     kvs.get(Key("k" + std::to_string(i))).value().getValue().getValue().c_str());
    }
}

TEST_F(KVS_tester, testDeleteLog) {
    KeyValueStore kvs;
    for (int i = 0; i < 20; i++) {
        auto key = Key("k" + std::to_string(i));
        auto value = Value("v" + std::to_string(i));
        auto kv = KeyValue(key, value);
        kvs.add(kv);
    }

    for (int i = 0; i < 10; i++) {

        auto key = Key("k" + std::to_string(i));
        auto value = Value("v" + std::to_string(i));
        auto kv = KeyValue(key, value);

        kvs.del(key);

        EXPECT_EQ(std::nullopt,
                  kvs.get(key));

        kvs.add(kv);
        EXPECT_STREQ(value.getValue().c_str(),
                     kvs.get(key).value().getValue().getValue().c_str());
    }

}

TEST_F(KVS_tester, testDeleteSSTable) {
    KeyValueStore kvs;
    for (int i = 0; i < 20; i++) {
        auto key = Key("k" + std::to_string(i));
        auto value = Value("v" + std::to_string(i));
        auto kv = KeyValue(key, value);
        kvs.add(kv);
    }
    auto key1 = Key("k11");
    auto value1 = Value("v1");
    auto kv1 = KeyValue(key1, value1);

    kvs.del(key1);

    EXPECT_EQ(std::nullopt,
              kvs.get(key1));

    for (int i = 21; i < 40; i++) {
        auto key = Key("k" + std::to_string(i));
        auto value = Value("v" + std::to_string(i));
        auto kv = KeyValue(key, value);
        kvs.add(kv);
    }

    EXPECT_EQ(std::nullopt,
              kvs.get(key1));

    kvs.add(kv1);
    EXPECT_STREQ(value1.getValue().c_str(),
                 kvs.get(key1).value().getValue().getValue().c_str());

}


TEST_F(KVS_tester, testDeleteNonExisting) {
    KeyValueStore kvs;

    for (int i = 0; i < 20; i++) {
        auto key = Key("k" + std::to_string(i));
        auto value = Value("v" + std::to_string(i));
        auto kv = KeyValue(key, value);
        kvs.add(kv);
    }

    auto key1 = Key("my_key");
    auto value1 = Value("v1");
    auto kv1 = KeyValue(key1, value1);

    kvs.del(key1);

    EXPECT_EQ(std::nullopt,
              kvs.get(key1));

    for (int i = 21; i < 40; i++) {
        auto key = Key("k" + std::to_string(i));
        auto value = Value("v" + std::to_string(i));
        auto kv = KeyValue(key, value);
        kvs.add(kv);
    }

    EXPECT_EQ(std::nullopt,
              kvs.get(key1));

    kvs.add(kv1);

    for (int i = 41; i < 60; i++) {
        auto key = Key("k" + std::to_string(i));
        auto value = Value("v" + std::to_string(i));
        auto kv = KeyValue(key, value);
        kvs.add(kv);
    }

    EXPECT_STREQ(value1.getValue().c_str(),
                 kvs.get(key1).value().getValue().getValue().c_str());

}

TEST_F(KVS_tester, testMergeAddDelete) {
    KeyValueStore kvs(10);

    for (int i = 0; i < 9; i++) {
        auto key = Key("k" + std::to_string(i));
        auto value = Value("v" + std::to_string(i));
        auto kv = KeyValue(key, value);
        kvs.add(kv);
    }

    auto key = Key("k1");
    auto value = Value("v1");
    auto kv = KeyValue(key, value);

    EXPECT_STREQ(value.getValue().c_str(),
                 kvs.get(key).value().getValue().getValue().c_str());

    kvs.del(key);

    EXPECT_EQ(std::nullopt,
              kvs.get(key));
}


TEST_F(KVS_tester, testMergeAddDeleteAdd) {
    KeyValueStore kvs(10);

    for (int i = 0; i < 8; i++) {
        auto key = Key("k" + std::to_string(i));
        auto value = Value("v" + std::to_string(i));
        auto kv = KeyValue(key, value);
        kvs.add(kv);
    }

    auto key = Key("k1");
    auto value = Value("v1");
    auto kv = KeyValue(key, value);

    EXPECT_STREQ(value.getValue().c_str(),
                 kvs.get(key).value().getValue().getValue().c_str());

    kvs.del(key);

    EXPECT_EQ(std::nullopt,
              kvs.get(key));

    kvs.add(kv);

    EXPECT_STREQ(value.getValue().c_str(),
                 kvs.get(key).value().getValue().getValue().c_str());
}

TEST_F(KVS_tester, testSparse) {
    KeyValueStore kvs(10);

    for (int i = 0; i < 2000; i++) {
        auto key = Key("k" + std::to_string(i));
        auto value = Value("v" + std::to_string(i));
        auto kv = KeyValue(key, value);
        kvs.add(kv);
    }

    for (int i = 0; i < 1000; i++) {
        auto key = Key("k" + std::to_string(i));
        kvs.del(key);
    }

    auto key1 = Key("k1001");
    auto value1 = Value("v1001");
    auto kv1 = KeyValue(key1, value1);

    EXPECT_STREQ(value1.getValue().c_str(),
                 kvs.get(key1).value().getValue().getValue().c_str());

    auto key2 = Key("k999");
    auto value2 = Value("v999");
    auto kv2 = KeyValue(key2, value2);

    EXPECT_EQ(std::nullopt,
              kvs.get(key2));
}

TEST_F(KVS_tester, testFilter) {
    std::vector<Key> vec = {Key("k1"), Key("k2"), Key("k3"), Key("k4"), Key("k5")};
    Filter f(vec);
    for (const auto &el: vec) {
        EXPECT_TRUE(f.isPresent(el));
    }

    EXPECT_FALSE(f.isPresent(Key("k6")));
}

TEST_F(KVS_tester, testClearFile) {
    KeyValueStore kvs(10);

    for (int i = 0; i < 2000; i++) {
        auto key = Key("k" + std::to_string(i));
        auto value = Value("v" + std::to_string(i));
        auto kv = KeyValue(key, value);
        kvs.add(kv);
    }

    for (int i = 0; i <= 1000; i++) {
        auto key = Key("k" + std::to_string(i));
        kvs.del(key);
    }
    std::ifstream ifs("outputData.json");
    std::string line;
    int num = 0;
    while (std::getline(ifs, line)) {
        num++;
    }

    EXPECT_EQ(1000, num);

}
