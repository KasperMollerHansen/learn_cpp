#pragma once
#include <vector>
#include <utility>
#include <stdexcept>
#include <iostream>

class Matrix {
    std::vector<std::vector<int>> data;
    size_t rows, cols;

public:
    Matrix(size_t r, size_t c);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other) noexcept;
    Matrix& operator=(const Matrix& other);
    Matrix& operator=(Matrix&& other) noexcept;

    int& operator()(size_t x, size_t y);

    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator/(const Matrix& other) const;
    Matrix operator%(const Matrix& other) const;

    void Move(std::pair<size_t, size_t> src, std::pair<size_t, size_t> dst);
    std::vector<int> Row(size_t n) const;
    std::vector<int> Column(size_t n) const;
    void Print() const;
    void FillRandom(int max_value);
};