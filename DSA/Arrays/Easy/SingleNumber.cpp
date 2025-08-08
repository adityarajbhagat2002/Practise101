
https://leetcode.com/problems/single-number/


// Leetcode 136: Single Number
// ✅ Finds the element that appears only once in an array where every other element appears twice

class Solution {
public:
    // Function to return the single number that doesn't appear twice
    int singleNumber(vector<int>& nums) {
        int nondupe = 0;    // Will hold the unique element using XOR

        // XOR all elements; pairs will cancel out to 0, leaving the unique element
        for (int i = 0; i < nums.size(); i++) {
            nondupe ^= nums[i];
        }

        return nondupe;
    }
};

/*
Why This Works:
----------------
- XOR (^) of two equal numbers is 0, and XOR with 0 returns the number itself
   e.g. x ^ x = 0, 0 ^ y = y
- When you XOR all numbers, all pairs cancel out, leaving just the single number 
- This technique works in linear time with constant extra space

When To Use:
-------------
- When every element occurs exactly twice except one unique outlier
- Efficiently checks for the non-duplicate in a space-efficient way
- Classic bitwise trick for finding "odd man out" or unique values

Time Complexity: O(n)       // Single pass through the array
Space Complexity: O(1)      // No extra storage needed
*/
