#include "SparseSSTable.h"

std::pair<std::optional<KeyOffset>, std::optional<KeyOffset>> SparseSSTable::getBounds(const Key& key) {
    std::optional<KeyOffset> start;
    std::optional<KeyOffset> end;
    for (auto & i : sparse) {
        if (strcmp(i.getKey().getKey().c_str(), key.getKey().c_str()) <= 0)
            start = i;
        if (strcmp(i.getKey().getKey().c_str(), key.getKey().c_str()) >= 0) {
            end = i;
            break;
        }
    }
    return {start, end};
}

void SparseSSTable::recount() {
    sparse.clear();
    size_t size = SSTableFileHandler::number_of_lines;
    for (int i = 0; i < size; i += 100) {
        sparse.push_back(file.readFromFile(i));
    }
}


