#include <vector>
#include <algorithm>
#include "KVS.h"
#include "Log.h"

std::optional<KeyOffset> Log::find(const Key &key) {
    for (int i = log.size() - 1; i >= 0; i--) {
        if (log[i].getKey().getKey() == key.getKey()) {
            return (KeyOffset(log[i].getKey(), log[i].getOffset(), log[i].deleted));
        }
    }
    return std::nullopt;
}

void Log::remove(const Key &key) {
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

bool Log::add(const KeyOffset &keyOffset) {
    if (is_full())
        return false;
    log.push_back(keyOffset);
    return true;
}

std::vector<KeyOffset> Log::getLog() {
    return log;
}

bool Log::is_full() {
    return log.size() == size;
}
