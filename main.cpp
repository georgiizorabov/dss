#include <iostream>
#include "json.h"
#include "kvs.h"
#include "SStable.h"
#include "Log.h"

using json = nlohmann::json;

int main() {

//    fileHandler::fileName = "output.json";
    Log log = Log();

    auto ko1 = KeyOffset(Key("k1", 1), 1);
    auto ko2 = KeyOffset(Key("k2", 1), 1);
    auto ko3 = KeyOffset(Key("k3", 1), 1);

    log.add(ko1);
    log.add(ko2);
    log.add(ko3);

    SSTable ssTable(fileHandler("output.txt"));
    ssTable.addLog(log.getLog());

    return 0;
}
