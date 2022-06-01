#pragma once

#include "kvs.h"
#include <utility>
#include <optional>
#include "SStable.h"

class SparseSSTable {
    char const *ch = "";
    std::vector<KeyOffset> sparse = {};
    std::pair<std::optional<KeyOffset>, std::optional<KeyOffset>> getBounds(Key key) {
        std::optional<KeyOffset> start;
        std::optional<KeyOffset> end;

        for (int i = 0; i < sparse.size(); ++i) {
            if (strcmp(sparse[i].getKey().getKey(), key.getKey()) <= 0)
                start = sparse[i];
            if (strcmp(sparse[i].getKey().getKey(), key.getKey()) >= 0) {
                end = sparse[i];
                break;
            }
        }

        return {start, end};
    }
    void recount() {

    }
//    поля:
//            array <pair<key, offset>>

};

