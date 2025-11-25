
#include <vector>
#include <iostream>
#include <ranges>
#include <algorithm>
#include <functional>
int main(){

    std::vector<int> vec = {10, 20, 30, 40, 50};

    // originally one would sort like this
    std::sort(vec.begin(), vec.end(), std::greater<int>());
    //and sort reversely but omitting the last 5 elements like this
    std::sort(vec.rbegin() + 5, vec.rend(), std::greater<int>());


    // with ranges one can do it like this
    std::ranges::sort(vec);
    // and 
    std::ranges::sort(std::views::drop(std::views::reverse(vec), 5));

    return 0;
}

