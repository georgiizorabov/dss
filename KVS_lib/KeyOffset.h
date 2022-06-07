#pragma once

#include <optional>
#include "json.h"

using json = nlohmann::json;

class Key {
    std::string key;
    size_t size;
public:
    Key(std::string value, size_t size);

    std::string getKey() const;

    size_t getSize() const;
};

struct Value {
    std::string value;
    size_t size;
public:
    Value(std::string value, size_t size);

    std::string getValue() const;

    size_t getSize() const;
};

struct KeyValue {
    Key key;
    Value value;
public:
    KeyValue(std::string key, size_t key_size, std::string value, size_t value_size);

    KeyValue(Key  key, Value  value);

    Key getKey() const;

    Value getValue() const;
};

void to_json(json &j, const KeyValue &kv);

void to_json(json &j, const std::vector<KeyValue> &kv);

class KeyOffset {
    Key key;
    size_t offset;
public:
    size_t getOffset() const;

    Key getKey() const;

    KeyOffset();

    KeyOffset(Key key, size_t i, bool deleted = false);

    bool deleted;
};

void to_json(json &j, const KeyOffset &ko);

void from_json(const json &j, KeyOffset &keyOffset);

void from_json(const json &j, std::vector<KeyOffset> &vec);

void from_json(const json &j, KeyValue &kv);

void from_json(const json &j, std::vector<KeyValue> &vec);