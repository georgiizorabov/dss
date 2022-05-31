#include "fileHandler.h"
#include <iostream>
#include <fstream>

void fileHandler::writeToFile(const json &j) {
    std::ofstream ofs("output.json");
    ofs << std::setw(4) << j << std::endl;
}

json fileHandler::readFromFile() {
    std::ifstream ifs("output.json");
    auto jf = json::parse<>(ifs);
    return jf;
}
