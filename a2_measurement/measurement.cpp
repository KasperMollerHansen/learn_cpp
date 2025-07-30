#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <sstream>
#include <locale>

using Clock = std::chrono::high_resolution_clock;

std::string format_with_dots(size_t n) {
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

template<typename F>
void benchmark(const std::string& name, F&& f) {
    auto start = Clock::now();
    f();
    auto end = Clock::now();
    std::chrono::duration<double, std::milli> ms = end - start;
    std::cout << name << ": " << ms.count() << " ms\n";
}

int main() {
    const size_t N = 1'000'000'000; // Very large vector for performance testing
    const size_t N_small = 1'000'000; // Smaller vector for quick tests
    std::cout << "Running benchmarks with N = " << format_with_dots(N) << "\n";
    std::cout << "Running small benchmarks with N_small = " << format_with_dots(N_small) << "\n";
    std::vector<int> vi(N, 42); // Initialize with all 42
    std::vector<int> vi_small(N_small, 42); // Smaller vector for quick tests

    // --- std::find on vector<int>
    // Case 1: Find 7 in the middle
    auto run_find_middle = [](std::vector<int>& v, size_t idx, const std::string& name) {
        v[idx] = 7;
        benchmark(name, [&] {
            auto it = std::find(v.begin(), v.end(), 7);
        });
        v[idx] = 42; // Reset
    };
    run_find_middle(vi, N/2, "std::find int (found middle)");
    run_find_middle(vi_small, N_small/2, "std::find int (found middle small)");

    // Case 2: Find 7 not present
    benchmark("std::find int (not found)", [&] {
        auto it = std::find(vi.begin(), vi.end(), 7);
    });
    benchmark("std::find int (not found small)", [&] {
        auto it = std::find(vi_small.begin(), vi_small.end(), 7);
    });

    // --- std::find_if on vector<int>
    // Case 3: Find x < 7 in middle
    auto run_find_if_middle = [](std::vector<int>& v, size_t idx, const std::string& name) {
        v[idx] = 5;
        benchmark(name, [&] {
            auto it = std::find_if(v.begin(), v.end(), [](int x){ return x < 7; });
        });
        v[idx] = 42; // Reset
    };
    run_find_if_middle(vi, N/2, "std::find_if int (found middle)");
    run_find_if_middle(vi_small, N_small/2, "std::find_if int (found middle small)");

    // Case 4: Find x < 7 not present
    benchmark("std::find_if int (not found)", [&] {
        auto it = std::find_if(vi.begin(), vi.end(), [](int x){ return x < 7; });
    });
    benchmark("std::find_if int (not found small)", [&] {
        auto it = std::find_if(vi_small.begin(), vi_small.end(), [](int x){ return x < 7; });
    });

    // --- std::find on vector<string>
    const size_t Nstr = 1'000'000;
    std::vector<std::string> vs;
    vs.reserve(Nstr);

    std::mt19937 rng(12345);
    std::uniform_int_distribution<char> dist('A', 'Z');
    for (size_t i = 0; i < Nstr; ++i) {
        std::string s(20, 'X');
        for (auto& c : s) c = dist(rng);
        vs.push_back(std::move(s));
    }

    std::string needle(20, 'X');

    // Case 5: Try to find "XXXXXXXXXXXXXXXXXXXX" (most likely absent)
    benchmark("std::find string (not found)", [&] {
        auto it = std::find(vs.begin(), vs.end(), needle);
    });

    // Case 6: Place it in middle and find
    vs[Nstr/2] = needle;
    benchmark("std::find string (found middle)", [&] {
        auto it = std::find(vs.begin(), vs.end(), needle);
    });

    return 0;
}