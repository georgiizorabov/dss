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

    for (const auto &rec: kv) {
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
    bool deleted;
    j.at("key").get_to(key);
    j.at("deleted").get_to(deleted);
    j.at("offset").get_to(offset);
    keyOffset = KeyOffset(Key(key, 1), atoi(offset.c_str()), deleted);
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

size_t KeyOffset::getOffset() const {
    return offset;
}

KeyOffset::KeyOffset(Key key, size_t i, bool deleted) : key(std::move(key)), offset(i), deleted(deleted) {}

KeyOffset::KeyOffset() : key(Key("1", 1)), offset(1) {}

void to_json(json &j, const KeyOffset &ko) {

    j = json{
            {"key",     ko.getKey().getKey()},
            {"offset",  std::to_string(ko.getOffset())},
            {"deleted", ko.deleted}
    };

}

void to_json(json &j, const std::vector<KeyOffset> &kv) {

    for (const auto &rec: kv) {
        j.push_back(rec);
    }

}


void KeyValueStore::add(const KeyValue &kv) {
    KeyOffset keyOffset = KeyOffset(kv.getKey(), file.current_offset, false);
    file.writeToFile(kv);
    while (!log.add(keyOffset)) {
        ssTable.addLog(log.getLog());
        log.clear();
    }
}

KeyValueStore::KeyValueStore(int sz) : ssTable(
        SSTable(SSTableFileHandler("outputSStable.json"), SparseSSTable("outputSStable.json"))),
                                       file("outputData.json"), log(sz) {}


void KeyValueStore::rewriteDataFile() {
    ssTable.addLog(log.getLog());
    log.clear();
    DataFileHandler copy("outputDataCopy.json");
    auto vec = ssTable.getAll();
    ssTable.clear();
    for (const auto &i: vec) {
        KeyOffset keyOffset = KeyOffset(i.getKey(), copy.current_offset);
        KeyValue keyValue = file.readFromFile(i.getOffset());
        copy.writeToFile(keyValue);
        while (!log.add(keyOffset)) {
            ssTable.addLog(log.getLog());
            log.clear();
        }
    }
    std::remove(file.fileName.c_str());
    std::rename("outputDataCopy.json", "outputData.json");
    copy.fileName = "outputData.json";
    file = copy;
    ssTable.sparseSSTable.recount();
}

std::optional<KeyValue> KeyValueStore::get(const Key &key) {
    auto inLog = log.find(key);
    if (inLog.has_value()) {
        if (inLog.value().deleted) {
            return std::nullopt;
        }
        return file.readFromFile(inLog->getOffset());
    }
    auto offset = ssTable.find(key);
    if (offset.has_value()) {
        return file.readFromFile(offset.value());
    }
    return std::nullopt;
}

void KeyValueStore::del(const Key &k) {
    auto kv = KeyValue(k, Value("none", 4));
    file.writeToFile(kv);
    while (!log.add(KeyOffset(kv.getKey(), ssTable.size + log.getLog().size(), true))) {
        if (ssTable.addLog(log.getLog())) {
            rewriteDataFile();
        }
        log.clear();
    }
    ssTable.deletedElems++;
}

KeyValue::KeyValue(Key key, Value value) : key(std::move(key)), value(std::move(value)) {}