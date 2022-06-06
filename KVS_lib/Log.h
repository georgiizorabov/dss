#pragma once
class Log {
    std::vector<KeyOffset> log = {};

public:
    bool add(const KeyOffset& keyOffset);

    std::optional<KeyOffset> find(const Key& key);

    void remove(const Key& key);

    void clear();

    std::vector<KeyOffset> getLog();
};
