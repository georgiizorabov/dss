#pragma once

#include <utility>
#include <vector>
#include "KeyOffset.h"
#include "Filter.h"
#include "SparseSSTable.h"

struct SSTable {
    SSTableFileHandler file;

    SSTable(SSTableFileHandler file_) : sparseSSTable(file_),  file(std::move(file_)) {}

    void addLog(const std::vector<KeyOffset> &toAdd);

    long size = 0;

    std::optional<long> find(const Key &key);

    void removeElement();

    Filter filter;
    SparseSSTable sparseSSTable;
};

