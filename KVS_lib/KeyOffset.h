#pragma once

#include <optional>
#include "json.h"
//#include "fileHandler.h"
//#include "SStable.h"

using json = nlohmann::json;

class Key {
    std::string key;
public:
    Key(std::string value);

    [[nodiscard]] std::string getKey() const;

};

struct Value {
    std::string value;
public:
    Value(std::string value);

    [[nodiscard]] std::string getValue() const;
};

struct KeyValue {
    Key key;
    Value value;
public:
    KeyValue(std::string key, std::string value);

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

    bool deleted /*= false*/;
};

void to_json(json &j, const KeyOffset &ko);

void from_json(const json &j, KeyOffset &keyOffset);

void from_json(const json &j, std::vector<KeyOffset> &vec);

void from_json(const json &j, KeyValue &kv);

void from_json(const json &j, std::vector<KeyValue> &vec);