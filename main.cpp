#include <iostream>
#include <fstream>
//#include "json.h"
#include "KVS_lib/KVS.h"
#include <chrono>

//using json = nlohmann::json;
struct res {
    long N, M, p, sz;
    long avReq;
    long avRead;
    long avWrite;
    long maxRead;
    long maxWrite;
    long minRead;
    long minWrite;
};

int main(int argc, char **argv) {
    std::ofstream ofs1("outputData.json");
    std::ofstream ofs2("outputSStable.json");
    ofs1 << "";
    ofs2 << "";

    std::vector<long> values = {1, 1, 1, 1};
    std::vector<long> Ms = {10, 25, 50, 75, 100, 500, 1000, 2000, 10000, 20000};
    std::vector<long> Ns = {10, 100, 1000, 5000, 10000};
    std::vector<long> Ps = {10, 25, 50, 75, 90};
    std::vector<long> Szs = {10, 100, 500, 1000, 2000};
    std::vector<res> res1;
    std::vector<res> res2;
    long N, M, p, sz;
    std::cout << "All adds then all gets: \n";
    for (long m: Ms) { // перебираем M
        try {
            M = m; // M -- количество запросов, обращенных к хранилищу в процессе тестирования
            for (long n: Ns) { // перебираем N
                N = n; // N -- количество элементов в хранилище на момент начала теста
                for (long P: Ps) { // перебираем p
                    p = P; // p -- целое число от 0 до 100 -- процент запросов на чтение
                    for (long s: Szs) { // перебираем sz
                        sz = s; // sz -- размер лога

                        long avReq;
                        long avRead;
                        long avWrite;
                        long maxRead = -1;
                        long maxWrite = -1;
                        long minRead = 0;
                        long minWrite = 0;


                        std::vector<long> avW;
                        std::vector<long> avR;
                        KeyValueStore kvs(sz);

                        for (int i = 0; i < N; i++) {
                            auto key = Key("k" + std::to_string(rand() % (N + M)));
                            auto value = Value("v" + std::to_string(i));
                            auto kv = KeyValue(key, value);

                            kvs.add(kv);
                        } // кладем N элементов

                        for (int i = 0; i < M * p / 100; i++) { // пишем

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

                        avWrite = std::accumulate(avW.begin(), avW.end(), 0) / avW.size();

                        for (int i = 0; i < M - M * p / 100; i++) { // читаем

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
                        avRead = std::accumulate(avR.begin(), avR.end(), 0) / avR.size();
                        avW.insert(avW.end(), avR.begin(), avR.end());
                        avReq = std::accumulate(avW.begin(), avW.end(), 0) / avW.size();

                        std::cout << "N = " << N << "; M = " << M << "; p = " << p << "; sz = " << sz << '\n' <<
                                  "average time of request: " << avReq << '\n' <<
                                  "average time of request get: " << avRead << '\n' <<
                                  "average time of request add: " << avWrite << '\n' <<
                                  "max time of request get: " << maxRead << '\n' <<
                                  "max time of request add: " << maxWrite << '\n' <<
                                  "min time of request get: " << minRead << '\n' <<
                                  "min time of request add: " << minWrite <<
                                  "\n-----------------------------------------------------\n";
                        res1.push_back({N, M, p, sz, avReq,
                                        avRead,
                                        avWrite,
                                        maxRead,
                                        maxWrite,
                                        minRead,
                                        minWrite,});
                    }
                }
            }
        } catch (...) {
//            std::cout << "sth went wrong при "
//                      << "N = " << N << "; M = " << M << "; p = " << p << "; sz = " << sz << '\n';
        }
    }
    std::cout
            << "\n=======================================================\nHalf adds then half gets then rest adds then rest gets: \n";

    for (long m: Ms) { // перебираем M
        try {
            M = m; // M -- количество запросов, обращенных к хранилищу в процессе тестирования
            for (long n: Ns) { // перебираем N
                N = n; // N -- количество элементов в хранилище на момент начала теста
                for (long P: Ps) { // перебираем p
                    p = P; // p -- целое число от 0 до 100 -- процент запросов на чтение
                    for (long s: Szs) { // перебираем sz
                        sz = s; // sz -- размер лога

                        long avReq;
                        long avRead;
                        long avWrite;
                        long maxRead = -1;
                        long maxWrite = -1;
                        long minRead = 0;
                        long minWrite = 0;


                        std::vector<long> avW;
                        std::vector<long> avR;
                        KeyValueStore kvs(sz);

                        for (int i = 0; i < N; i++) {
                            auto key = Key("k" + std::to_string(rand() % (N + M)));
                            auto value = Value("v" + std::to_string(i));
                            auto kv = KeyValue(key, value);

                            kvs.add(kv);
                        } // кладем N элементов
                        for (int cnt = 0; cnt < 2; cnt++) {
                            for (int i = 0; i < (M * p / 100) / 2; i++) { // пишем

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
                            if (!avW.size()) {
                                continue;
                            }
                            avWrite = std::accumulate(avW.begin(), avW.end(), 0) / avW.size();

                            for (int i = 0; i < (M - M * p / 100) / 2; i++) { // читаем

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
                        }

                        if (!avR.size()) {
                            continue;
                        }

                        avRead = std::accumulate(avR.begin(), avR.end(), 0) / avR.size();
                        avW.insert(avW.end(), avR.begin(), avR.end());
                        avReq = std::accumulate(avW.begin(), avW.end(), 0) / avW.size();

                        std::cout << "N = " << N << "; M = " << M << "; p = " << p << "; sz = " << sz << '\n' <<
                                  "average time of request: " << avReq << '\n' <<
                                  "average time of request get: " << avRead << '\n' <<
                                  "average time of request add: " << avWrite << '\n' <<
                                  "max time of request get: " << maxRead << '\n' <<
                                  "max time of request add: " << maxWrite << '\n' <<
                                  "min time of request get: " << minRead << '\n' <<
                                  "min time of request add: " << minWrite <<
                                  "\n-----------------------------------------------------\n";
                        res2.push_back({N, M, p, sz, avReq,
                                        avRead,
                                        avWrite,
                                        maxRead,
                                        maxWrite,
                                        minRead,
                                        minWrite});
                    }
                }
            }
        } catch (...) {
//            std::cout << "sth went wrong при "
//                      << "N = " << N << "; M = " << M << "; p = " << p << "; sz = " << sz << '\n';
        }
    }
    std::cout
            << "N, M, p, sz, avReq, avRead, avWrite, maxRead, maxWrite, minRead, minWrite'\n";
    for (auto el: res1) {
        std::cout << el.N << ",\t" << el.M << ",\t" << el.p << ",\t" << el.sz << ",\t" << el.avReq << ",\t" << el.avRead
                  << ",\t" << el.avWrite << ",\t" << el.maxRead << ",\t" << el.maxWrite
                  << el.minRead << ",\t" << el.minWrite << '\n';
    }
    std::cout
            << "\n=================================================================================================\n";
    for (auto el: res2) {
        std::cout << el.N << ",\t" << el.M << ",\t" << el.p << ",\t" << el.sz << ",\t" << el.avReq << ",\t" << el.avRead
                  << ",\t" << el.avWrite << ",\t" << el.maxRead << ",\t" << el.maxWrite
                  << el.minRead << ",\t" << el.minWrite << '\n';
    }
    return 0;
}
