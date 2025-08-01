#include "matrix.h"
#include <cstdlib>

// 1. Default construction: all elements gets the default value 0.
Matrix::Matrix(size_t r, size_t c) : data(r, std::vector<int>(c, 0)), rows(r), cols(c) {
    if (r == 0 || c == 0)
        throw std::invalid_argument("Matrix: size must be greater than 0");
}

// 2. Copy constructor
Matrix::Matrix(const Matrix& other) : data(other.data), rows(other.rows), cols(other.cols) {}

// 2. Move constructor
Matrix::Matrix(Matrix&& other) noexcept : data(std::move(other.data)), rows(other.rows), cols(other.cols) {
    other.rows = 0;
    other.cols = 0;
}

// 2. Assignment operator (=)
Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        data = other.data;
        rows = other.rows;
        cols = other.cols;
    }
    return *this;
}

// 2. Move assignment operator
Matrix& Matrix::operator=(Matrix&& other) noexcept {
    if (this != &other) {
        data = std::move(other.data);
        rows = other.rows;
        cols = other.cols;
        other.rows = 0;
        other.cols = 0;
    }
    return *this;
}

// 3. Subscripting: m(x,y) is the x, y element. Assignable.
int& Matrix::operator()(size_t x, size_t y) {
    if (x >= rows || y >= cols)
        throw std::out_of_range("Matrix: index out of range");
    return data[x][y];
}

// 4. +, -, *, /, %, yielding a new Matrix.
Matrix Matrix::operator+(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols)
        throw std::invalid_argument("Matrix: dimensions must match for addition");
    Matrix result(rows, cols);
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            result.data[i][j] = data[i][j] + other.data[i][j];
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols)
        throw std::invalid_argument("Matrix: dimensions must match for subtraction");
    Matrix result(rows, cols);
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            result.data[i][j] = data[i][j] - other.data[i][j];
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (cols != other.rows)
        throw std::invalid_argument("Matrix: dimensions must match for multiplication");
    Matrix result(rows, other.cols);
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < other.cols; ++j)
            for (size_t k = 0; k < cols; ++k)
                result.data[i][j] += data[i][k] * other.data[k][j];
    return result;
}

Matrix Matrix::operator/(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols)
        throw std::invalid_argument("Matrix: dimensions must match for division");
    Matrix result(rows, cols);
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j) {
            if (other.data[i][j] == 0)
                throw std::runtime_error("Matrix: division by zero");
            result.data[i][j] = data[i][j] / other.data[i][j];
        }
    return result;
}

Matrix Matrix::operator%(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols)
        throw std::invalid_argument("Matrix: dimensions must match for modulo");
    Matrix result(rows, cols);
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j) {
            if (other.data[i][j] == 0)
                throw std::runtime_error("Matrix: modulo by zero");
            result.data[i][j] = data[i][j] % other.data[i][j];
        }
    return result;
}

// 5. Move(x,y): place the value from location x to location y and set x to 0.
void Matrix::Move(std::pair<size_t, size_t> src, std::pair<size_t, size_t> dst) {
    size_t x1 = src.first, y1 = src.second;
    size_t x2 = dst.first, y2 = dst.second;
    if (x1 >= rows || y1 >= cols || x2 >= rows || y2 >= cols)
        throw std::out_of_range("Matrix: index out of range for Move");
    data[x2][y2] = data[x1][y1];
    data[x1][y1] = 0;
}

// 6. Row(n): return a vector<int> with the values from the nth row.
std::vector<int> Matrix::Row(size_t n) const {
    if (n >= rows)
        throw std::out_of_range("Matrix: row index out of range");
    return data[n];
}

// 7. Column(n): return a vector<int> with the values from the nth column.
std::vector<int> Matrix::Column(size_t n) const {
    if (n >= cols)
        throw std::out_of_range("Matrix: column index out of range");
    std::vector<int> col_data;
    for (size_t i = 0; i < rows; ++i)
        col_data.push_back(data[i][n]);
    return col_data;
}

// Utility: Print the matrix
void Matrix::Print() const {
    if (rows == 0 || cols == 0 || data.empty()) {
        std::cout << "[Empty matrix]\n";
        return;
    }
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j)
            std::cout << data[i][j] << " ";
        std::cout << "\n";
    }
}

// Utility: Fill matrix with random values
void Matrix::FillRandom(int max_value) {
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            data[i][j] = rand() % (max_value + 1);
}