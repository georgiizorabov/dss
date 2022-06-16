#include <iostream>
#include <fstream>
//#include "json.h"
#include "KVS_lib/KVS.h"
#include <chrono>
//using json = nlohmann::json;

int main(int argc, char **argv) {
    std::ofstream ofs1("outputData.json");
    std::ofstream ofs2("outputSStable.json");
    ofs1 << "";
    ofs2 << "";

    if (argc < 5) {
        printf("usage: insert numberOfElements, numberOfRequests, procReadReqs, LogSize, ");
        exit(0);
    }

    long N = atoi(argv[1]);
    long M = atoi(argv[1]);
    long p = atoi(argv[1]);
    long sz = atoi(argv[1]);

    long avReq;
    long avRead;
    long avWrite;
    long maxRead = -1;
    long maxWrite = -1;
    long minRead = -1;
    long minWrite = -1;
    std::vector<long> avW;
    std::vector<long> avR;
    KeyValueStore kvs(sz);

    for (int i = 0; i < N; i++) {
        auto key = Key("k" + std::to_string(rand() % (N + M)));
        auto value = Value("v" + std::to_string(i));
        auto kv = KeyValue(key, value);

        kvs.add(kv);
    }

    for (int i = 0; i < M / 100 * p; i++) {

        auto key = Key("k" + std::to_string(rand() % (N + M)));
        auto value = Value("v" + std::to_string(i));
        auto kv = KeyValue(key, value);

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        kvs.add(kv);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        long t = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        avW.push_back(t);
        if (t < minWrite || !minWrite) {
            minWrite = t;
        }
        if (t > maxWrite || !maxWrite) {
            maxWrite = t;
        }
    }

    avWrite = std::reduce(avW.begin(), avW.end()) / avW.size();

    for (int i = 0; i < M - M / 100 * p; i++) {

        auto key = Key("k" + std::to_string(rand() % N));

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        kvs.get(key);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        long t = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        avR.push_back(t);
        if (t < minRead || !minRead) {
            minRead = t;
        }
        if (t > maxRead || !maxRead) {
            maxRead = t;
        }

    }
    avRead = std::reduce(avR.begin(), avR.end()) / avR.size();
    avW.insert(avW.end(), avR.begin(), avR.end());
    avReq = std::reduce(avW.begin(), avW.end()) / avW.size();

    std::cout << "среднее время звпроса: " << avReq << '\n' <<
              "среднее время звпроса на чтение: " << avRead << '\n' <<
              "среднее время звпроса на запись: " << avWrite << '\n' <<
              "максимальное время звпроса на чтение: " << maxRead << '\n' <<
              "максимальное время звпроса на запись: " << maxWrite << '\n' <<
              "минимальное время звпроса на чтение: " << minRead << '\n' <<
              "минимальное время звпроса на запись: " << minWrite;

    return 0;
}
