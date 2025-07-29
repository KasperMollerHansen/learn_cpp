#include <iostream>
#include <charconv> // C++17
#include <chrono>
#include <ctime>

int main() {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm* tm_ptr = std::localtime(&t);
    int year = tm_ptr->tm_year + 1900; // tm_year is years since 1900 :O

    constexpr size_t buffer_size = 5;
    char buffer[buffer_size];
    auto result = std::to_chars(buffer, buffer + buffer_size, year);
    if (result.ec == std::errc()) {
        std::cout << "Hello, World!\n";
        std::cout << "This is the year " << std::string(buffer, result.ptr) << "\n";
    } else {
        std::cout << "Conversion failed\n";
    }
}