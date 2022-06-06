#pragma once
class Log {
    std::vector<KeyOffset> log = {};
    size_t size;
public:
    explicit Log(size_t size_) : size(size_) {}
    bool add(const KeyOffset& keyOffset);

    std::optional<KeyOffset> find(const Key& key);

    void remove(const Key& key);

    void clear();

    bool is_full();
    std::vector<KeyOffset> getLog();
};
