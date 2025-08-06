https://leetcode.com/problems/rotate-array/description/


// Leetcode 189: Rotate Array
// ✅ In-place rotation of array to the right by k steps using reverse

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k = k % n;  // Handle cases where k >= n

        // Step 1: Reverse the entire array
        reverse(nums.begin(), nums.end());

        // Step 2: Reverse the first k elements
        reverse(nums.begin(), nums.begin() + k);

        // Step 3: Reverse the remaining elements
        reverse(nums.begin() + k, nums.end());
    }
};

/*
Why This Works:
----------------
- We can rotate the array in-place by reversing the entire array first.
- Then, we reverse the first k elements (which are now the ones we want at the front).
- Finally, we reverse the rest of the array to restore the correct order.

Example:
Input: nums = [1, 2, 3, 4, 5, 6, 7], k = 3
Step 1: Reverse whole array → [7, 6, 5, 4, 3, 2, 1]
Step 2: Reverse first k → [5, 6, 7, 4, 3, 2, 1]
Step 3: Reverse rest → [5, 6, 7, 1, 2, 3, 4]

When To Use:
-------------
- You want to rotate elements **in-place** with O(1) extra space
- You need **fast performance** with large arrays
- A brute force shifting method would be too slow for big `k`

Time Complexity: O(n)      // 3 reverse operations, each O(n)
Space Complexity: O(1)     // In-place modification
*/