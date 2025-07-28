#include <iostream>
#include <charconv> // C++17

int main() {
    const int year = 2025;
    constexpr size_t buffer_size = 5; // 4 digits + null terminator (extra space is safe)
    char buffer[buffer_size];
    auto result = std::to_chars(buffer, buffer + buffer_size, year);
    if (result.ec == std::errc()) {
        std::cout << "Hello, World!\n";
        std::cout << "This is the year " << std::string(buffer, result.ptr) << "\n";
    } else {
        std::cout << "Conversion failed\n";
    }
}