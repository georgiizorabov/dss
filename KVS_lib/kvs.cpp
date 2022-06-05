#include <fstream>
#include "json.h"
#include "kvs.h"

using json = nlohmann::json;

Key::Key(const char *value, size_t size) :
        key(value),
        size(size) {

}

const char *Key::getKey() const {
    return key;
}

size_t Key::getSize() const {
    return size;
}

Value::Value(const char *value, size_t size) :
        value(value), size(size) {
}

const char *Value::getValue() const {
    return value;
}

size_t Value::getSize() const {
    return size;
}

KeyValue::KeyValue(const char *key, size_t key_size, const char *value, size_t value_size) :
        key(Key(key, key_size)), value(Value(value, value_size)) {
}

Value KeyValue::getValue() const {
    return value;
}

Key KeyValue::getKey() const {
    return key;
}

void to_json(json &j, const KeyValue &kv) {
    j = json{
            {"key",   kv.getKey().getKey()},
            {"value", kv.getValue().getValue()}
    };
}

void to_json(json &j, const std::vector<KeyValue> &kv) {

    for (auto rec: kv) {
        j.push_back(rec);
    }

}

//KeyValue from_json(const json &j) {
//    std::string key;
//    std::string value;
//    j.at("key").get_to(key);
//    j.at("value").get_to(value);
//    KeyValue keyValue = KeyValue(Key(key.c_str(), 64), Value(value.c_str(), 64));
//
//    return keyValue;
//}
void from_json(const json &j, KeyValue &kv){
    std::string key;
    std::string value;
    j.at("key").get_to(key);
    j.at("value").get_to(value);
    kv = KeyValue(Key(key.c_str(), 64), Value(value.c_str(), 64));
}


void from_json(const json &j, std::vector<KeyValue> &vec) {
    for (const json &i: j) {
        KeyValue kv = KeyValue(nullptr, 0, nullptr, 0);
        from_json(i, kv);
        vec.push_back(kv);
    }
}


void from_json(const json &j, KeyOffset &keyOffset) {
    std::string key;
    std::string offset;
    j.at("key").get_to(key);
    j.at("offset").get_to(offset);
    keyOffset = KeyOffset(Key(key.c_str(), 64), atoi(offset.c_str()));
}


void from_json(const json &j, std::vector<KeyOffset> &vec) {
    for (const json &i: j) {
        KeyOffset keyOffset;
        from_json(i, keyOffset);
        vec.push_back(keyOffset);
    }
}


Key KeyOffset::getKey() const {
    return key;
}

long KeyOffset::getOffset() const {
    return offset;
}

KeyOffset::KeyOffset(Key key, int i) : key(key), offset(i) {}

KeyOffset::KeyOffset() : key(Key("1", 1)), offset(1) {}

void to_json(json &j, const KeyOffset &ko) {

    j = json{
            {"key",    ko.getKey().getKey()},
            {"offset", ko.getOffset()}
    };

}

void to_json(json &j, const std::vector<KeyOffset> &kv) {

    for (auto rec: kv) {
        j.push_back(rec);
    }

}

void KeyValueStore::add(const KeyValue &kv) {
    file.writeToFile(kv);
    log.add(KeyOffset(kv.getKey(), log.getLog().size()));
}

KeyValueStore::KeyValueStore() : ssTable(SSTable(sstableFileHandler("outputSStable.json"))), file("outputData.json") {}

std::optional<KeyValue> KeyValueStore::get(const Key &key) {
    auto inLog = log.find(key);
    if (inLog.has_value()) {
        return file.readFromFile(inLog->getOffset());
    }
    return ssTable.find(key);
}

KeyValue::KeyValue(const Key key, const Value value) : key(key), value(value) {}