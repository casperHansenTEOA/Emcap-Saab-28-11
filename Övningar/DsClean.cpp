// Clean file with stubs and a simple driver

#include <iostream>
#include <vector>
#include <algorithm>

// Quicksort (stub)
void quicksort(std::vector<int>& a, int lo, int hi) {
    // Implementation removed — stub does nothing
    (void)a; (void)lo; (void)hi;
}

// Two-sum (stub)
std::vector<int> twoSum(const std::vector<int>& nums, int target) {
    // Implementation removed — return empty result
    (void)nums; (void)target;
    return {};
}

// Max trapped water (stub)
int maxWater(const std::vector<int>& arr) {
    // Implementation removed — return zero
    (void)arr;
    return 0;
}

int main() {
    // Driver for quicksort (calls stub)
    std::vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    quicksort(v, 0, static_cast<int>(v.size()) - 1);
    std::cout << "Quicksort result (stub): ";
    for (int x : v) std::cout << x << ' ';
    std::cout << '\n';

    // Driver for twoSum (calls stub)
    std::vector<int> nums = {1, 2, 3, 4, 5};
    int target = 7;
    auto res = twoSum(nums, target);
    std::cout << "twoSum indices for target " << target << " (stub): ";
    if (!res.empty()) std::cout << res[0] << ' ' << res[1];
    else std::cout << "none";
    std::cout << '\n';

    // Driver for maxWater (calls stub)
    std::vector<int> heights = {0,1,0,2,1,0,1,3,2,1,2,1};
    std::cout << "Max trapped water (stub): " << maxWater(heights) << '\n';

    return 0;
}
