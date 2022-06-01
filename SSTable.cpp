#include "SStable.h"
#include "json.h"
//#include "kvs.h"
#include "fileHandler.h"
#include "Filter.h"
using json = nlohmann::json;

void SSTable::addLog(const std::vector<KeyOffset> &vec) {
    json j;
    Filter filter;
    for(const KeyOffset& ko : vec){
        j.push_back(ko);
    }
    for(const auto &el : vec){
        filter.addElement(el.getKey());
    }
    fileHandler::writeToFile(j);
//    filter.addElement;
//    sparseSSTable.recount
//    fileHandler.add
}

void SSTable::find() {
}

void SSTable::removeElement() {
}
