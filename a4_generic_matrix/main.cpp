#include "matrix.h"
#include <iostream>
#include <functional>
#include <vector>
#include <cstdlib>

size_t a = 3;
size_t b = 3;

// Helper function to print a vector (row or column)
void PrintVector(const std::vector<int>& vec, const std::string& label) {
    std::cout << label << ": ";
    for (int val : vec) {
        std::cout << val << " ";
    }
    std::cout << "\n";
}

// Helper function to print results of matrix operations
void PrintMatrixOp(const Matrix& m1, const Matrix& m2, 
                   const std::function<Matrix(const Matrix&, const Matrix&)>& op,
                   const std::string& op_name) {
    try {
        Matrix result = op(m1, m2);
        std::cout << "Result of m1 " << op_name << " m2:\n";
        result.Print();
    } catch (const std::exception& e) {
        std::cout << "Error in " << op_name << ": " << e.what() << "\n";
    }
}

int main() {
    // a3 assignment -> needs to test that it will still work

    std::cout << "1. Constructing matrix with all zeros\n"; 
    try {
        Matrix m0(0, 0); // This should throw an exception
    } catch (const std::invalid_argument& e) {
        std::cout << "Exception caught: " << e.what() << "\n";
    }

    Matrix m1(a, b); // Create matrix
    m1.Print();
    std::cout << "Matrix created with " << a << " rows and " << b << " columns.\n";

    // 2. Test assignment operator and copy/move constructors
    std::cout << "\n2. Testing copy and move constructors and assignment operator.\n";
    Matrix m2 = m1; // Copy constructor
    Matrix m3 = std::move(m1); // Move constructor
    std::cout << "Copied matrix:\n";
    m2.Print();
    std::cout << "Moved matrix:\n";
    m3.Print();
    std::cout << "Original matrix (should be empty):\n";
    m1.Print();

    // 3. Test subscripting
    std::cout << "\n3. Testing subscripting operator.\n";
    m2(0, 0) = 10; // Set value at (0, 0)
    std::cout << "Value at (0, 0) after setting to 10:\n";
    std::cout << m2(0, 0) << "\n";
    std::cout << "Matrix after setting value:\n";
    m2.Print();
    try {
        std::cout << m2(10, 10) << "\n";
    } catch (const std::out_of_range& e) {
        std::cout << "Exception caught: " << e.what() << "\n";
    }

    // 4. Test arithmetic operations
    m1 = Matrix(a, b);
    m1.FillRandom(10); // Fill m1 with random values
    m2 = Matrix(a, b);
    m2.FillRandom(10); // Fill m2 with random values
    std::cout << "\n4. Testing arithmetic operations.\n";
    std::cout << "Matrix m1:\n";
    m1.Print();
    std::cout << "Matrix m2:\n";
    m2.Print();

    PrintMatrixOp(m1, m2, [](const Matrix& x, const Matrix& y){ return x + y; }, "+");
    PrintMatrixOp(m1, m2, [](const Matrix& x, const Matrix& y){ return x - y; }, "-");
    PrintMatrixOp(m1, m2, [](const Matrix& x, const Matrix& y){ return x * y; }, "*");
    PrintMatrixOp(m1, m2, [](const Matrix& x, const Matrix& y){ return x / y; }, "/");
    PrintMatrixOp(m1, m2, [](const Matrix& x, const Matrix& y){ return x % y; }, "%");

    // 5. Test Move operation
    std::cout << "\n5. Testing Move operation.\n";
    std::cout << "Matrix m1:\n";
    m1.Print();
    std::cout << "Moving value from (0, 0) to (1, 0).\n";
    m1.Move({0, 0}, {1, 0});
    std::cout << "Matrix m1 after move:\n";
    m1.Print();

    // 6 Test Row operation
    std::cout << "\n6. Testing Row operation.\n";
    PrintVector(m1.Row(1), "Row 1");

    // 7 Test Column operation
    std::cout << "\n7. Testing Column operation.\n";
    PrintVector(m1.Column(1), "Column 1");
    
    // New testcases for the generic matrix

    return 0;
}