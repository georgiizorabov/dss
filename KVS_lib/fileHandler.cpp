#include "fileHandler.h"
#include <iostream>
#include <fstream>
#include <utility>
#include "KeyOffset.h"

void sstableFileHandler::writeToFile(const json &j) {
    std::ofstream ofs(fileName);
    ofs << std::setw(4) << j << std::endl;
}

json sstableFileHandler::readFromFile() {
    std::ifstream ifs(fileName);
    auto jf = json::parse<>(ifs);
    return jf;
}

sstableFileHandler::sstableFileHandler(std::string s) {
    fileName = std::move(s);
}


void dataFileHandler::writeToFile(const json &j) {
    std::ofstream ofs(fileName);
    ofs << std::setw(4) << j << std::endl;
}

KeyValue dataFileHandler::readFromFile(long offset) {
    std::ifstream ifs(fileName);
    auto jf = json::parse<>(ifs);
//    std::cout << jf.at(offset) << fflush(stdout);
    KeyValue ret = from_json(jf/*.at(offset)*/);
    return ret;
}

dataFileHandler::dataFileHandler(std::string s) {
    fileName = std::move(s);
}
