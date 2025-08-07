#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <functional>
#include <fstream>
#include <filesystem>
#include "include/find_all.hpp"

void small_demo_test() {
    std::vector<int> data{1,2,3,4,5,6,7,8,9,10};

    auto pred_eq5 = [](int x) { return x == 5; };
    auto pred_gt5 = [](int x) { return x > 5; };

    std::cout << "Small test: find 5\n";
    auto [res1, t1] = find_all<int, std::function<bool(int&)>>(data, pred_eq5);

    std::cout << "find_all: ";
    for (auto* p : res1) std::cout << *p << " ";
    std::cout << "(time: " << t1 << " ms)\n";

    auto [res2, t2] = parallel_find_all<int, std::function<bool(int&)>>(data, pred_eq5, 2);
    std::cout << "parallel_find_all: ";
    for (auto* p : res2) std::cout << *p << " ";
    std::cout << "(time: " << t2 << " ms)\n";

    auto [res3, t3] = parallel_find_all_ready<int, std::function<bool(int&)>>(data, pred_eq5, 2);
    std::cout << "parallel_find_all_ready: ";
    for (auto* p : res3) std::cout << *p << " ";
    std::cout << "(time: " << t3 << " ms)\n";

    std::cout << "\nSmall test: find >5\n";
    auto [res4, t4] = find_all<int, std::function<bool(int&)>>(data, pred_gt5);
    std::cout << "find_all: ";
    for (auto* p : res4) std::cout << *p << " ";
    std::cout << "(time: " << t4 << " ms)\n";

    auto [res5, t5] = parallel_find_all<int, std::function<bool(int&)>>(data, pred_gt5, 2);
    std::cout << "parallel_find_all: ";
    for (auto* p : res5) std::cout << *p << " ";
    std::cout << "(time: " << t5 << " ms)\n";

    auto [res6, t6] = parallel_find_all_ready<int, std::function<bool(int&)>>(data, pred_gt5, 2);
    std::cout << "parallel_find_all_ready: ";
    for (auto* p : res6) std::cout << *p << " ";
    std::cout << "(time: " << t6 << " ms)\n\n";
}

void run_serial_vs_parallel_benchmarks(const std::string& csv_path, std::size_t num_threads) {
    std::ofstream csv(csv_path);
    csv << "N,serial,parallel,parallel_ready\n";

    std::vector<std::size_t> sizes = {
        10'000, 100'000, 1'000'000, 10'000'000, 100'000'000, 1'000'000'000
    };
    std::vector<unsigned int> seeds = {42, 43, 44, 45, 46};

    for (auto N : sizes) {
        double serial_sum = 0, parallel_sum = 0, parallel_ready_sum = 0;

        for (auto seed : seeds) {
            std::mt19937 rng(seed);
            std::uniform_int_distribution<int> dist(0, 100);

            std::vector<int> data(N);
            for (auto& x : data) x = dist(rng);
            int int_target = 42;
            auto pred_int = [int_target](int x) { return x == int_target; };

            // Serial
            auto [res1, serial] = find_all<int, std::function<bool(int&)>>(data, pred_int);
            serial_sum += serial;

            // Parallel (with thread creation)
            auto [res2, parallel] = parallel_find_all<int, std::function<bool(int&)>>(data, pred_int, num_threads);
            parallel_sum += parallel;

            // Parallel (excluding thread creation)
            auto [res3, parallel_ready] = parallel_find_all_ready<int, std::function<bool(int&)>>(data, pred_int, num_threads);
            parallel_ready_sum += parallel_ready;
        }

        double serial_mean = serial_sum / seeds.size();
        double parallel_mean = parallel_sum / seeds.size();
        double parallel_ready_mean = parallel_ready_sum / seeds.size();

        std::cout << "N=" << N << " done.\n";
        csv << N << "," << serial_mean << "," << parallel_mean << "," << parallel_ready_mean << "\n";
    }

    csv.close();
    std::cout << "Results written to " << csv_path << "\n";

}

void run_thread_scaling_benchmarks(const std::string& csv_path, std::size_t N) {
    std::ofstream csv(csv_path);
    csv << "threads,parallel,parallel_ready\n";

    std::vector<unsigned int> seeds = {42, 43, 44, 45, 46};

    for (std::size_t num_threads = 2; num_threads <= 128; num_threads *= 2) { //Should be a power of 2 to ensure even distribution
        double parallel_sum = 0, parallel_ready_sum = 0;

        for (auto seed : seeds) {
            std::mt19937 rng(seed);
            std::uniform_int_distribution<int> dist(0, 100);

            std::vector<int> data(N);
            for (auto& x : data) x = dist(rng);
            int int_target = 42;
            auto pred_int = [int_target](int x) { return x == int_target; };

            // Parallel (with thread creation)
            auto [res2, parallel] = parallel_find_all<int, std::function<bool(int&)>>(data, pred_int, num_threads);
            parallel_sum += parallel;

            // Parallel (excluding thread creation)
            auto [res3, parallel_ready] = parallel_find_all_ready<int, std::function<bool(int&)>>(data, pred_int, num_threads);
            parallel_ready_sum += parallel_ready;
        }

        double parallel_mean = parallel_sum / seeds.size();
        double parallel_ready_mean = parallel_ready_sum / seeds.size();

        std::cout << "Threads=" << num_threads << " done.\n";
        csv << num_threads << "," << parallel_mean << "," << parallel_ready_mean << "\n";
    }

    csv.close();
    std::cout << "Thread scaling results written to " << csv_path << "\n";
}



int main() {
    std::cout << "Running small demo test...\n";
    small_demo_test();

    std::filesystem::create_directories("../output_data");
    run_serial_vs_parallel_benchmarks("../output_data/results_serial_vs_parallel.csv", 10);
    run_thread_scaling_benchmarks("../output_data/results_thread_scaling_small.csv", 1'000'000);
    run_thread_scaling_benchmarks("../output_data/results_thread_scaling_large.csv", 1'000'000'000);

    return 0;
}