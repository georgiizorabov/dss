#include "bloom_filter.hpp"
#include <iostream>
#include "kvs.h"
#include "Filter.h"


Filter::Filter(const std::vector<Key> &vec) {
    parameters.projected_element_count = 1000;

    // Maximum tolerable false positive probability? (0,1)
    parameters.false_positive_probability = 0.0001; // 1 in 10000

    // Simple randomizer (optional)
    parameters.random_seed = 0xA5A5A5A5;

    parameters.compute_optimal_parameters();

    //Instantiate Bloom Filter
    bloom_filter filter1(parameters);
    filter = filter1;
    // Insert into Bloom Filter
    {
        // Insert some keys
        for (const auto &i: vec) {
            filter.insert(i);
        }

    }
}

void Filter::addElement(const Key &k) {
    filter.insert(k);
}

bool Filter::isPresent(const Key &k) const {
    std::cout << filter.contains(k) << ' ' << k.getKey();
    return filter.contains(k);
}

void Filter::removeElement() {
//        filter.
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

