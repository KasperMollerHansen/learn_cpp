#include <utils.h>
#include <fstream>

#include <iostream>

template<typename Func>
void benchmark_insert_remove(
    const std::vector<int>& N_list,
    const std::vector<unsigned int>& seed_list,
    Func insert_remove_func,
    const std::string& filename)
{
    std::ofstream out(filename);
    out << "N,seed,insert_time_ms,remove_time_ms\n";
    for (unsigned int seed : seed_list) {
        for (int N : N_list) {
            auto [insert_time, remove_time] = insert_remove_func(N, seed);
            out << N << "," << seed << "," << insert_time << "," << remove_time << "\n";
        }
    }
    out.close();
}




int main()
{
    // Testing of each contatiner's insert and remove functions
    int N = 5;
    unsigned int seed = 42;

    std::cout << "Testing vector insert/remove:" << std::endl;
    test_vector_insert_remove(N, seed);
    std::cout << "Testing list insert/remove:" << std::endl;
    test_list_insert_remove(N, seed);
    std::cout << "Testing set insert/remove:" << std::endl;
    test_set_insert_remove(N, seed);

    std::cout << "All tests completed." << std::endl;

    // Benchmarking
    std::cout << "Starting benchmarks..." << std::endl;
    std::vector<int> N_list = {100'000, 500'000, 1'000'000};
    std::vector<unsigned int> seed_list = {42, 43, 44};

    std::cout << "Benchmarking vector insert/remove..." << std::endl;
    benchmark_insert_remove(N_list, seed_list, vector_insert_remove, "vector_benchmark.csv");
    std::cout << "Benchmarking list insert/remove..." << std::endl;
    benchmark_insert_remove(N_list, seed_list, list_insert_remove, "list_benchmark.csv");
    std::cout << "Benchmarking set insert/remove..." << std::endl;
    benchmark_insert_remove(N_list, seed_list, set_insert_remove, "set_benchmark.csv");

    return 0;

}