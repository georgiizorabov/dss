#pragma once

#include <optional>
#include "fileHandler.h"
#include "SStable.h"
#include "KeyOffset.h"
#include "Log.h"

class KeyValueStore {
public:
    KeyValueStore();

    void add(const KeyValue &);

    std::optional<KeyValue> get(const Key &); // Желательно добавить сюда const в конец (по возможности)
    void del(const Key &);


    Log log;
    SSTable ssTable;
    dataFileHandler file;

//    KeyValueStore(){
//
//    }
};
