import measurement_utils;
#include <random>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

constexpr int kDefaultValue = 42;

int main() {
    const size_t N = 1'000'000'000; // Very large vector for performance testing
    const size_t N_small = 1'000'000; // Smaller vector for quick tests
    std::cout << "Running benchmarks with N = " << format_with_dots(N) << "\n";
    std::cout << "Running small benchmarks with N_small = " << format_with_dots(N_small) << "\n";
    
    // Initialize with all with kDefaultValue
    std::vector<int> vi(N, kDefaultValue);
    std::vector<int> vi_small(N_small, kDefaultValue); 

    // --- std::find on vector<int>
    // Case 1 & 2: Find 7 in the middle and not found
    std::cout << "\nRunning find benchmarks...\n";
    run_find_case(vi, N/2, "std::find int (found middle)", "std::find int (not found)",
        [](auto begin, auto end) { return std::find(begin, end, 7); }, 7);
    run_find_case(vi_small, N_small/2, "std::find int (found middle small)", "std::find int (not found small)",
        [](auto begin, auto end) { return std::find(begin, end, 7); }, 7);

    // --- std::find_if on vector<int>
    // Case 3 & 4: Find x < 7 in middle and not found
    std::cout << "\nRunning find_if benchmarks...\n";
    run_find_case(vi, N/2, "std::find_if int (found middle)", "std::find_if int (not found)",
        [](auto begin, auto end) { return std::find_if(begin, end, [](int x){ return x < 7; }); }, 5);

    run_find_case(vi_small, N_small/2, "std::find_if int (found middle small)", "std::find_if int (not found small)",
        [](auto begin, auto end) { return std::find_if(begin, end, [](int x){ return x < 7; }); }, 5);

    // --- std::find on vector<string>
    std::vector<std::string> vs;
    vs.reserve(N_small);

    std::mt19937 rng(12345);
    std::uniform_int_distribution<char> dist('A', 'Z');
    for (size_t i = 0; i < N_small; ++i) {
        std::string s(20, 'X');
        for (auto& c : s) c = dist(rng);
        vs.push_back(std::move(s));
    }

    std::string needle(20, 'X');

    // Case 5: Try to find "XXXXXXXXXXXXXXXXXXXX" (most likely absent)
    std::cout << "\nRunning find benchmarks on strings...\n";
    benchmark("std::find string (not found)", [&] {
        auto it = std::find(vs.begin(), vs.end(), needle);
    });

    // Case 6: Place it in middle and find
    vs[N_small/2] = needle;
    benchmark("std::find string (found middle)", [&] {
        auto it = std::find(vs.begin(), vs.end(), needle);
    });

    return 0;
}