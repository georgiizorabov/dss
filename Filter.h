#pragma once

#include "bloom_filter.hpp"
#include <iostream>
#include "kvs.h"

class Filter {
    bloom_parameters parameters;
    bloom_filter filter;

    Filter(const std::vector<Key> &vec);

    void addElement(const Key &k);

    bool isPresent(const Key &k);

    void removeElement();

    void clear();

};

