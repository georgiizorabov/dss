#include "SStable.h"
#include "json.h"
//#include "kvs.h"
#include "FileHandler.h"
#include "Filter.h"
#include <climits>
#include <set>
#include <algorithm>
#include <vector>

using json = nlohmann::json;

void SSTable::addLog(const std::vector<KeyOffset> &vec) {
    json j;
    std::vector<KeyOffset> viOld = file.readFromFileAll().get<std::vector<KeyOffset>>();
    std::vector<KeyOffset> viNew;
    for (const KeyOffset &ko: vec) {
        size++;
        viNew.push_back(ko);
    }
    std::vector<std::pair<KeyOffset, int>> viNewInd;
    std::vector<std::pair<KeyOffset, int>> viOldInd;
    for (int i = 0; i < viNew.size(); i++) {
        viNewInd.emplace_back(viNew[i], i);
    }
    for (auto &i: viOld) {
        viOldInd.emplace_back(i, INT_MAX);
    }

    std::vector<std::pair<KeyOffset, int>> viMergedInd;

    std::merge(viOldInd.begin(), viOldInd.end(), viNewInd.begin(), viNewInd.end(),
               std::back_inserter(viMergedInd),
               [](const std::pair<KeyOffset, int> &a, const std::pair<KeyOffset, int> &b) {
                   return a.first.getKey().getKey() == b.first.getKey().getKey() ?
                          a.second < b.second : a.first.getKey().getKey() < b.first.getKey().getKey();
               });

    std::vector<KeyOffset> viMerged;
    std::unordered_map<std::string, int> mp{};

    for (int i = 0; i < viMergedInd.size(); i++) {

        if ((i != 0 && (viMergedInd[i].first.getKey().getKey() == viMergedInd[i - 1].first.getKey().getKey()))
            || viMergedInd[i].first.deleted) {
            continue;
        }

        viMerged.push_back(viMergedInd[i].first);
    }

    file.clear_file();
    file.writeToFile(json(viMerged));
    for (const auto &el: vec) {
        filter.addElement(el.getKey());
        if (filter.deletedElems >= 1000) {
            filter.clear();
            std::vector<Key> filterVec;
            std::transform(viMerged.begin(), viMerged.end(), std::back_inserter(filterVec),
                           [](KeyOffset const &ko) { return ko.getKey(); });
            filter = Filter(filterVec);
        }
    }

    sparseSSTable.recount();
}

std::optional<long> SSTable::find(const Key &key) {
    if (!filter.isPresent(key)) {
        return std::nullopt;
    }
    auto bounds = sparseSSTable.getBounds(key);
    if (bounds.first.has_value()) {
        long long end_search = SSTableFileHandler::number_of_lines;
        if (bounds.second.has_value())
            end_search = bounds.second->getOffset();
        for (auto i = bounds.first->getOffset(); i < end_search; i++) {
            if (file.readFromFile(i).get<KeyOffset>().getKey().getKey() == key.getKey())
                return file.readFromFile(i).get<KeyOffset>().getOffset();
        }
    }

    return std::nullopt;
}

std::vector<KeyOffset> SSTable::getAll() {
    return file.readFromFileAll().get<std::vector<KeyOffset>>();
}

void SSTable::clear() {
    file.clear_file();
}