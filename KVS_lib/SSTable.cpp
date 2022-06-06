#include "SStable.h"
#include "json.h"
//#include "kvs.h"
#include "FileHandler.h"
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
    sparseSSTable.recount();
}

std::optional<long> SSTable::find(const Key &key) {
    if (!filter.isPresent(key)) {
        return std::nullopt;
    }
    auto bounds = sparseSSTable.getBounds(key);
    if (bounds.first.has_value()) {
        long long end_search = file.number_of_lines;
        if (bounds.second.has_value())
            end_search = bounds.second->getOffset();
        for (auto i = bounds.first->getOffset(); i < end_search; i++) {
            if (file.readFromFile(i).get<KeyOffset>().getKey().getKey() == key.getKey())
                return file.readFromFile(i).get<KeyOffset>().getOffset();
        }
    }
    /*auto data = file.readFromFileAll( *//* 0  offset *//*);
    std::vector<KeyOffset> v;
    from_json(data, v);
    for (const auto &el: v) {
        if (el.getKey().getKey() == key.getKey()) {
            return el.getOffset();
        }
    }
    */
    return std::nullopt;
}

void SSTable::removeElement() {
}
