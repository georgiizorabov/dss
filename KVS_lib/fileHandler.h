#pragma once

#include "json.h"
#include "KeyOffset.h"

using json = nlohmann::json;

struct sstableFileHandler{

    std::string fileName;
    sstableFileHandler(std::string);
    void writeToFile(const json &j);
    json readFromFile();
};

struct dataFileHandler{

    std::string fileName;
    dataFileHandler(std::string);
    void writeToFile(const json &j);
    KeyValue readFromFile(long offset);
};

