#pragma once

#include "bloom_filter.hpp"
#include <iostream>
#include "kvs.h"

struct Filter {
    bloom_parameters parameters;
    bloom_filter filter;

    Filter(const std::vector<Key> &vec);

    void addElement(const Key &k);

    bool isPresent(const Key &k) const;

    void removeElement();

    void clear();

    Filter();
};

