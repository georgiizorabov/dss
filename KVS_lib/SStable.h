#pragma once
#include <utility>
#include <vector>
#include "KeyOffset.h"
#include "Filter.h"
#include "SparseSSTable.h"

struct SSTable {
    sstableFileHandler file;
    SSTable(sstableFileHandler file_) : file(std::move(file_)){}
    void addLog(const std::vector<KeyOffset>& toAdd);

    std::optional<KeyValue> find(const Key & key);

    void removeElement();

    Filter filter;
    SparseSSTable sparseSSTable;
};

