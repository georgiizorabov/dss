#pragma once
#include <vector>
#include "kvs.h"

struct SSTable {
    void addLog(const std::vector<KeyOffset>& toAdd);

    void find();

    void removeElement();

//    SSTableFabric fabric;
//    filter filter;
//    sparseSSTable sparseSSTable;
};

