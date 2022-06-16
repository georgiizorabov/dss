#pragma once

#include <utility>
#include <vector>
#include "KeyOffset.h"
#include "Filter.h"
#include "SparseSSTable.h"

struct SSTable {
    SSTableFileHandler file;

    SSTable(SSTableFileHandler file_, SparseSSTable sparseSsTable_) : sparseSSTable(std::move(sparseSsTable_)),  file(std::move(file_)) {}

    bool addLog(const std::vector<KeyOffset> &vec);

    long size = 0;

    int deletedElems = 0;

    std::optional<long> find(const Key &key);

    std::vector<KeyOffset> getAll();
    Filter filter;
    SparseSSTable sparseSSTable;

    void clear();

    std::vector<KeyOffset> getHundred();
};

