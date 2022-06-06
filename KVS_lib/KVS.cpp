#include <fstream>
#include <utility>
#include "json.h"
#include "KVS.h"

using json = nlohmann::json;

Key::Key(std::string value, size_t size) :
        key(std::move(value)),
        size(size) {

}

std::string Key::getKey() const {
    return key;
}

size_t Key::getSize() const {
    return size;
}

Value::Value(std::string value, size_t size) :
        value(std::move(value)), size(size) {
}

std::string Value::getValue() const {
    return value;
}

size_t Value::getSize() const {
    return size;
}

KeyValue::KeyValue(std::string key, size_t key_size, std::string value, size_t value_size) :
        key(Key(std::move(key), key_size)), value(Value(std::move(value), value_size)) {
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

    for (const auto& rec: kv) {
        j.push_back(rec);
    }

}

void from_json(const json &j, KeyValue &kv) {
    std::string key;
    std::string value;
    j.at("key").get_to(key);
    j.at("value").get_to(value);
    kv = KeyValue(Key(key, 1), Value(value, 1));
}


void from_json(const json &j, std::vector<KeyValue> &vec) {
    for (const json &i: j) {
        KeyValue kv = KeyValue("nullptr", 0, "nullptr", 0);
        from_json(i, kv);
        vec.push_back(kv);
    }
}


void from_json(const json &j, KeyOffset &keyOffset) {
    std::string key;
    std::string offset;
    j.at("key").get_to(key);
    j.at("offset").get_to(offset);
    keyOffset = KeyOffset(Key(key, 64), atoi(offset.c_str()));
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

KeyOffset::KeyOffset(Key key, long i) : key(std::move(key)), offset(i) {}

KeyOffset::KeyOffset() : key(Key("1", 1)), offset(1) {}

void to_json(json &j, const KeyOffset &ko) {

    j = json{
            {"key",    ko.getKey().getKey()},
            {"offset", std::to_string(ko.getOffset())}
    };

}

void to_json(json &j, const std::vector<KeyOffset> &kv) {

    for (const auto& rec: kv) {
        j.push_back(rec);
    }

}

void KeyValueStore::add(const KeyValue &kv) {
    file.writeToFile(kv);
    if(log.add(KeyOffset(kv.getKey(), ssTable.size + log.getLog().size()))){
        ssTable.addLog(log.getLog());
        log.clear();
    }
}

KeyValueStore::KeyValueStore() : ssTable(SSTable(SSTableFileHandler("outputSStable.json"))), file("outputData.json") {}

std::optional<KeyValue> KeyValueStore::get(const Key &key) {
    auto inLog = log.find(key);
    if (inLog.has_value()) {
        return file.readFromFile(inLog->getOffset());
    }
    auto offset = ssTable.find(key);
    if(offset.has_value()) {
        return file.readFromFile(offset.value());
    }
    return std::nullopt;
}

KeyValue::KeyValue(Key  key, Value  value) : key(std::move(key)), value(std::move(value)) {}