#include "matrix.h"
#include <iostream>
#include <string>

size_t a = 2;
size_t b = 2;

// Helper function to print a vector (row or column)
template<typename T>
void PrintVector(const std::vector<T>& vec, const std::string& label) {
    std::cout << label << ": ";
    for (const auto& val : vec) {
        std::cout << val << " ";
    }
    std::cout << "\n";
}

int main() {
    Matrix<int> m1(a, b);
    m1(0, 0) = 1;
    m1(0, 1) = 2;
    m1(1, 0) = 3;
    m1(1, 1) = 4;
    m1.Print();
    std::cout << "Matrix created with " << a << " rows and " << b << " columns.\n";

    Matrix<float> m2(a, b);
    m2(0, 0) = 1.1f;
    m2(0, 1) = 2.2f;
    m2(1, 0) = 3.3f;
    m2(1, 1) = 4.4f;
    m2.Print();
    std::cout << "Float matrix created with " << a << " rows and " << b << " columns.\n";

    Matrix<std::string> m3(a, b);
    m3(0, 0) = "hello";
    m3(0, 1) = "world";
    m3(1, 0) = "Year";
    m3(1, 1) = "2025";
    m3.Print();
    std::cout << "String matrix created with " << a << " rows and " << b << " columns.\n\n";

    // Edit the matrix
    m1(0, 0) = 5;
    std::cout << "After editing, the first element is: " << m1(0, 0) << "\n";
    std::cout << "Matrix after editing:\n";
    m1.Print();
    m2(0, 0) = 5.5f;
    std::cout << "After editing, the first element is: " << m2(0, 0) << "\n";
    std::cout << "Matrix after editing:\n";
    m2.Print();
    m3(0, 0) = "Goodbye";
    std::cout << "After editing, the first element is: " << m3(0, 0) << "\n";
    std::cout << "Matrix after editing:\n";
    m3.Print();
    // Test arithmetic operations
    auto m4 = m1 + m1;
    std::cout << "Result of adding two integer matrices:\n";
    m4.Print();
    auto m5 = m2 - m2;
    std::cout << "Result of subtracting two float matrices:\n";
    m5.Print();
    auto m6 = m1 * m1;
    std::cout << "Result of multiplying two integer matrices:\n";
    m6.Print();
    auto m7 = m2 / m2;
    std::cout << "Result of dividing two float matrices:\n";
    m7.Print();
    // Test string operations
    // Note: String addition is not defined, so this will not compile
    auto m8 = m3 + m3;
    std::cout << "Result of adding two string matrices:\n";
    m8.Print();
    // auto m9 = m3 - m3; // This crashes at compile time, since std::string does not support subtraction

    // Test move within the matrix
    std::cout << "Moving element from (0, 0) to (1, 1) in integer matrix:\n";
    m1.Move({0, 0}, {1, 1});
    m1.Print();
    std::cout << "Movingor arithmetic types element from (0, 0) to (1, 1) in float matrix:\n";
    m2.Move({0, 0}, {1, 1});
    m2.Print();
    std::cout << "Moving element from (0, 0) to (1, 1) in string matrix:\n";
    m3.Move({0, 0}, {1, 1});
    m3.Print();

    // Test row and column extraction
    std::cout << "Row 0 of integer matrix:\n";
    PrintVector(m1.Row(0), "Row 0");
    std::cout << "Column 1 of integer matrix:\n";
    PrintVector(m1.Column(1), "Column 1");
    std::cout << "Row 0 of float matrix:\n";
    PrintVector(m2.Row(0), "Row 0");
    std::cout << "Column 1 of float matrix:\n";
    PrintVector(m2.Column(1), "Column 1");
    std::cout << "Row 0 of string matrix:\n";
    PrintVector(m3.Row(0), "Row 0");
    std::cout << "Column 1 of string matrix:\n";
    PrintVector(m3.Column(1), "Column 1");  

    return 0;
}