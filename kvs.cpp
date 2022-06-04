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

void from_json(const json& j, KeyOffset& keyOffset) {
    std::string key;
    std::string offset;
    j.at("key").get_to(key);
    j.at("offset").get_to(offset);
    keyOffset = KeyOffset(Key(key.c_str(), 64), atoi(offset.c_str()));
}


void from_json(const json& j, std::vector<KeyOffset> &vec) {

}


Key KeyOffset::getKey() const {
    return key;
}

int KeyOffset::getOffset() const {
    return offet;
}

KeyOffset::KeyOffset(Key key, int i) : key(key), offet(i) {}

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
