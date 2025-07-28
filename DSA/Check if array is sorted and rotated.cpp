https://leetcode.com/problems/check-if-array-is-sorted-and-rotated/

// Leetcode 1752: Check if Array Is Sorted and Rotated
// ✅ Checks if a non-decreasing sorted array was rotated some number of times

class Solution {
public:
    bool check(vector<int>& nums) {
        int jump = 0;              // Count of places where order breaks (nums[i] > nums[i+1])
        int n = nums.size();

        for (int i = 0; i < n; i++) {
            // Use modulo to wrap around to the first element after the last
            if (nums[i] > nums[(i + 1) % n]) {
                jump++;
            }

            // If order breaks more than once, it can't be a rotated sorted array
            if (jump > 1) return false;
        }
        return true;
    }
};

/*
Why This Works:
----------------
- A sorted and rotated array will have **at most one place** where the order breaks
- Example: [3, 4, 5, 1, 2] → only one place where `5 > 1`
- We loop with modulo to compare last and first element as well
- If more than one such 'jump' is found, the array can't be sorted-rotated

When To Use:
-------------
- You need to check if an array is a **rotation of a sorted array**
- When duplicates may exist and order must be preserved
- Good for checking data integrity in cyclic structures

Time Complexity: O(n)      // Single pass through array
Space Complexity: O(1)     // Constant space
*/

