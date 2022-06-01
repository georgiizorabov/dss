#include "SparseSSTable.h"

std::pair<std::optional<KeyOffset>, std::optional<KeyOffset>> SparseSSTable::getBounds(Key key) {
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

void SparseSSTable::recount(fileHandler file) {
    sparse.clear();
    json js = file.readFromFile();
    size_t size = js.size();
    auto v = js.get<std::vector<KeyOffset>>();
    for (int i = 0; i < js.size(); i += 100) {
        sparse.push_back(v[i]);
    }
}


