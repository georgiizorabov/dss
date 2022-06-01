#pragma once
class Log {
    std::vector<KeyOffset> log = {};

public:
    void add(KeyOffset keyOffset);

    bool find(Key key);

    void remove(Key key);

    void clear();

    std::vector<KeyOffset> getLog();
};
