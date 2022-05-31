
#ifndef SHDPROJ_SSTABLE_H
#define SHDPROJ_SSTABLE_H

#include <vector>
#include "kvs.h"

class SSTable {
    void addLog(const std::vector<KeyOffset>& toAdd);

    void find();

    void removeElement();

//    SSTableFabric fabric;
//    filter filter;
//    sparseSSTable sparseSSTable;
};

#endif //SHDPROJ_SSTABLE_H
