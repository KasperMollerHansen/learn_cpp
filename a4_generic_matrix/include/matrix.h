#pragma once
#include <vector>
#include <utility>
#include <stdexcept>
#include <iostream>

// Template declaration
template<typename T>
class Matrix {
    std::vector<std::vector<T>> data;
    size_t rows, cols;

public:
    // 1. Default construction
    Matrix(size_t r, size_t c);
    ~Matrix() = default;

    // 2. Copy and move constructors and assignment operators
    Matrix(const Matrix& other) = default;
    Matrix(Matrix&& other) noexcept = default;
    Matrix& operator=(const Matrix& other) = default;
    Matrix& operator=(Matrix&& other) noexcept = default;

    // 3. Subscripting operator
    T& operator()(size_t x, size_t y);
    const T& operator()(size_t x, size_t y) const;

    // 4. Arithmetic operators
    Matrix operator+(const Matrix& other) const requires requires (T a, T b) { a + b; };
    Matrix operator-(const Matrix& other) const requires requires (T a, T b) { a - b; };
    Matrix operator*(const Matrix& other) const requires requires (T a, T b) { a * b; };
    Matrix operator/(const Matrix& other) const requires requires (T a, T b) { a / b; };
    Matrix operator%(const Matrix& other) const requires requires (T a, T b) { a % b; };

    // 5. Move elements within the matrix
    void Move(std::pair<size_t, size_t> src, std::pair<size_t, size_t> dst);

    // 6. Get a row or column as a vector
    std::vector<T> Row(size_t n) const;
    std::vector<T> Column(size_t n) const;


    // Utility functions
    void Print() const;
};

// Include implementation
#include "matrix.tpp"