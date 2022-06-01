#include <vector>
#include <algorithm>
#include "kvs.h"
#include "Log.h"

bool Log::find(Key key) {
    return std::any_of(log.begin(), log.end(), [key](KeyOffset keyOffset) {return keyOffset.getKey().getKey() == key.getKey();});
}

void Log::remove(Key key) {
    for (auto i = log.begin(); i != log.end(); i++) {
        if (i->getKey().getKey() == key.getKey()) {
            log.erase(i);
            return;
        }
    }
}

void Log::clear() {
    log.clear();
}

void Log::add(KeyOffset keyOffset) {
    log.push_back(keyOffset);
}

std::vector<KeyOffset> Log::getLog() {
    return log;
}
