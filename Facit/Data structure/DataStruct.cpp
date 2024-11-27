
// Vänd håll på ett ord utan reverse-funktionen


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




// Givet en lista, implementera en algoritms samt använd en datastruktur för att hitta en given summa av par i listan.
//Exempel: [1,2,3,4,5], sum = 7 => (3,4)


// brute force approach (Långsam)
class SolutionBad {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
    for (int i = 0; i < nums.size(); i++) {
        for (int j = i + 1; j < nums.size(); j++) {
            if (nums[i] + nums[j] == target) {
                return {i, j};
            }
        }
    }
    return {};
  }
};


// This approach optimizes the Two-Pass Hash Table Approach by only making one iteration through the array. 
// During the iteration, we add each element’s index to a hash map and check if the complement already exists in the hash map.

  std::vector<int> twoSum(std::vector<int>& nums, int target) {
    std::unordered_map<int, int> numMap;

    for (int i = 0; i < nums.size(); i++) {
        int complement = target - nums[i];
        if (numMap.count(complement)) {
            return {numMap[complement], i};
        }
        numMap[nums[i]] = i;
    }
    return {};
  }


// driver test main 
int main() {

    std::vector<int> v = {1, 2, 3, 4, 5};
    std::vector<int> res = twoSum(v, 7);
    for (int i : res) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
}

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

// Function to return the maximum water that can be stored
int maxWater(std::vector<int>& arr) {

	std::stack<int> st;  // Stack to store the indices of bars
	int res = 0;    // Variable to store the maximum water

	for (int i = 0; i < arr.size(); i++) {
	   
		// Pop all items (bars) smaller than arr[i] from the stack
		while (!st.empty() && arr[st.top()] < arr[i]) {          
			int pop_height = arr[st.top()]; // Height of the bar being popped
			st.pop();
						
			if (st.empty()){
				break;
			}
			
			// arr[i] is the next greater bar for the removed item
			// and the new stack top is the previous greater bar
			int distance = i - st.top() - 1; // Distance between the two bars
			// Take the minimum of two heights (next and previous greater bars)
			// and find the amount of water that we can fill in all
			// bars between the two
			int water = std::min(arr[st.top()], arr[i]) - pop_height;
			res += distance * water; // Accumulate the water amount
		}
		st.push(i); // Push the current bar index to the stack
	}
	return res; // Return the maximum water amount
}

// Driver code
int main() {

    std::vector<int> arr = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    std::cout << maxWater(arr);
    return 0;
}

