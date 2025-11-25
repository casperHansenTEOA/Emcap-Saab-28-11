// example for cimbining operations in views
#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>

int main() {
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Create a view that filters even numbers and then squares them
    auto evenSquaresView = data 
        | std::views::filter([](int x) { return x % 2 == 0; }) 
        | std::views::transform([](int x) { return x * x; });

    // Output the results
    std::cout << "Even squares: ";
    for (int value : evenSquaresView) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    // Calculate the sum of the even squares
    int sum = std::accumulate(evenSquaresView.begin(), evenSquaresView.end(), 0);
    std::cout << "Sum of even squares: " << sum << std::endl;

    return 0;
}
