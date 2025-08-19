https://leetcode.com/problems/remove-duplicates-from-sorted-array/description/
//Do Dry run 

// Leetcode 26: Remove Duplicates from Sorted Array
// ✅ In-place removal, preserving order of unique elements

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int i = 0;  // i points to the last unique element in the modified array

        // Loop through the array starting from the second element
        for (int j = 1; j < nums.size(); j++) {
            // If the current element is not equal to the last unique one
            if (nums[j] != nums[i]) {
                nums[i + 1] = nums[j];  // Place the unique element at the next position
                i++;                    // Move the pointer forward for next unique spot
            }
        }

        return i + 1;  // Total count of unique elements (indexing starts at 0)
    }
};

/*
Why This Works:
----------------
- Since the array is sorted, all duplicates are adjacent
- We use two pointers:
  → `i` to track the last placed unique element
  → `j` to scan the array from left to right
- Whenever a new unique element is found, we place it at the next position after `i`

Example 

Input: nums = [0,0,1,1,1,2,2,3,3,4]
Output: 5, nums = [0,1,2,3,4,_,_,_,_,_]
Explanation: Your function should return k = 5, with the first five elements of nums being 0, 1, 2, 3, and 4 respectively.
It does not matter what you leave beyond the returned k (hence they are underscores).


When To Use:
-------------
- When the array is **sorted** and you need to remove duplicates **in-place**
- When **order of elements must be preserved**
- You want a space-efficient solution

Time Complexity: O(n)      // Traverse array once
Space Complexity: O(1)     // In-place modification
*/
;


