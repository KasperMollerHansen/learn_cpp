#pragma once
#include <vector>
#include <list>
#include <set>
#include <tuple>


void test_vector_insert_remove(int N, unsigned int seed);
void test_list_insert_remove(int N, unsigned int seed);
void test_set_insert_remove(int N, unsigned int seed);

std::tuple<double, double> vector_insert_remove(int N, unsigned int seed);
std::tuple<double, double> list_insert_remove(int N, unsigned int seed);
std::tuple<double, double> set_insert_remove(int N, unsigned int seed);