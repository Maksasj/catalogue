#ifndef _BENCHMARK_H_
#define _BENCHMARK_H_

#include <functional>
#include <string>
#include <chrono>
#include <iostream>
#include <random>
#include <algorithm>

#include "catalogue.h"

template<typename _T>
void fill_with_random_values(std::vector<_T>& container, const unsigned long long& testSampleDataSize) {
    using namespace std;

    for(int i = 0; i < testSampleDataSize; ++i)
        container.push_back(i);

    auto rng = default_random_engine {};
    shuffle(begin(container), end(container), rng);
}

void measure_operation(const std::string& operationName, const std::function<void(void)>& lambda, const std::string& offset = "") {
    using namespace std;
    using namespace chrono;

    steady_clock::time_point begin = steady_clock::now();

    lambda();

    steady_clock::time_point end = steady_clock::now();
    cout << offset << operationName << " took: " << duration_cast<nanoseconds> (end - begin).count() * 0.000001 << "[ms]\n";
}

#endif
