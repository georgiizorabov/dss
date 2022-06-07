#include "bloom_filter.hpp"
#include <iostream>
#include "Filter.h"
#include "KVS.h"


Filter::Filter(const std::vector<Key> &vec) : Filter() {
    // Insert some keys
    for (const auto &i: vec) {
        filter.insert(i.getKey());
    }

}

void Filter::addElement(const Key &k) {
    filter.insert(k.getKey());
}

bool Filter::isPresent(const Key &k) const {
    return filter.contains(k.getKey());
}


void Filter::clear() {
    filter.clear();
}

Filter::Filter() {
    parameters.projected_element_count = 1000;

    // Maximum tolerable false positive probability? (0,1)
    parameters.false_positive_probability = 0.0001; // 1 in 10000

    // Simple randomizer (optional)
    parameters.random_seed = 0xA5A5A5A5;

    parameters.compute_optimal_parameters();

    //Instantiate Bloom Filter
    bloom_filter filter1(parameters);
    filter = filter1;
}