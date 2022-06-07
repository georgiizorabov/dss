#include "SparseSSTable.h"

size_t SSTableFileHandler::number_of_lines = 0;

std::pair<std::optional<KeyOffset>, std::optional<KeyOffset>> SparseSSTable::getBounds(const Key &key) {
    std::optional<KeyOffset> start;
    std::optional<KeyOffset> end;
//    for (auto & i : sparse) {
    for (size_t i = 0; i < sparse.size(); i++) {
        if (strcmp(sparse[i].getKey().getKey().c_str(), key.getKey().c_str()) <= 0)
            start = sparse[i];
        if (strcmp(sparse[i].getKey().getKey().c_str(), key.getKey().c_str()) > 0) {
            end = sparse[i];
            break;
        }
    }
    return {start, end};
}

void SparseSSTable::recount() {
    sparse.clear();
    size_t size = SSTableFileHandler::number_of_lines;
    for (int i = 0; i < size; i += 100) {
        sparse.emplace_back(file.readFromFile(i).get<KeyOffset>().getKey(), i);
    }
}


