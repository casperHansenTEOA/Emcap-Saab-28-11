
// Vänd håll på ett ord utan reverse-funktionen

// use a stack to reverse a string
#include <iostream>
#include <stack>
#include <string>

// std::string reverseString(std::string s) {
//     std::stack<char> st;
//     for (char c : s) {
//         st.push(c);
//     }
//     std::string res;
//     while (!st.empty()) {
//         res += st.top();
//         st.pop();
//     }
//     return res;
// }


//Skriv en quicksort

// #include <iostream>
// #include <vector>
// #include <algorithm>

// void qs(std::vector<int>::iterator first, std::vector<int>::iterator last) {
//     if (first == last) return;
//     auto pivot = *std::next(first, std::distance(first, last) / 2); // väljer ett pivotelement i mitten
//     auto split = std::partition(first, last, [pivot](const int& em) { return em < pivot; }); //splittar arrayen baserat på pivot
//     auto pivotPos = std::partition(first, split, [pivot](const int& em) { return em == pivot; });
//     qs(first, pivotPos); // recursion 
//     qs(split, last);
// }




// Givet en lista, implementera en algoritms samt använd en datastruktur för att hitta en given summa av par i listan.
//Exempel: [1,2,3,4,5], sum = 7 => (3,4)
#include <vector>
#include <unordered_map>
using namespace std;
// brute force approach
// class Solution {
// public:
//     vector<int> twoSum(vector<int>& nums, int target) {
//     for (int i = 0; i < nums.size(); i++) {
//         for (int j = i + 1; j < nums.size(); j++) {
//             if (nums[i] + nums[j] == target) {
//                 return {i, j};
//             }
//         }
//     }
//     return {};
//   }
// };
// This approach optimizes the Two-Pass Hash Table Approach by only making one iteration through the array. During the iteration, we add each element’s index to a hash map and check if the complement already exists in the hash map.
// class Solution {
// public:
//   vector<int> twoSum(vector<int>& nums, int target) {
//     unordered_map<int, int> numMap;
//     for (int i = 0; i < nums.size(); i++) {
//         int complement = target - nums[i];
//         if (numMap.count(complement)) {
//             return {numMap[complement], i};
//         }
//         numMap[nums[i]] = i;
//     }
//     return {};
//   }
// };


// Givet ett antal staplar med bredd 1 i ett stapeldiagram mur många enheter vatten kan lagras mellan splana på ett sätt så att vattnet inte rinnerut (det är normal gravitation)

// //brute force 
// #include <iostream>
// #include <vector>
// using namespace std;

// int maxWater(vector<int> &arr) { 
  
//     int left = 1;
//     int right = arr.size() - 2;

//     // lMax : Maximum in subarray arr[0..left-1]
//     // rMax : Maximum in subarray arr[right+1..n-1]
//     int lMax = arr[left - 1];
//     int rMax = arr[right + 1];

//     int res = 0;
//     while (left <= right) {
      
//         // If rMax is smaller, then we can decide the amount of water for arr[right]
//         if (rMax <= lMax) {
          
//             // Add the water for arr[right]
//             res += max(0, rMax - arr[right]);

//             // Update right max
//             rMax = max(rMax, arr[right]);

//             // Update right pointer as we have decided the amount of water for this
//             right -= 1;
//         } else { 
//             // Add the water for arr[left]
//             res += max(0, lMax - arr[left]);

//             // Update left max
//             lMax = max(lMax, arr[left]);

//             // Update left pointer as we have decided water for this
//             left += 1;
//         }
//     }
//     return res;
// }

// // Driver code
// int main() {
//     vector<int> arr = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
//     cout << maxWater(arr) << endl;
//     return 0;
// }

// // Lösning med stack
// #include <iostream>
// #include <vector>
// #include <stack>
// using namespace std;

// // Function to return the maximum water that can be stored
// int maxWater(vector<int>& arr) {

//     stack<int> st;  
//     int res = 0;
//     for (int i = 0; i < arr.size(); i++) {
       
//         // Pop all items smaller than arr[i]
//         while (!st.empty() && arr[st.top()] < arr[i]) {          
            
//             int pop_height = arr[st.top()];
//             st.pop();
          
//             if (st.empty())
//                 break;

//             // arr[i] is the next greater for the removed item
//             // and new stack top is the previous greater 
//             int distance = i - st.top() - 1;
          
//             // Take the minimum of two heights (next and prev greater)
//             // and find the amount of water that we can fill in all
//             // bars between the two
//             int water = min(arr[st.top()], arr[i]) - pop_height;

            
//             res += distance * water;
//         }
//         st.push(i);
//     }
//     return res;
// }

// // Driver code
// int main() {

//     vector<int> arr = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
//     cout << maxWater(arr);
//     return 0;
// }

#include <iostream>
#include <iterator>
#include <functional>
#include <numeric>
#include <limits>
#include <queue>
#include <set>
#include <map>
#include <list>
#include <deque>
#include <array>
#include <bitset>
#include <forward_list>
#include <tuple>
#include <random>
#include <chrono>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <memory>
#include <type_traits>
#include <utility>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <stack>


// use a stack for something cool

// class Solution {
// public:
//     int longestValidParentheses(string s) {
//         stack<int> st;
//         st.push(-1);
//         int res = 0;
//         for (int i = 0; i < s.size(); i++) {
//             if (s[i] == '(') {
//                 st.push(i);
//             } else {
//                 st.pop();
//                 if (st.empty()) {
//                     st.push(i);
//                 } else {
//                     res = max(res, i - st.top());
//                 }
//             }
//         }
//         return res;
//     }



std::array<int, 4> a = {1, 2, 3, 4};


std::vector<int> v = {1, 2, 3, 4};


std::deque<int> d = {1, 2, 3, 4};


std::list<int> l = {1, 2, 3, 4};


std::forward_list<int> f = {1, 2, 3, 4};









std::array<int, 4> * b = new std::array<int, 4> {1, 2, 3, 4};


std::vector<int> * w = new std::vector<int> {1, 2, 3, 4};


std::deque<int> * e = new std::deque<int> {1, 2, 3, 4};


std::list<int> * m = new std::list<int> {1, 2, 3, 4};


std::forward_list<int> * g = new std::forward_list<int> {1, 2, 3, 4};