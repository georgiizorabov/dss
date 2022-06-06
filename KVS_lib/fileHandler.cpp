#include "fileHandler.h"
#include <iostream>
#include <fstream>
#include <utility>
#include "KeyOffset.h"

void sstableFileHandler::writeToFile(const json &j) {
    std::ofstream ofs(fileName, std::ios_base::app);
    for (const auto &el: j) {
        ofs << el << std::endl;
    }
}

json sstableFileHandler::readFromFile(long offset) {
    std::ifstream ifs(fileName);
    for (int i = 0; i < offset; ++i) {
        ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::string value;
    std::getline(ifs, value);
    auto jf = json::parse<>(value);
    KeyOffset ko = KeyOffset(Key("nullptr", 0), 0); // TODO change
    from_json(jf, ko);

    return ko;
}

sstableFileHandler::sstableFileHandler(std::string s) {
    fileName = std::move(s);
}

json sstableFileHandler::readFromFileAll() {
    std::ifstream ifs(fileName);
    std::string value;
    json j;
    while (std::getline(ifs, value)) {
        j.push_back(json::parse<>(value));
    }
    return j;
}


void dataFileHandler::writeToFile(const json &j) {
    std::ofstream ofs(fileName, std::ios_base::app);
    ofs << j << std::endl;
}

KeyValue dataFileHandler::readFromFile(long offset) {
    std::ifstream ifs(fileName);
    for (int i = 0; i < offset; ++i) {
        ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::string value;
    std::getline(ifs, value);
    auto jf = json::parse<>(value);
    KeyValue kv = KeyValue("nullptr", 0, "nullptr", 0);
    from_json(jf, kv);

    return kv;
}

dataFileHandler::dataFileHandler(std::string s) {
    fileName = std::move(s);
}
