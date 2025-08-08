https://leetcode.com/problems/two-sum/description/

// Leetcode 1: Two Sum
// ✅ Find indices of two numbers in an array that add up to a specific target
// Assumes exactly one solution exists and the same element cannot be used twice

// Solution 1: Brute-force approach (O(n^2) time)
class Solution {
public:
    // Function returns indices of two elements whose sum equals target
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();

        // Check every pair (i, j) with j > i to avoid using same element twice and duplicates
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (nums[i] + nums[j] == target) {
                    return {i, j};  // Return immediately after finding the pair
                }
            }
        }

        return {};  // If no pair found (problem guarantees solution, so not expected)
    }
};

/*
Why This Works:
----------------
- Checks all possible pairs of numbers.
- Returns as soon as a valid pair summing to target is found.
- Straightforward and easy to understand.

When To Use:
-------------
- When input size is small.
- When simplicity is more important than performance.
- For learning or brute-force baseline.

Time Complexity: O(n^2)      // Nested loops scanning all pairs
Space Complexity: O(1)       // No extra space used
*/


// Solution 2: Using Map (Hash Map) for faster lookup - O(n) time
#include <map>  // or use unordered_map for faster average lookup

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        map<int,int> mpp;  // Map from number to its index seen so far

        for (int i = 0; i < nums.size(); i++) {
            int more = target - nums[i];  // Number needed to form target sum with nums[i]

            // Check if more has been seen before in map
            if (mpp.find(more) != mpp.end()) {
                return {mpp[more], i};  // Return indices immediately
            }

            // Record current number and its index for future mores
            mpp[nums[i]] = i;
        }

        return {};  // No pair found (not expected)
    }
};

/*
Why This Works:
----------------
- Uses map to store numbers and their indices seen so far.
- For each element nums[i], checks if more (target - nums[i]) exists in map.
- Efficiently finds the required pair in a single pass.

When To Use:
-------------
- When input size is large and performance matters.
- When fast lookup needed for more values.
- Recommended approach for coding interviews and production-level code.

Time Complexity: O(n log n)
  - Using std::map which has O(log n) insertion and search.
  - Can be improved to O(n) by using unordered_map (hash table).

Space Complexity: O(n)       // For the map storing numbers and their indices
*/

