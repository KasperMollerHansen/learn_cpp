#pragma once
#include <vector>
#include <utility>
#include <stdexcept>
#include <iostream>

class Imatrix {
    std::vector<std::vector<int>> data;
    size_t rows, cols;

public:
    Imatrix(size_t r, size_t c);

     // Since we use std::vector, we can use the default copy and move constructors and assignment operators.
    // Imatrix(const Imatrix& other);
    // Imatrix(Imatrix&& other) noexcept;
    // Imatrix& operator=(const Imatrix& other);
    // Imatrix& operator=(Imatrix&& other) noexcept;

    int& operator()(size_t x, size_t y);

    Imatrix operator+(const Imatrix& other) const;
    Imatrix operator-(const Imatrix& other) const;
    Imatrix operator*(const Imatrix& other) const;
    Imatrix operator/(const Imatrix& other) const;
    Imatrix operator%(const Imatrix& other) const;

    void Move(std::pair<size_t, size_t> src, std::pair<size_t, size_t> dst);
    std::vector<int> Row(size_t n) const;
    std::vector<int> Column(size_t n) const;
    void Print() const;
    void FillRandom(int max_value);
};