#pragma once

#include "kvs.h"
#include <utility>
#include <optional>
#include "SStable.h"

class SparseSSTable {
    char const *ch = "";
    std::vector<KeyOffset> sparse = {};
    std::pair<std::optional<KeyOffset>, std::optional<KeyOffset>> getBounds(Key key);
    void recount(fileHandler f);
//    поля:
//            array <pair<key, offset>>

};

