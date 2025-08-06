#include "find_all.hpp"
#include <thread>

template<typename T, typename Pred>
std::vector<T*> find_all(std::vector<T>& vec, Pred pred) {
    std::vector<T*> result;
    for (auto& elem : vec) {
        if (pred(elem)) result.push_back(&elem);
    }
    return result;
}

template<typename T, typename Pred>
void find_all_worker(std::vector<T>& vec, std::size_t start, std::size_t end, Pred pred, std::vector<T*>& out) {
    for (std::size_t i = start; i < end; ++i) {
        if (pred(vec[i])) out.push_back(&vec[i]);
    }
}

template<typename T, typename Pred>
std::vector<T*> parallel_find_all(std::vector<T>& vec, Pred pred, std::size_t num_threads) {
    std::vector<std::vector<T*>> results(num_threads);
    std::vector<std::thread> threads;
    std::size_t chunk = vec.size() / num_threads;
    std::size_t rem = vec.size() % num_threads;

    std::size_t start = 0;
    for (std::size_t t = 0; t < num_threads; ++t) {
        std::size_t end = start + chunk + (t < rem ? 1 : 0);
        threads.emplace_back(find_all_worker<T, Pred>, std::ref(vec), start, end, pred, std::ref(results[t]));
        start = end;
    }
    for (auto& th : threads) th.join();

    std::vector<T*> combined;
    for (auto& part : results) combined.insert(combined.end(), part.begin(), part.end());
    return combined;
}

// Explicit instantiations for int and std::function<bool(int&)>
template std::vector<int*> find_all<int, std::function<bool(int&)>>(std::vector<int>&, std::function<bool(int&)>);
template std::vector<int*> parallel_find_all<int, std::function<bool(int&)>>(std::vector<int>&, std::function<bool(int&)>, std::size_t);