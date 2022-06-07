#include "FileHandler.h"
#include <iostream>
#include <fstream>
#include <utility>
#include "KeyOffset.h"

void SSTableFileHandler::writeToFile(const json &j) {
    std::ofstream ofs(fileName, std::ios_base::app);
    for (const auto &el: j) {
        ofs << el << std::endl;
        number_of_lines++;
    }
}

void SSTableFileHandler::clear_file() {
    std::ofstream ofs(fileName);
    ofs << "";
    number_of_lines = 0;
}

json SSTableFileHandler::readFromFile(long offset) {
    std::ifstream ifs(fileName);
    for (int i = 0; i < offset; ++i) {
        ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::string value;
    std::getline(ifs, value);
    auto jf = json::parse<>(value);
    KeyOffset ko = KeyOffset(Key(""), 0);
    from_json(jf, ko);
    ifs.seekg(offset);
    return ko;
}

SSTableFileHandler::SSTableFileHandler(std::string s) {
    fileName = std::move(s);
    std::string line;
    std::ifstream file(fileName);
    number_of_lines = 0;
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
    current_offset += to_string(j).size()
#ifdef linux
                      + sizeof('\n');
#elif _WIN32
    + sizeof("\n");
#endif
    std::ofstream ofs(fileName, std::ios_base::app);
    ofs << j << '\n';
    ofs.close();
}

KeyValue DataFileHandler::readFromFile(long offset) {
    std::ifstream ifs(fileName);
    ifs.clear();
    ifs.seekg(offset);
    std::string value;
    std::getline(ifs, value);
    auto jf = json::parse<>(value);
    KeyValue kv = KeyValue("nullptr", "nullptr");
    from_json(jf, kv);

    return kv;
}

DataFileHandler::DataFileHandler(std::string s) {
    fileName = std::move(s);
}
