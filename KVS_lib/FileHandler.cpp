#include "FileHandler.h"
#include <iostream>
#include <fstream>
#include <utility>
#include "KeyOffset.h"

void SSTableFileHandler::writeToFile(const json &j) {
    std::ofstream ofs(fileName, std::ios_base::app);
    for (const auto &el: j) {
        ofs << el << std::endl;
    }
    number_of_lines++;
}

json SSTableFileHandler::readFromFile(long offset) {
    std::ifstream ifs(fileName);
    for (int i = 0; i < offset; ++i) {
        ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::string value;
    std::getline(ifs, value);
    auto jf = json::parse<>(value);
    KeyOffset ko = KeyOffset(Key("nullptr", 0), 0); // FTODO change
    from_json(jf, ko);

    return ko;
}

SSTableFileHandler::SSTableFileHandler(std::string s) : number_of_lines(0) {
    fileName = std::move(s);
    std::string line;
    std::ifstream file(fileName);

    while (std::getline(file, line))
        ++number_of_lines;
    file.close();
}

json SSTableFileHandler::readFromFileAll() {
    std::ifstream ifs(fileName);
    std::string value;
    json j;
    while (std::getline(ifs, value)) {
        j.push_back(json::parse<>(value));
    }
    return j;
}


void DataFileHandler::writeToFile(const json &j) {
    std::ofstream ofs(fileName, std::ios_base::app);
    ofs << j << std::endl;
}

KeyValue DataFileHandler::readFromFile(long offset) {
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

DataFileHandler::DataFileHandler(std::string s) {
    fileName = std::move(s);
}
