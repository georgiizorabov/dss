#include <iostream>
#include <fstream>
#include "json.h"
#include "kvs.h"
//#include "Log.h"
#include "SStable.h"
using json = nlohmann::json;

int main() {

//    fileHandler::fileName = "output.json";

    auto kv1 = KeyValue("k1", 1, "v1", 1);
    auto kv2 = KeyValue("k2", 1, "v2", 1);
    auto kv3 = KeyValue("k3", 1, "v3", 1);
    json j;

    j.push_back(kv1);
    j.push_back(kv2);
    j.push_back(kv3);

//    std::ofstream o("output.json");
//    o << std::setw(4) << j << std::endl;
//
//    std::ifstream ifs("output.json");
//    auto jf = json::parse<>(ifs);
//    for (const auto& el: jf) {
//        std::cout << el.dump();
//    }

    auto ko1 = KeyOffset(Key("k1", 1), 1);
    auto ko2 = KeyOffset(Key("k2", 1), 1);
    auto ko3 = KeyOffset(Key("k3", 1), 1);

    SSTable ssTable;
    ssTable.addLog({ko1, ko2, ko3});
    return 0;
}
