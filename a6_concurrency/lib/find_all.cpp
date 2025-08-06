#include "find_all.hpp"
#include <thread>
#include <future>
#include <chrono>
#include <utility>

// Serial
template<typename T, typename Pred>
std::pair<std::vector<T*>, double> find_all(std::vector<T>& vec, Pred pred) {
    auto t1 = std::chrono::high_resolution_clock::now();
    std::vector<T*> result;
    for (auto& elem : vec) {
        if (pred(elem)) result.push_back(&elem);
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    double elapsed = std::chrono::duration<double>(t2-t1).count();
    return {result, elapsed};
}

// Parallel
template<typename T, typename Pred>
void _find_all_worker(std::vector<T>& vec, std::size_t start, std::size_t end, Pred pred, std::vector<T*>& out) {
    for (std::size_t i = start; i < end; ++i) {
        if (pred(vec[i])) out.push_back(&vec[i]);
    }
}

template<typename T, typename Pred>
std::pair<std::vector<T*>, double> parallel_find_all(std::vector<T>& vec, Pred pred, std::size_t num_threads) {
    std::vector<std::vector<T*>> results(num_threads);
    std::vector<std::thread> threads;
    std::size_t chunk = vec.size() / num_threads;
    std::size_t rem = vec.size() % num_threads;

    auto t1 = std::chrono::high_resolution_clock::now();
    std::size_t start = 0;
    for (std::size_t t = 0; t < num_threads; ++t) {
        std::size_t end = start + chunk + (t < rem ? 1 : 0);
        threads.emplace_back(_find_all_worker<T, Pred>, std::ref(vec), start, end, pred, std::ref(results[t]));
        start = end;
    }
    for (auto& th : threads) th.join();
    auto t2 = std::chrono::high_resolution_clock::now();

    std::vector<T*> combined;
    for (auto& part : results) combined.insert(combined.end(), part.begin(), part.end());
    double elapsed = std::chrono::duration<double>(t2-t1).count();
    return {combined, elapsed};
}

// Parallel ready
template<typename T, typename Pred>
void _worker_ready(std::vector<T>& vec, std::size_t start, std::size_t end, Pred pred, std::vector<T*>& out, std::shared_future<void> ready) {
    ready.wait();
    for (std::size_t i = start; i < end; ++i) {
        if (pred(vec[i])) out.push_back(&vec[i]);
    }
}

template<typename T, typename Pred>
std::pair<std::vector<T*>, double> parallel_find_all_ready(std::vector<T>& vec, Pred pred, std::size_t num_threads) {
    std::vector<std::vector<T*>> results(num_threads);
    std::vector<std::thread> threads;
    std::promise<void> go;
    std::shared_future<void> ready(go.get_future());

    std::size_t chunk = vec.size() / num_threads;
    std::size_t rem = vec.size() % num_threads;
    std::size_t start = 0;
    for (std::size_t t = 0; t < num_threads; ++t) {
        std::size_t end = start + chunk + (t < rem ? 1 : 0);
        threads.emplace_back(_worker_ready<T, Pred>, std::ref(vec), start, end, pred, std::ref(results[t]), ready);
        start = end;
    }

    auto t1 = std::chrono::high_resolution_clock::now();
    go.set_value();
    for (auto& th : threads) th.join();
    auto t2 = std::chrono::high_resolution_clock::now();

    std::vector<T*> combined;
    for (auto& part : results) combined.insert(combined.end(), part.begin(), part.end());
    double elapsed = std::chrono::duration<double>(t2-t1).count();
    return {combined, elapsed};
}

// Explicit instantiations for int and char
template std::pair<std::vector<int*>, double> find_all<int, std::function<bool(int&)>>(std::vector<int>&, std::function<bool(int&)>);
template std::pair<std::vector<int*>, double> parallel_find_all<int, std::function<bool(int&)>>(std::vector<int>&, std::function<bool(int&)>, std::size_t);
template std::pair<std::vector<int*>, double> parallel_find_all_ready<int, std::function<bool(int&)>>(std::vector<int>&, std::function<bool(int&)>, std::size_t);
template std::pair<std::vector<char*>, double> find_all<char, std::function<bool(char&)>>(std::vector<char>&, std::function<bool(char&)>);
template std::pair<std::vector<char*>, double> parallel_find_all<char, std::function<bool(char&)>>(std::vector<char>&, std::function<bool(char&)>, std::size_t);
template std::pair<std::vector<char*>, double> parallel_find_all_ready<char, std::function<bool(char&)>>(std::vector<char>&, std::function<bool(char&)>, std::size_t);