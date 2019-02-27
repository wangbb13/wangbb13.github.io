// shuffle a vector
// C++ version: C++ 11
#pragma once

#include <vector>
// #include <random> uniform_int_distribution has no randomness
#include <cstdlib>
#include <ctime>

namespace algds {
    template<typename T>
    void shuffle(std::vector<T>& vec) {
        // std::default_random_engine generator;
        // std::uniform_int_distribution<int> distribution;
        srand(time(NULL));
        int a = 0, b = vec.size() - 1, rv;
        T temp;
        while (a < b) {
            // distribution = std::uniform_int_distribution<int>(a, b);
            // rv = distribution(generator);
            rv = a + rand() % (b - a + 1);
            temp = vec[a];
            vec[a] = vec[rv];
            vec[rv] = temp;
            a++;
        }
    }
}