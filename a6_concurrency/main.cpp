#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <functional>
#include "include/find_all.hpp"

int main() {
    const std::size_t N = 10'000'000;
    std::vector<int> data(N);
    std::mt19937 rng(42);
    std::uniform_int_distribution<int> dist(0, 100);

    for (auto& x : data) x = dist(rng);

    auto pred = [](int x) { return x == 42; };

    // Serial
    auto t1 = std::chrono::high_resolution_clock::now();
    auto res1 = find_all<int, std::function<bool(int&)>>(data, pred);
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Serial found: " << res1.size()
              << " in " << std::chrono::duration<double>(t2-t1).count() << "s\n";

    // Parallel
    std::size_t num_threads = 10;
    auto t3 = std::chrono::high_resolution_clock::now();
    auto res2 = parallel_find_all<int, std::function<bool(int&)>>(data, pred, num_threads);
    auto t4 = std::chrono::high_resolution_clock::now();
    std::cout << "Parallel (" << num_threads << " threads) found: " << res2.size()
              << " in " << std::chrono::duration<double>(t4-t3).count() << "s\n";

    return 0;
}