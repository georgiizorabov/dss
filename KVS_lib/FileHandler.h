#pragma once

#include "json.h"
#include "KeyOffset.h"

using json = nlohmann::json;

struct SSTableFileHandler{

    std::string fileName;
    SSTableFileHandler(std::string);
    void writeToFile(const json &j);
    json readFromFile(long offset);
    json readFromFileAll();
};

struct DataFileHandler{

    std::string fileName;
    DataFileHandler(std::string);
    void writeToFile(const json &j);
    KeyValue readFromFile(long offset);
};

