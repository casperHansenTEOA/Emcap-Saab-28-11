
#include <iostream>

// simple recursive constexpr function
constexpr int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

// constexpr value
constexpr int pi = 3;

int main() {
    // Using constexpr function
    constexpr int fact5 = factorial(pi);
    std::cout << "Factorial of " << pi << " is: " << fact5 << std::endl;
}