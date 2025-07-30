module;
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

export module measurement_utils;

using Clock = std::chrono::high_resolution_clock;

export std::string format_with_dots(size_t n) {
    std::string s = std::to_string(n);
    std::string result;
    int count = 0;
    for (auto it = s.rbegin(); it != s.rend(); ++it) {
        if (count && count % 3 == 0)
            result.insert(0, 1, '.');
        result.insert(0, 1, *it);
        ++count;
    }
    return result;
}

export template<typename F>
void benchmark(const std::string& name, F&& f) {
    auto start = Clock::now();
    f();
    auto end = Clock::now();
    std::chrono::duration<double, std::milli> ms = end - start;
    std::cout << name << ": " << ms.count() << " ms\n";
}

