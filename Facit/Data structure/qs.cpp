#include <iostream>
#include <stack>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
//Skriv en quicksort
void qs(std::vector<int>::iterator first, std::vector<int>::iterator last) {
    if (first == last) return;
    auto pivot = *std::next(first, std::distance(first, last) / 2); // väljer ett pivotelement i mitten
    auto split = std::partition(first, last, [pivot](const int& em) { return em < pivot; }); //splittar arrayen baserat på pivot
    auto pivotPos = std::partition(first, split, [pivot](const int& em) { return em == pivot; });
    qs(first, pivotPos); // recursion 
    qs(split, last);
}

// test code
int main() {
    std::vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    qs(v.begin(), v.end());
    for (int i : v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
}