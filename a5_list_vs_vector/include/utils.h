#pragma once
#include <vector>
#include <list>
#include <set>
#include <tuple>


// We could make a template for list and vector, but we keep them separate for clarity
void test_vector_insert_remove(int N, unsigned int seed);
void test_list_insert_remove(int N, unsigned int seed);
void test_set_insert_remove(int N, unsigned int seed);

std::tuple<double, double> vector_insert_remove(int N, unsigned int seed);
std::tuple<double, double> list_insert_remove(int N, unsigned int seed);
std::tuple<double, double> set_insert_remove(int N, unsigned int seed);

void test_vector_insert_remove_large(int N, unsigned int seed);
void test_list_insert_remove_large(int N, unsigned int seed);
void test_set_insert_remove_large(int N, unsigned int seed);

std::tuple<double, double> vector_insert_remove_large(int N, unsigned int seed);
std::tuple<double, double> list_insert_remove_large(int N, unsigned int seed);
std::tuple<double, double> set_insert_remove_large(int N, unsigned int seed);