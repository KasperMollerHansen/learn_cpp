module;
#include <chrono>
#include <iostream>
#include <string>

export module measurement_utils;

using Clock = std::chrono::high_resolution_clock;

export std::string format_with_dots(size_t n) noexcept {
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

export template<typename Container, typename ValueOrPredicate>
void run_find_case(
    Container& v,
    size_t idx,
    const std::string& name_found,
    const std::string& name_not_found,
    ValueOrPredicate finder,
    typename Container::value_type found_value = {}
) {
    // Store the original value
    const auto original_value = v[idx];

    // Case: value matches in the middle
    v[idx] = found_value;

    benchmark(name_found, [&] {
        auto it = finder(v.begin(), v.end());
        if (it != v.end())
            std::cout << "Found at index " << format_with_dots(std::distance(v.begin(), it)) << "\n";
        else
            std::cout << "Not found\n";
    });

    // Reset to original value
    v[idx] = original_value;

    // Case: value does not match
    benchmark(name_not_found, [&] {
        auto it = finder(v.begin(), v.end());
        if (it != v.end())
            std::cout << "Found at index " << format_with_dots(std::distance(v.begin(), it)) << "\n";
        else
            std::cout << "Not found\n";
    });
}