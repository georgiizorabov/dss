#include "SStable.h"
#include "json.h"
//#include "kvs.h"
#include "fileHandler.h"
using json = nlohmann::json;

void SSTable::addLog(const std::vector<KeyOffset> &vec) {
    json j;
    for(const KeyOffset& ko : vec){
        j.push_back(ko);
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
