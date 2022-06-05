#pragma once

#include <optional>
#include "json.h"
//#include "fileHandler.h"
//#include "SStable.h"

using json = nlohmann::json;

class Key {
    const char *key;
    size_t size;
public:
    Key(const char *value, size_t size);

    const char *getKey() const;

    size_t getSize() const;
};

struct Value {
    const char *value;
    size_t size;
public:
    Value(const char *value, size_t size);

    const char *getValue() const;

    size_t getSize() const;
};

class KeyValue {
    Key key;
    Value value;
public:
    KeyValue(const char *key, size_t key_size, const char *value, size_t value_size);

    KeyValue(Key key, Value value);

    Key getKey() const;

    Value getValue() const;
};

void to_json(json &j, const KeyValue &kv);

void to_json(json &j, const std::vector<KeyValue> &kv);

class KeyOffset {
    Key key;
    int offset;
public:
    long getOffset() const;

    Key getKey() const;

    KeyOffset();

    KeyOffset(Key key, int i);
};

void to_json(json &j, const KeyOffset &ko);

void from_json(const json &j, KeyOffset &keyOffset);

void from_json(const json &j, std::vector<KeyOffset> &vec);

void from_json(const json &j, KeyValue &kv);

void from_json(const json &j, std::vector<KeyValue> &vec);