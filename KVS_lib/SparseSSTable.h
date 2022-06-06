#pragma once

//#include "kvs.h"
#include <utility>
#include <optional>
#include "KeyOffset.h"
#include "FileHandler.h"
//#include "SStable.h"

class SparseSSTable {
    SSTableFileHandler file;
    std::vector<KeyOffset> sparse = {};
   //    поля:
//            array <pair<key, offset>>

public:
    void recount();
    std::pair<std::optional<KeyOffset>, std::optional<KeyOffset>> getBounds(const Key& key);

    SparseSSTable(SSTableFileHandler fileHandler) : file(std::move(fileHandler)) {}
};

