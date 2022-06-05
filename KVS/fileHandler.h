#pragma once

#include "json.h"
//#include "kvs.h"

using json = nlohmann::json;

struct fileHandler{

    std::string fileName;
    fileHandler(std::string);
    void writeToFile(const json &j);
    json readFromFile();
};
