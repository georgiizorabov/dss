#pragma once

#include "json.h"
//#include "kvs.h"

using json = nlohmann::json;

struct fileHandler{
//    static std::string fileName;
    static void writeToFile(const json &j);
    static json readFromFile();
};
