https://leetcode.com/problems/max-consecslackutive-ones/description/

// Leetcode 485: Max Consecutive Ones
// ✅ Finds the maximum number of consecutive 1's in a binary array

class Solution {
public:
    // Function to return the maximum number of consecutive 1's in the array
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int count = 0;         // Current streak of 1's
        int prevcount = 0;     // Max streak seen so far

        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == 1) {
                count++;                   // Increment current streak
                if (count > prevcount)     // Update max streak if needed
                    prevcount = count;
            } else {
                count = 0;                 // Reset current streak on 0
            }
        }

        return prevcount;
    }
};

/*
Why This Works:
----------------
- Loops through the array, counting consecutive 1's as they appear
- Resets the current streak whenever a 0 is encountered
- Updates the maximum whenever a longer streak is found
- No extra space is used; method is highly efficient and easy to read

When To Use:
-------------
- To determine the longest run of 1's in a binary sequence or array
- Useful for problems involving segment detection or run analysis in arrays

Time Complexity: O(n)      // Single pass through the array
Space Complexity: O(1)     // Constant extra space
*/
