#pragma once

//#include "kvs.h"
#include <utility>
#include <optional>
#include "KeyOffset.h"
#include "fileHandler.h"
//#include "SStable.h"

class SparseSSTable {
    char const *ch = "";
    std::vector<KeyOffset> sparse = {};
    std::pair<std::optional<KeyOffset>, std::optional<KeyOffset>> getBounds(Key key);
    //    поля:
//            array <pair<key, offset>>

public:
    void recount(sstableFileHandler f);
};

