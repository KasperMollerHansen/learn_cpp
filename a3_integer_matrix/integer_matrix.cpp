#include <vector>
#include <iostream>
#include <stdexcept>
#include <functional>

size_t a = 3;
size_t b = 3;

class Imatrix {
    std::vector<std::vector<int>> data;
    size_t rows, cols;

public:
    // 1. Default construction: all elements gets the default value 0.
    Imatrix(size_t r, size_t c) : data(r, std::vector<int>(c, 0)), rows(r), cols(c) {
        if (r == 0 || c == 0)
            throw std::invalid_argument("Imatrix: size must be greater than 0");
    }
    // 2. Assignment operator (=) and copy and move constructors.
    // These should be inherited from std::vector, but let's define them anyway.
    Imatrix(const Imatrix& other) : data(other.data), rows(other.rows), cols(other.cols) {} // Copy constructor
    Imatrix(Imatrix&& other) noexcept : data(std::move(other.data)), rows(other.rows), cols(other.cols) {
        other.rows = 0; // Reset the moved-from object
        other.cols = 0;
    } // Move constructor
    Imatrix& operator=(const Imatrix& other) {
        if (this != &other) {
            data = other.data;
            rows = other.rows;
            cols = other.cols;
        }
        return *this;
    } // Copy assignment operator

    Imatrix& operator=(Imatrix&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
            rows = other.rows;
            cols = other.cols;
            other.rows = 0; // Reset the moved-from object
            other.cols = 0;
        }
        return *this;
    } // Move assignment operator

    // 3. Subscripting: m(x,y) is the x, y element.
    int& operator()(size_t x, size_t y) {
        if (x >= rows || y >= cols)
            throw std::out_of_range("Imatrix: index out of range");
        return data[x][y];
    }

    // 4. +, *, /, -, and %, yielding a new Imatrix.
    Imatrix operator+(const Imatrix& other) const {
        if (rows != other.rows || cols != other.cols)
            throw std::invalid_argument("Imatrix: dimensions must match for addition");
        Imatrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    Imatrix operator-(const Imatrix& other) const {
        if (rows != other.rows || cols != other.cols)
            throw std::invalid_argument("Imatrix: dimensions must match for subtraction");
        Imatrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    Imatrix operator*(const Imatrix& other) const {
        if (cols != other.rows)
            throw std::invalid_argument("Imatrix: dimensions must match for multiplication");
        Imatrix result(rows, other.cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < other.cols; ++j) {
                result.data[i][j] = 0;
                for (size_t k = 0; k < cols; ++k) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    Imatrix operator/(const Imatrix& other) const {
        if (rows != other.rows || cols != other.cols)
            throw std::invalid_argument("Imatrix: dimensions must match for division");
        Imatrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                if (other.data[i][j] == 0)
                    throw std::runtime_error("Imatrix: division by zero");
                result.data[i][j] = data[i][j] / other.data[i][j];
            }
        }
        return result;
    }

    Imatrix operator%(const Imatrix& other) const {
        if (rows != other.rows || cols != other.cols)
            throw std::invalid_argument("Imatrix: dimensions must match for modulo");
        Imatrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                if (other.data[i][j] == 0)
                    throw std::runtime_error("Imatrix: modulo by zero");
                result.data[i][j] = data[i][j] % other.data[i][j];
            }
        }
        return result;
    }

    // 5. Move(x,y): place the value from location x to location y and set x to 0.
    void Move(std::pair<size_t, size_t> src, std::pair<size_t, size_t> dst) {
        size_t x1 = src.first, y1 = src.second;
        size_t x2 = dst.first, y2 = dst.second;
        if (x1 >= rows || y1 >= cols || x2 >= rows || y2 >= cols)
            throw std::out_of_range("Imatrix: index out of range for Move");
        data[x2][y2] = data[x1][y1];
        data[x1][y1] = 0;
    }

    // 6. Row(n): return a vector<int> with the values from the nth row.
    std::vector<int> Row(size_t n) const {
        if (n >= rows)
            throw std::out_of_range("Imatrix: row index out of range");
        return data[n];
    }

    // 7. Column(n): return a vector<int> with the values from the nth column.
    std::vector<int> Column(size_t n) const {
        if (n >= cols)
            throw std::out_of_range("Imatrix: column index out of range");
        std::vector<int> col_data;
        for (size_t i = 0; i < rows; ++i) {
            col_data.push_back(data[i][n]);
        }
        return col_data;
    }

    // Print function to display the matrix
    void Print() const {
        if (rows == 0 || cols == 0 || data.empty()) {
            std::cout << "[Empty matrix]\n";
            return;
        }
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                std::cout << data[i][j] << " ";
            }
            std::cout << "\n";
        }
    }

    // Function to fill the matrix with random values between 0 and input value
    // This function is not part of the original requirements but is useful for testing.
    void FillRandom(int max_value) {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                data[i][j] = rand() % (max_value + 1);
            }
        }
    }
};

void PrintMatrixOp(const Imatrix& m1, const Imatrix& m2, 
                const std::function<Imatrix(const Imatrix&, const Imatrix&)>& op,
                const std::string& op_name) {
    try {
        Imatrix result = op(m1, m2);
        std::cout << "Result of m1 " << op_name << " m2:\n";
        result.Print();
    } catch (const std::exception& e) {
        std::cout << "Error in " << op_name << ": " << e.what() << "\n";
    }
}
void PrintVector(const std::vector<int>& vec, const std::string& label) {
    std::cout << label << ": ";
    for (int val : vec) {
        std::cout << val << " ";
    }
    std::cout << "\n";
}


int main() {
    // 1. Construct will all 0:
    std::cout << "1. Constructing matrix with all zeros\n"; 
    try {
        Imatrix m0(0, 0); // This should throw an exception
    } catch (const std::invalid_argument& e) {
        std::cout << "Exception caught: " << e.what() << "\n";
    }

    Imatrix m1(a, b); // Create matrix
    m1.Print();
    std::cout << "Matrix created with " << a << " rows and " << b << " columns.\n";

    // 2. Test assignment operator and copy/move constructors
    std::cout << "\n2. Testing copy and move constructors and assignment operator.\n";
    Imatrix m2 = m1; // Copy constructor
    Imatrix m3 = std::move(m1); // Move constructor
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
    m1 = Imatrix(a, b);
    m1.FillRandom(10); // Fill m1 with random values
    m2 = Imatrix(a, b);
    m2.FillRandom(10); // Fill m2 with random values
    // Print the matrices before operations
    std::cout << "\n4. Testing arithmetic operations.\n";
    std::cout << "Matrix m1:\n";
    m1.Print();
    std::cout << "Matrix m2:\n";
    m2.Print();

    PrintMatrixOp(m1, m2, [](const Imatrix& x, const Imatrix& y){ return x + y; }, "+");
    PrintMatrixOp(m1, m2, [](const Imatrix& x, const Imatrix& y){ return x - y; }, "-");
    PrintMatrixOp(m1, m2, [](const Imatrix& x, const Imatrix& y){ return x * y; }, "*");
    PrintMatrixOp(m1, m2, [](const Imatrix& x, const Imatrix& y){ return x / y; }, "/");
    PrintMatrixOp(m1, m2, [](const Imatrix& x, const Imatrix& y){ return x % y; }, "%");

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
    return 0;
}