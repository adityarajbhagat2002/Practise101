https://leetcode.com/problems/move-zeroes/description/

// Leetcode 283: Move Zeroes
// ✅ In-place, efficient, maintains order

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int zero = -1;              // Will store index of first 0
        int n = nums.size();

        // Step 1: Find the first zero's index
        for (int i = 0; i < n; i++) {
            if (nums[i] == 0) {
                zero = i;
                break;
            }
        }

        // Step 2: If there are no zeros, no need to do anything
        if (zero == -1) return;

        // Step 3: Move non-zero elements forward, starting from zero + 1
        for (int i = zero + 1; i < n; i++) {
            if (nums[i] != 0) {
                swap(nums[zero++], nums[i]);
            }
        }
    }
};

/*
Why This Works:
----------------
- We find the first zero index (`zero`). Before this, all values are already non-zero and ordered correctly.
- From the next index onward, every time we find a non-zero, we swap it with the zero index.
- The `zero` pointer tracks where the next non-zero should go.
- This maintains relative order of non-zero elements and shifts all 0s to the end.

When To Use:
-------------
- You want to move/remove elements **in-place**.
- You want to **preserve the relative order** of other elements.
- You want to **minimize unnecessary swaps** (compared to blindly swapping all non-zero elements).

Time Complexity: O(n)
Space Complexity: O(1) (in-place)
*/









