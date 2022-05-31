//
// Created by georgii on 31.05.22.
//

#ifndef SHDPROJ_FILEHANDLER_H
#define SHDPROJ_FILEHANDLER_H

#include "json.h"
#include "kvs.h"

using json = nlohmann::json;

struct fileHandler{
//    static std::string fileName;
    static void writeToFile(const json &j);
    static json readFromFile();
};
#endif //SHDPROJ_FILEHANDLER_H
