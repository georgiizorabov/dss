#pragma once

#include "json.h"
#include "KeyOffset.h"

using json = nlohmann::json;

struct SSTableFileHandler{
    static size_t number_of_lines;

    std::string fileName;
    SSTableFileHandler(std::string);
    void writeToFile(const json &j);
    json readFromFile(long offset);
    json readFromFileAll();


    void clear_file();

    json readFromFileHundred();
};

struct DataFileHandler{
    size_t current_offset = 0;
    std::string fileName;
    DataFileHandler(std::string);
    void writeToFile(const json &j);
    KeyValue readFromFile(long offset);
};

