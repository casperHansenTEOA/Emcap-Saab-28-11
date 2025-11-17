
#include <concepts>
template<typename T>
concept Addable = requires(T a, T b) {
    { a + b } -> std::convertible_to<T>;
};

#include <iostream>
template<Addable T>
T add(T a, T b) {
    return a + b;
}

int main() {
    std::cout << add(3, 7) << std::endl;      // Call add for int
    std::cout << add(3.0, 7.0) << std::endl; // Call add for double
    std::cout << add('g', 'e') << std::endl;   // Call add for char

    return 0;
}

