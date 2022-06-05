#include "fileHandler.h"
#include <iostream>
#include <fstream>
#include <utility>
#include "KeyOffset.h"

void sstableFileHandler::writeToFile(const json &j) {
    std::ofstream ofs(fileName, std::ios_base::app);
    ofs << j << std::endl;
}

json sstableFileHandler::readFromFile(long offset) {
    std::ifstream ifs(fileName);
//    std::cout << jf.at(offset) << fflush(stdout);
    for (int i = 0; i < offset - 1; ++i) {
        ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::string value;
    std::getline(ifs, value);
    auto jf = json::parse<>(value);
    KeyValue kv = KeyValue(nullptr, 0, nullptr, 0);
    from_json(jf, kv);

    return kv;
}

sstableFileHandler::sstableFileHandler(std::string s) {
    fileName = std::move(s);
}


void dataFileHandler::writeToFile(const json &j) {
    std::ofstream ofs(fileName, std::ios_base::app);
    ofs << j << std::endl;
}

KeyValue dataFileHandler::readFromFile(long offset) {
    std::ifstream ifs(fileName);
//    std::cout << jf.at(offset) << fflush(stdout);
    for (int i = 0; i < offset - 1; ++i) {
        ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::string value;
    std::getline(ifs, value);
    auto jf = json::parse<>(value);
    KeyValue kv = KeyValue(nullptr, 0, nullptr, 0);
    from_json(jf, kv);

    return kv;
}

dataFileHandler::dataFileHandler(std::string s) {
    fileName = std::move(s);
}
