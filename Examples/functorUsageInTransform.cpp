//inclue stl algorith
#include <algorithm>
//inclue stl vector
#include <functional>
#include <vector>
//inclue stl iostream
#include <iostream>



int main(){
    std::vector<int> v = {1, 2, 3, 4, 5};
    int toAdd = 10;
    // increment functor

    std::plus<int> add;

    add(toAdd, 5);

    // transform the vector




}