// ****************************************************************************************
// Problem: Next Permutation
// LeetCode: Rearrange numbers into the lexicographically next greater permutation
// Language: C++
// ****************************************************************************************

/*
Problem Statement:
------------------
Given an array of integers nums, rearrange it into the lexicographically next greater permutation of numbers.
If such arrangement is impossible (currently highest permutation), rearrange it into the lowest possible order (ascending).

Notes:
- The replacement must be done in-place and use only constant extra memory.
- The array may contain duplicate numbers.

---

## Brute Force Approach (High-Level Overview):

1. **Generate all permutations** of the given array.
2. **Sort all permutations lexicographically**.
3. **Find the current permutation in the sorted list**.
4. Return the permutation next to the current one (or the smallest if current is last).

### Why Brute Force is Impractical:
- Generating all permutations is factorial in time \( O(n!) \).
- Even for moderate \( n \), this becomes computationally infeasible.
- Does not satisfy in-place or constant space requirements.


---

## Optimal Approach (Greedy In-Place Algorithm):

### Intuition:

- Think of permutations arranged in ascending (dictionary) order.
- The next permutation is the minimal rearrangement to get the next bigger arrangement.
- To find it:
  - Find the longest non-increasing suffix from the end.
  - Identify the pivot just before this suffix.
  - Swap the pivot with the rightmost element larger than pivot.
  - Reverse the suffix to get the minimal order.

### Steps:

1. Traverse from right to left to find the first index `i` where `nums[i] < nums[i+1]`.  
   This index `i` is the pivot point.  
   If no such index exists, the array is the highest permutation.

2. If array is the highest permutation, reverse entire array (to lowest permutation).

3. Otherwise, find the rightmost index `j` greater than `i` such that `nums[j] > nums[i]`.

4. Swap `nums[i]` and `nums[j]`.

5. Reverse the suffix starting at `i+1` to the end.

---

### Why It Works:

- The pivot `i` is where we can make the permutation "larger".
- Swapping the pivot with next bigger number makes the permutation just bigger enough.
- Reversing suffix ensures the suffix is the smallest possible order.

---

### Time Complexity:
- O(n) — single pass to find pivot, single pass to find element to swap, single pass to reverse suffix.

### Space Complexity:
- O(1) — in-place modifications without extra space.

---

### Edge Cases:
- Array sorted in descending order (last permutation).
- Arrays with duplicates.
- Small arrays (single element).

---

## Code Implementation:

*/

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int index = -1;
        int n = nums.size();

        // Step 1: Find the pivot
        for (int i = n - 2; i >= 0; --i) {
            if (nums[i] < nums[i + 1]) {
                index = i;
                break;
            }
        }

        // Step 2: If pivot not found, reverse whole array
        if (index == -1) {
            reverse(nums.begin(), nums.end());
            return;
        }

        // Step 3: Find rightmost element greater than pivot
        for (int i = n - 1; i > index; --i) {
            if (nums[i] > nums[index]) {
                swap(nums[i], nums[index]);
                break;
            }
        }

        // Step 4: Reverse suffix after pivot
        reverse(nums.begin() + index + 1, nums.end());
    }
};

/*
Example Dry Run:

Input: [1, 2, 3]
- Pivot found at i=1 (2 < 3)
- Rightmost element > 2 is 3 at j=2
- Swap: [1, 3, 2]
- Reverse suffix after i: [1, 3, 2] (suffix length 1, no change)
Output: [1, 3, 2]

Input: [3, 2, 1]
- No pivot found (descending array)
- Reverse whole array: [1, 2, 3]
Output: [1, 2, 3]

Input: [1, 1, 5]
- Pivot at i=1 (1<5)
- Rightmost element > 1 is 5 at j=2
- Swap: [1, 5, 1]
- Reverse suffix after i: [1, 5, 1] (suffix length 1, unchanged)
Output: [1, 5, 1]

Summary:
- Brute force approach is factorial time and space.
- Optimal solution uses a clever in-place approach with clear intuition.
- Considers longest non-increasing suffix to find pivot.
- Swaps pivot with just bigger element.
- Reverses suffix to form next lex order.
- Runs in O(n) time and constant space.



Additional Notes:
-----------------
- C++ STL provides function `next_permutation` which does this internally.
- In interviews, show understanding by explaining:
  - The pivot (dip) search
  - The swap with next bigger number
  - The reversal for minimal sequence after pivot.
- Demonstrate dry runs for clarity.

---

*/
