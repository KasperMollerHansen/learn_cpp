#include <cstdlib>
#include "matrix.h"

// 1. Default construction: all elements gets the default value 0.
template<typename T>
Matrix<T>::Matrix(size_t r, size_t c) : data(r, std::vector<T>(c, T{})), rows(r), cols(c) {
    if (r == 0 || c == 0)
        throw std::invalid_argument("Matrix: size must be greater than 0");
}

// 3. Subscripting: m(x,y) is the x, y element. Assignable.
template<typename T>
T& Matrix<T>::operator()(size_t x, size_t y) {
    if (x >= rows || y >= cols)
        throw std::out_of_range("Matrix: index out of range");
    return data[x][y];
}
template<typename T>
const T& Matrix<T>::operator()(size_t x, size_t y) const {
    if (x >= rows || y >= cols)
        throw std::out_of_range("Matrix: index out of range");
    return data[x][y];
}

// 4. Arithmetic operators
template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix& other) const requires (Arithmetic<T> || Addable<T>) {
    if (rows != other.rows || cols != other.cols)
        throw std::invalid_argument("Matrix: dimensions must match for addition");
    Matrix result(rows, cols);
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            result.data[i][j] = data[i][j] + other.data[i][j];
    return result;
}
template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix& other) const requires Arithmetic<T> {
    if (rows != other.rows || cols != other.cols)
        throw std::invalid_argument("Matrix: dimensions must match for subtraction");
    Matrix result(rows, cols);
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            result.data[i][j] = data[i][j] - other.data[i][j];
    return result;
}
template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix& other) const requires Arithmetic<T> {
    if (cols != other.rows)
        throw std::invalid_argument("Matrix: dimensions must match for multiplication");
    Matrix result(rows, other.cols);
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < other.cols; ++j)
            for (size_t k = 0; k < cols; ++k)
                result.data[i][j] += data[i][k] * other.data[k][j];
    return result;
}
template<typename T>
Matrix<T> Matrix<T>::operator/(const Matrix& other) const requires Arithmetic<T> {
    if (rows != other.rows || cols != other.cols)
        throw std::invalid_argument("Matrix: dimensions must match for division");
    Matrix result(rows, cols);
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j) {
            if (other.data[i][j] == 0)
                throw std::invalid_argument("Matrix: division by zero");
            result.data[i][j] = data[i][j] / other.data[i][j];
        }
    return result;
}
template<typename T>
Matrix<T> Matrix<T>::operator%(const Matrix& other) const requires Arithmetic<T> {
    if (rows != other.rows || cols != other.cols)
        throw std::invalid_argument("Matrix: dimensions must match for modulo");
    Matrix result(rows, cols);
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j) {
            if (other.data[i][j] == 0)
                throw std::invalid_argument("Matrix: modulo by zero");
            result.data[i][j] = data[i][j] % other.data[i][j];
        }
    return result;
}

// 5. Move elements within the matrix
template<typename T>
void Matrix<T>::Move(std::pair<size_t, size_t> src, std::pair<size_t, size_t> dst) {
    if (src.first >= rows || src.second >= cols ||
        dst.first >= rows || dst.second >= cols)
        throw std::out_of_range("Matrix: index out of range for Move operation");
    data[dst.first][dst.second] = data[src.first][src.second];
    data[src.first][src.second] = T{}; // Assuming T has a default constructor
}

// 6. Get a row or column as a vector
template<typename T>
std::vector<T> Matrix<T>::Row(size_t n) const {
    if (n >= rows)
        throw std::out_of_range("Matrix: row index out of range");
    return data[n];
}
template<typename T>
std::vector<T> Matrix<T>::Column(size_t n) const {
    if (n >= cols)
        throw std::out_of_range("Matrix: column index out of range");
    std::vector<T> column(rows);
    for (size_t i = 0; i < rows; ++i)
        column[i] = data[i][n];
    return column;
}

// Utility function to print the matrix
template<typename T>
void Matrix<T>::Print() const {
    for (const auto& row : data) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << "\n";
    }
}