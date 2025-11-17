template <typename T> T myMax(T x, T y)
{
    return (x > y) ? x : y;
}

#include <iostream>
int main() {
    std::cout << myMax<int>(3, 7) << std::endl;      // Call myMax for int
    std::cout << myMax<double>(3.0, 7.0) << std::endl; // Call myMax for double
    std::cout << myMax<char>('g', 'e') << std::endl;   // Call myMax for char

    return 0;
}