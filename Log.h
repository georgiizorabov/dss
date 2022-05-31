//
// Created by Fedya on 31.05.2022.
//

#ifndef KVS_LOG_H
#define KVS_LOG_H

#endif //KVS_LOG_H

class Log {
    std::vector<KeyOffset> log;

public:
    void add(KeyOffset keyOffset);

    bool find(Key key);

    void remove(Key key);

    void clear();
};
