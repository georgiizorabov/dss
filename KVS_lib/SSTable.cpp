#include "SStable.h"
#include "json.h"
//#include "kvs.h"
#include "fileHandler.h"
#include "Filter.h"

using json = nlohmann::json;

void SSTable::addLog(const std::vector<KeyOffset> &vec) {
    json j;

    for (const KeyOffset &ko: vec) {
        size++;
        j.push_back(ko);
    }
    for (const auto &el: vec) {
        filter.addElement(el.getKey());
    }

    file.writeToFile(j);
//    sparseSSTable.recount(file.fileName); TODO: uncomment
}

std::optional<long> SSTable::find(const Key &key) {
    if (!filter.isPresent(key)) {
        return std::nullopt;
    }
    auto data = file.readFromFileAll( /* 0  offset */); //TODO sparse
    std::vector<KeyOffset> v;
    from_json(data, v);
    for (const auto &el: v) {
        if (el.getKey().getKey() == key.getKey()) {
            return el.getOffset();
        }
    }
    return std::nullopt;
}

void SSTable::removeElement() {
}
