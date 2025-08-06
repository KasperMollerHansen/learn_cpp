#pragma once
#include <vector>
#include <cstddef>
#include <functional>
#include <future>
#include <utility>

template<typename T, typename Pred>
std::pair<std::vector<T*>, double> find_all(std::vector<T>& vec, Pred pred);

template<typename T, typename Pred>
std::pair<std::vector<T*>, double> parallel_find_all(std::vector<T>& vec, Pred pred, std::size_t num_threads);

template<typename T, typename Pred>
std::pair<std::vector<T*>, double> parallel_find_all_ready(std::vector<T>& vec, Pred pred, std::size_t num_threads);