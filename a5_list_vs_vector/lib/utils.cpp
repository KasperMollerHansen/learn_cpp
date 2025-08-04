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
void print(const std::vector<int>& vec) {
    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

void print(const std::list<int>& lst) {
    for (int num : lst) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

void print(const std::set<int>& s) {
    for (int num : s) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

std::vector<int> _insert_numbers_sorted_vector(const std::vector<int>& numbers_to_insert, bool print_each_step = false) {
    std::vector<int> result;
    for (int num : numbers_to_insert) {
        auto pos = std::lower_bound(result.begin(), result.end(), num);
        result.insert(pos, num);
        if (print_each_step) {
            print(result);
        }
    }
    return result;
}

std::list<int> _insert_numbers_sorted_list(const std::vector<int>& numbers_to_insert, bool print_each_step = false) {
    std::list<int> result;
    for (int num : numbers_to_insert) {
        auto pos = std::find_if(result.begin(), result.end(), [num](int x){ return x >= num; });
        result.insert(pos, num);
        if (print_each_step) {
            print(result);
        }
    }
    return result;
}

std::set<int> _insert_numbers_set(const std::vector<int>& numbers_to_insert, bool print_each_step = false) {
    std::set<int> result;
    for (int num : numbers_to_insert) {
        result.insert(num);
        if (print_each_step) {
            print(result);
        }
    }
    return result;
}

void _remove_from_vector(std::vector<int>& vec, const std::vector<int>& removal_indices, bool print_each_step = false) {
    for (int idx : removal_indices) {
        if (!vec.empty() && idx < vec.size()) {
            vec.erase(vec.begin() + idx);
        }
        if (print_each_step) {
            print(vec);
        }
    }
}

void _remove_from_list(std::list<int>& lst, const std::vector<int>& removal_indices, bool print_each_step = false) {
    for (int idx : removal_indices) {
        if (!lst.empty() && idx < lst.size()) {
            auto it = lst.begin();
            std::advance(it, idx);
            lst.erase(it);
        }
        if (print_each_step) {
            print(lst);
        }
    }
}

void _remove_from_set(std::set<int>& s, const std::vector<int>& removal_indices, bool print_each_step = false) {
    for (int idx : removal_indices) {
        if (!s.empty() && idx < s.size()) {
            auto it = s.begin();
            std::advance(it, idx);
            s.erase(it);
        }
        if (print_each_step) {
            print(s);
        }
    }
}

void test_vector_insert_remove(int N, unsigned int seed) {
    // Generate random numbers and indices
    std::vector<int> numbers = _generate_random_numbers_for_insertion(N, seed);
    std::vector<int> removal_indices = _generate_random_deletion_indices(N, seed);

    std::cout << "Random numbers for insertion: ";
    print(numbers);

    std::cout << "Random indices for removal: ";
    print(removal_indices);

    // Insert numbers in sorted order
    std::vector<int> vec = _insert_numbers_sorted_vector(numbers, true);

    std::cout << "Vector after all insertions: ";
    print(vec);

    // Remove elements using removal_indices
    _remove_from_vector(vec, removal_indices, true);

    std::cout << "Vector after all removals: ";
    print(vec);
}

void test_list_insert_remove(int N, unsigned int seed) {
    // Generate random numbers and indices
    std::vector<int> numbers = _generate_random_numbers_for_insertion(N, seed);
    std::vector<int> removal_indices = _generate_random_deletion_indices(N, seed);

    std::cout << "Random numbers for insertion: ";
    print(numbers);

    std::cout << "Random indices for removal: ";
    print(removal_indices);

    // Insert numbers in sorted order
    std::list<int> lst = _insert_numbers_sorted_list(numbers, true);

    std::cout << "List after all insertions: ";
    print(lst);

    // Remove elements using removal_indices
    _remove_from_list(lst, removal_indices, true);

    std::cout << "List after all removals: ";
    print(lst);
}

void test_set_insert_remove(int N, unsigned int seed) {
    // Generate random numbers and indices
    std::vector<int> numbers = _generate_random_numbers_for_insertion(N, seed);
    std::vector<int> removal_indices = _generate_random_deletion_indices(N, seed);

    std::cout << "Random numbers for insertion: ";
    print(numbers);

    std::cout << "Random indices for removal: ";
    print(removal_indices);

    // Insert numbers in set (order doesn't matter, set is always sorted)
    std::set<int> s = _insert_numbers_set(numbers, true);

    std::cout << "Set after all insertions: ";
    print(s);

    // Remove elements using removal_indices
    _remove_from_set(s, removal_indices, true);

    std::cout << "Set after all removals: ";
    print(s);
}
// --- Real functions start here ---

std::tuple<double, double> vector_insert_remove(int N, unsigned int seed) {
    std::vector<int> numbers = _generate_random_numbers_for_insertion(N, seed);
    std::vector<int> removal_indices = _generate_random_deletion_indices(N, seed);

    auto start_insert = std::chrono::high_resolution_clock::now();
    std::vector<int> vec = _insert_numbers_sorted_vector(numbers, false);
    auto end_insert = std::chrono::high_resolution_clock::now();

    double insert_time = std::chrono::duration<double, std::milli>(end_insert - start_insert).count();

    auto start_remove = std::chrono::high_resolution_clock::now();
    _remove_from_vector(vec, removal_indices, false);
    auto end_remove = std::chrono::high_resolution_clock::now();

    double remove_time = std::chrono::duration<double, std::milli>(end_remove - start_remove).count();

    return {insert_time, remove_time};
}

std::tuple<double, double> list_insert_remove(int N, unsigned int seed) {
    std::vector<int> numbers = _generate_random_numbers_for_insertion(N, seed);
    std::vector<int> removal_indices = _generate_random_deletion_indices(N, seed);

    auto start_insert = std::chrono::high_resolution_clock::now();
    std::list<int> lst = _insert_numbers_sorted_list(numbers, false);
    auto end_insert = std::chrono::high_resolution_clock::now();

    double insert_time = std::chrono::duration<double, std::milli>(end_insert - start_insert).count();

    auto start_remove = std::chrono::high_resolution_clock::now();
    _remove_from_list(lst, removal_indices, false);
    auto end_remove = std::chrono::high_resolution_clock::now();

    double remove_time = std::chrono::duration<double, std::milli>(end_remove - start_remove).count();

    return {insert_time, remove_time};
}

std::tuple<double, double> set_insert_remove(int N, unsigned int seed) {
    std::vector<int> numbers = _generate_random_numbers_for_insertion(N, seed);
    std::vector<int> removal_indices = _generate_random_deletion_indices(N, seed);

    auto start_insert = std::chrono::high_resolution_clock::now();
    std::set<int> s = _insert_numbers_set(numbers, false);
    auto end_insert = std::chrono::high_resolution_clock::now();

    double insert_time = std::chrono::duration<double, std::milli>(end_insert - start_insert).count();

    auto start_remove = std::chrono::high_resolution_clock::now();
    _remove_from_set(s, removal_indices, false);
    auto end_remove = std::chrono::high_resolution_clock::now();

    double remove_time = std::chrono::duration<double, std::milli>(end_remove - start_remove).count();

    return {insert_time, remove_time};
}