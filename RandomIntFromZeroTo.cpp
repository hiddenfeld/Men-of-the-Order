#pragma once
#include <random>
#include <functional>
#include <chrono>

// This method returns a random int between zero and the transferred int.
// Both zero and the transferred int are included in the range of possible results
// Example randomIntFromZeroTo(5) returns a random one of these: { 0, 1, 2, 3, 4, 5 }
inline int randomIntFromZeroTo(unsigned int i) {
    auto seed{std::chrono::high_resolution_clock::now().time_since_epoch().count()};
    return std::bind(std::uniform_int_distribution<int>(0, (int)i), std::mt19937((unsigned int)seed))();
};
