#pragma once
#include <vector>
#include <cstddef>
#include <functional>

template<typename T, typename Pred>
std::vector<T*> find_all(std::vector<T>& vec, Pred pred);

template<typename T, typename Pred>
std::vector<T*> parallel_find_all(std::vector<T>& vec, Pred pred, std::size_t num_threads);