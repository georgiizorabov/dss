#include "fileHandler.h"
#include <iostream>
#include <fstream>
#include <utility>

void fileHandler::writeToFile(const json &j) {
    std::ofstream ofs(fileName);
    ofs << std::setw(4) << j << std::endl;
}

json fileHandler::readFromFile() {
    std::ifstream ifs(fileName);
    auto jf = json::parse<>(ifs);
    return jf;
}

fileHandler::fileHandler(std::string s) {
    fileName = std::move(s);
}
