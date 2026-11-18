#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>
#include <ranges>
#include <numeric>

// Exercise 1: quicksort using STL algorithms.
void quicksort(std::vector<int>::iterator begin,
               std::vector<int>::iterator end)
{
    if (std::distance(begin, end) <= 1)
    {
        return;
    }

    auto pivotIt = std::next(begin, std::distance(begin, end) / 2);
    const int pivotValue = *pivotIt;

    // Move pivot outside the range being partitioned.
    std::iter_swap(pivotIt, end - 1);

    // One partition: values less than pivot go to the left.
    auto pivotPosition = std::partition(
        begin,
        end - 1,
        [pivotValue](int value)
        {
            return value < pivotValue;
        });

    // Put the pivot between the two partitions.
    std::iter_swap(pivotPosition, end - 1);

    quicksort(begin, pivotPosition);
    quicksort(std::next(pivotPosition), end);
}
// Exercise 2: return the indexes of the first pair whose sum is target.
std::vector<int> two_sum(const std::vector<int> &values, int target)
{
    return {};
}

// Exercise 3: calculate trapped water with a monotonic stack of indexes.
int trapped_water(const std::vector<int> &heights)
{
    return 0;
}

void test_quicksort()
{
    std::vector<int> values{3, 1, 4, 1, 5, 9, 2, 6, 5};
    quicksort(values.begin(), values.end());
    assert(std::is_sorted(values.begin(), values.end()));

    std::vector<int> empty;
    quicksort(empty.begin(), empty.end());
    assert(empty.empty());
}

void test_two_sum()
{
    assert(two_sum({1, 2, 3, 4, 5}, 7) == std::vector<int>({2, 3}));
    assert(two_sum({3, 3}, 6) == std::vector<int>({0, 1}));
    assert(two_sum({1, 2, 3}, 99).empty());
}

void test_trapped_water()
{
    assert(trapped_water({0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}) == 6);
    assert(trapped_water({3, 2, 1}) == 0);
    assert(trapped_water({}) == 0);
}

int main()
{
    test_quicksort();
    test_two_sum();
    test_trapped_water();
    std::cout << "All tests passed.\n";
}
