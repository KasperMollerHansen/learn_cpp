#include <vector>
#include <random>
#include <algorithm>
#include <iostream>
#include <list>
#include <set>
#include <tuple>
#include <chrono>


// Generates a vector of numbers [0, N-1] in random order using the given seed
std::vector<int> _generate_random_numbers_for_insertion(int N, unsigned int seed) {
    std::vector<int> numbers(N);
    for (int i = 0; i < N; ++i) {
        numbers[i] = i;
    }
    std::mt19937 rng(seed);
    std::shuffle(numbers.begin(), numbers.end(), rng);
    return numbers;
}

// Generates a vector of random indices for deletion
std::vector<int> _generate_random_deletion_indices(int N, unsigned int seed) {
    std::vector<int> indices;
    std::mt19937 rng(seed);
    for (int size = N; size > 0; --size) {
        std::uniform_int_distribution<int> dist(0, size - 1);
        indices.push_back(dist(rng));
    }
    return indices;
}

// Nice feature, that the compiler chose the best suited print function, based on type of input!
template<typename Container>
void _print(const Container& container) {
    for (const auto& elem : container) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

// --- INSERT FUNCTIONS ---

template<typename SequenceContainer>
SequenceContainer _insert_numbers_sorted(const std::vector<int>& numbers_to_insert, bool print_each_step) {
    SequenceContainer result;
    for (int num : numbers_to_insert) {
        auto it = result.begin();
        while (it != result.end() && *it < num) {
            ++it;
        }
        result.insert(it, num);
        if (print_each_step) _print(result);
    }
    return result;
}

std::set<int> _insert_numbers_sorted_set(const std::vector<int>& numbers_to_insert, bool print_each_step) {
    std::set<int> result;
    for (int num : numbers_to_insert) {
        result.insert(num); // std::set keeps sorted order
        if (print_each_step) _print(result);
    }
    return result;
}

// --- REMOVE FUNCTION ---
template<typename Container>
void _remove_from_container(Container& container, const std::vector<int>& removal_indices, bool print_each_step = false) {
    for (int idx : removal_indices) {
        if (!container.empty() && idx < container.size()) {
            auto it = container.begin();
            for (int i = 0; i < idx; ++i) ++it;
            container.erase(it);
        }
        if (print_each_step) _print(container);
    }
}

// --- TEST FUNCTIONS ---

void test_vector_insert_remove(int N, unsigned int seed) {
    // Generate random numbers and indices
    std::vector<int> numbers = _generate_random_numbers_for_insertion(N, seed);
    std::vector<int> removal_indices = _generate_random_deletion_indices(N, seed);

    std::cout << "Random numbers for insertion: ";
    _print(numbers);

    std::cout << "Random indices for removal: ";
    _print(removal_indices);

    // Insert numbers in sorted order
    std::vector<int> vec = _insert_numbers_sorted<std::vector<int>>(numbers, true);

    std::cout << "Vector after all insertions: ";
    _print(vec);

    // Remove elements using removal_indices
    _remove_from_container(vec, removal_indices, true);

    std::cout << "Vector after all removals: ";
    _print(vec);
}

void test_list_insert_remove(int N, unsigned int seed) {
    // Generate random numbers and indices
    std::vector<int> numbers = _generate_random_numbers_for_insertion(N, seed);
    std::vector<int> removal_indices = _generate_random_deletion_indices(N, seed);

    std::cout << "Random numbers for insertion: ";
    _print(numbers);

    std::cout << "Random indices for removal: ";
    _print(removal_indices);

    // Insert numbers in sorted order
    std::list<int> lst = _insert_numbers_sorted<std::list<int>>(numbers, true);

    std::cout << "List after all insertions: ";
    _print(lst);

    // Remove elements using removal_indices
    _remove_from_container(lst, removal_indices, true);

    std::cout << "List after all removals: ";
    _print(lst);
}

void test_set_insert_remove(int N, unsigned int seed) {
    // Generate random numbers and indices
    std::vector<int> numbers = _generate_random_numbers_for_insertion(N, seed);
    std::vector<int> removal_indices = _generate_random_deletion_indices(N, seed);

    std::cout << "Random numbers for insertion: ";
    _print(numbers);

    std::cout << "Random indices for removal: ";
    _print(removal_indices);

    // Insert numbers in set (order doesn't matter, set is always sorted)
    std::set<int> s = _insert_numbers_sorted_set(numbers, true);

    std::cout << "Set after all insertions: ";
    _print(s);

    // Remove elements using removal_indices
    _remove_from_container(s, removal_indices, true);

    std::cout << "Set after all removals: ";
    _print(s);
}

// --- REAL FUNCTIONS ---

std::tuple<double, double> vector_insert_remove(int N, unsigned int seed) {
    std::vector<int> numbers = _generate_random_numbers_for_insertion(N, seed);
    std::vector<int> removal_indices = _generate_random_deletion_indices(N, seed);

    auto start_insert = std::chrono::high_resolution_clock::now();
    std::vector<int> vec = _insert_numbers_sorted<std::vector<int>>(numbers, false);
    auto end_insert = std::chrono::high_resolution_clock::now();

    double insert_time = std::chrono::duration<double, std::milli>(end_insert - start_insert).count();

    auto start_remove = std::chrono::high_resolution_clock::now();
    _remove_from_container(vec, removal_indices, false);
    auto end_remove = std::chrono::high_resolution_clock::now();

    double remove_time = std::chrono::duration<double, std::milli>(end_remove - start_remove).count();

    return {insert_time, remove_time};
}

std::tuple<double, double> list_insert_remove(int N, unsigned int seed) {
    std::vector<int> numbers = _generate_random_numbers_for_insertion(N, seed);
    std::vector<int> removal_indices = _generate_random_deletion_indices(N, seed);

    auto start_insert = std::chrono::high_resolution_clock::now();
    std::list<int> lst = _insert_numbers_sorted<std::list<int>>(numbers, false);
    auto end_insert = std::chrono::high_resolution_clock::now();

    double insert_time = std::chrono::duration<double, std::milli>(end_insert - start_insert).count();

    auto start_remove = std::chrono::high_resolution_clock::now();
    _remove_from_container(lst, removal_indices, false);
    auto end_remove = std::chrono::high_resolution_clock::now();

    double remove_time = std::chrono::duration<double, std::milli>(end_remove - start_remove).count();

    return {insert_time, remove_time};
}

std::tuple<double, double> set_insert_remove(int N, unsigned int seed) {
    std::vector<int> numbers = _generate_random_numbers_for_insertion(N, seed);
    std::vector<int> removal_indices = _generate_random_deletion_indices(N, seed);

    auto start_insert = std::chrono::high_resolution_clock::now();
    std::set<int> s = _insert_numbers_sorted_set(numbers, false);
    auto end_insert = std::chrono::high_resolution_clock::now();

    double insert_time = std::chrono::duration<double, std::milli>(end_insert - start_insert).count();

    auto start_remove = std::chrono::high_resolution_clock::now();
    _remove_from_container(s, removal_indices, false);
    auto end_remove = std::chrono::high_resolution_clock::now();

    double remove_time = std::chrono::duration<double, std::milli>(end_remove - start_remove).count();

    return {insert_time, remove_time};
}