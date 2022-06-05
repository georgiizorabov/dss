#include "SStable.h"
#include "json.h"
//#include "kvs.h"
#include "fileHandler.h"
#include "Filter.h"

using json = nlohmann::json;

void SSTable::addLog(const std::vector<KeyOffset> &vec) {
    json j;

    for (const KeyOffset &ko: vec) {
        j.push_back(ko);
    }
    for (const auto &el: vec) {
        filter.addElement(el.getKey());
    }
    file.writeToFile(j);
    sparseSSTable.recount(file.fileName);
}

std::optional<KeyValue> SSTable::find(const Key &key) {
    if (!filter.isPresent(key)) {
        return std::nullopt;
    }
    auto data = file.readFromFile(); //TODO sparse
    std::vector<KeyValue> v;
    from_json(data, v);
    for (const auto &el: v) {
        if (el.getKey().getKey() == key.getKey()) {
            return (KeyValue(el.getKey(), el.getValue()));
        }
    }
    return std::nullopt;
}

void SSTable::removeElement() {
}
