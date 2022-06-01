#pragma once
#include "kvs.h"
#include "SStable.h"

class Log {
    std::vector<KeyOffset> log;

public:
    void add(KeyOffset keyOffset);

    bool find(Key key);

    void remove(Key key);

    void clear();
};
