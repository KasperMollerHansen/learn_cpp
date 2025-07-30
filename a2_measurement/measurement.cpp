import measurement_utils;
#include <random>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

template<typename Container, typename ValueOrPredicate>
void run_find_case(Container& v, size_t idx, const std::string& name_found, const std::string& name_not_found, ValueOrPredicate finder, bool is_predicate = false, typename Container::value_type found_value = {}) {
    // Case: value/predicate matches in the middle
    if (!is_predicate) v[idx] = found_value;
    else v[idx] = found_value; // For predicate, set value that matches predicate

    benchmark(name_found, [&] {
        auto it = finder(v.begin(), v.end());
        if (it != v.end())
            std::cout << "Found at index " << std::distance(v.begin(), it) << "\n";
        else
            std::cout << "Not found\n";
    });
    v[idx] = 42; // Reset

    // Case: value/predicate does not match
    benchmark(name_not_found, [&] {
        auto it = finder(v.begin(), v.end());
        if (it != v.end())
            std::cout << "Found at index " << std::distance(v.begin(), it) << "\n";
        else
            std::cout << "Not found\n";
    });
}

int main() {
    const size_t N = 1'000'000'000; // Very large vector for performance testing
    const size_t N_small = 1'000'000; // Smaller vector for quick tests
    std::cout << "Running benchmarks with N = " << format_with_dots(N) << "\n";
    std::cout << "Running small benchmarks with N_small = " << format_with_dots(N_small) << "\n";
    std::vector<int> vi(N, 42); // Initialize with all 42
    std::vector<int> vi_small(N_small, 42); // Smaller vector for quick tests

    // --- std::find on vector<int>
    // Case 1 & 2: Find 7 in the middle
    run_find_case(vi, N/2, "std::find int (found middle)", "std::find int (not found)",
        [](auto begin, auto end) { return std::find(begin, end, 7); }, false, 7);
    run_find_case(vi_small, N_small/2, "std::find int (found middle small)", "std::find int (not found small)",
        [](auto begin, auto end) { return std::find(begin, end, 7); }, false, 7);

    // --- std::find_if on vector<int>
    // Case 3 & 4: Find x < 7 in middle
    run_find_case(vi, N/2, "std::find_if int (found middle)", "std::find_if int (not found)",
        [](auto begin, auto end) { return std::find_if(begin, end, [](int x){ return x < 7; }); }, true, 5);
    run_find_case(vi_small, N_small/2, "std::find_if int (found middle small)", "std::find_if int (not found small)",
        [](auto begin, auto end) { return std::find_if(begin, end, [](int x){ return x < 7; }); }, true, 5);

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