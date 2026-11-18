#include <vector>
#include <numeric>
#include <iostream>
#include <cassert>

int main()
{
    std::vector<double> data = {10, 12, 15, 20, 18, 25};
    std::vector<double> diff(data.size());
    std::vector<double> reconstructed(data.size());

    // adjacent_difference: diff[0] = data[0], diff[i] = data[i] - data[i-1]
    std::adjacent_difference(data.begin(), data.end(), diff.begin());

    // partial_sum på diff ska ge tillbaka original
    std::partial_sum(diff.begin(), diff.end(), reconstructed.begin());

    // enkel kontroll
    assert(data == reconstructed);

    std::cout << "Differenser: ";
    for (double d : diff)
        std::cout << d << " ";
    std::cout << "\nOK, rekonstruerad sekvens matchar original.\n";
}