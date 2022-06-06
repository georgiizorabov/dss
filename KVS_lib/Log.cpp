#include <vector>
#include <algorithm>
#include "kvs.h"
#include "Log.h"

std::optional<KeyOffset> Log::find(const Key& key) {
    for (const auto &el: log) {
        if (el.getKey().getKey() == key.getKey()) {
            return (KeyOffset(el.getKey(), el.getOffset()));
        }
    }
    return std::nullopt;
}

void Log::remove(const Key& key) {
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

bool Log::add(const KeyOffset& keyOffset) {
    log.push_back(keyOffset);
    if(log.size() >= 10){//TODO: log fullness criteria
        return true;
    }
    return false;
}

std::vector<KeyOffset> Log::getLog() {
    return log;
}
