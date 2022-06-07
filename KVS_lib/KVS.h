#pragma once

#include <optional>
#include "FileHandler.h"
#include "SStable.h"
#include "KeyOffset.h"
#include "Log.h"

class KeyValueStore {
public:
    KeyValueStore(int sz = 100);

    void add(const KeyValue &);

    std::optional<KeyValue> get(const Key &); // Желательно добавить сюда const в конец (по возможности)
    void del(const Key &);


    Log log;
    SSTable ssTable;
    DataFileHandler file;

};
