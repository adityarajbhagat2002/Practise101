// Sort Colors (Leetcode 75)
// ✅ Sort an array containing 0s, 1s, and 2s representing colors (red, white, blue)
//    using one-pass Dutch National Flag algorithm with constant space

/*
Problem:
--------
Given an array nums consisting of 0s, 1s, and 2s, sort them in-place so that all 0s (red) come first,
all 1s (white) next, and all 2s (blue) last.

Must solve it in one pass and O(1) extra space.

Logic & Intuition:
-------------------
- Use three pointers: 
    - low: boundary of red zone (all 0s)
    - mid: current element to check
    - high: boundary of blue zone (all 2s)
- The array is conceptually divided into four sections at any time:
    [0...low-1]: all 0s (red zone)
    [low...mid-1]: all 1s (white zone)
    [mid...high]: unknown/unprocessed
    [high+1...n-1]: all 2s (blue zone)
- Move mid pointer from left to right, classifying elements:
    - If nums[mid] == 0: swap with nums[low], low++, mid++
    - If nums[mid] == 1: mid++
    - If nums[mid] == 2: swap with nums[high], high--, do not move mid yet (check swapped element)
    
Why this works:
---------------
- Each element visited once: O(n) time.
- Swaps ensure partitioning of colors.
- Only constant extra memory used: O(1) space.
- Satisfies problem constraints of one pass and constant space.

/*
Diagram:
---------
  Array divided as:

  +---------+-----------+------------+------------+
  | 0's     |   1's     |   Unknown  |   2's      |
  |  Red    |  White    |            |   Blue     |
  +---------+-----------+------------+------------+
   ^         ^           ^            ^
   0         low         mid          high

As the algorithm runs, regions grow or shrink accordingly, 
and unknown region (mid to high) contracts till fully classified.
*/

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n = nums.size();
        int low = 0, mid = 0;
        int high = n - 1;

        while (mid <= high) {
            if (nums[mid] == 0) {
                // Swap current element with element at low, expand red zone
                swap(nums[mid], nums[low]);
                low++;
                mid++;
            }
            else if (nums[mid] == 1) {
                // White zone - just move mid pointer
                mid++;
            }
            else {
                // nums[mid] == 2, move blue to end by swapping with high
                swap(nums[mid], nums[high]);
                high--;
                // Do NOT move mid here because swapped element must be checked next
            }
        }
    }
};



/*
Time Complexity:
----------------
- O(n), where n is the length of the array.
- Each element is processed exactly once.
- The pointers low, mid, and high move at most n steps in total.

Space Complexity:
----------------
- O(1), constant extra space.
- Only uses a fixed number of pointers/variables regardless of input size.

Summary:
--------
- One-pass in-place partition using three pointers.
- Efficient and optimal for sorting the three distinct values 0, 1, and 2.
- Intuitive approach inspired by the Dutch National Flag problem.
- Highly recommended for problems involving sorting small fixed sets of values.

*/