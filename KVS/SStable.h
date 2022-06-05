#pragma once
#include <utility>
#include <vector>
#include "kvs.h"

struct SSTable {
    fileHandler file;
    SSTable(fileHandler file_) : file(std::move(file_)){}
    void addLog(const std::vector<KeyOffset>& toAdd);

    void find();

    void removeElement();

//    SSTableFabric fabric;
//    filter filter;
//    sparseSSTable sparseSSTable;
};

