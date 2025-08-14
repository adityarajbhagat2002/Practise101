// Maximum Subarray (LeetCode 53)
// ✅ Find the contiguous subarray with the largest sum
// Language: C++
// Approach: Kadane’s Algorithm (O(n) time, O(1) space)

/*
Problem:
--------
Given an integer array nums, find the subarray (contiguous) with the largest sum and return its sum.

Constraints:
1 <= nums.length <= 10^5
-10^4 <= nums[i] <= 10^4

---

Logic & Intuition (Kadane's Algorithm):
---------------------------------------
- At every index, decide whether to:
    1. Extend the current subarray (add nums[i] to sum), or
    2. Start a new subarray from nums[i]
- Why? If the previous sum is negative, it will only decrease the sum, so reset to nums[i].
- Keep track of:
    - `sum`     → sum of current subarray
    - `maxSum`  → best sum found so far
- Return the maximum found in one pass.

---

Steps:
------
1. Initialize:
   - maxSum = nums[0]
   - sum    = nums[0]
2. Iterate from i = 1 to n-1:
   - If sum >= 0 → sum += nums[i]
   - Else        → sum = nums[i] (start new subarray)
   - Update maxSum if sum > maxSum
3. Return maxSum.

---

Why it works:
-------------
- This algorithm works because adding a negative running sum reduces the potential future total.
- By resetting the sum to the current element when the sum so far is negative, we ensure we're always tracking the maximum possible sum for any subarray ending at index i.

Time Complexity:
----------------
O(n) — single pass through the array.

Space Complexity:
-----------------
O(1) — only a few variables are used.

---

Extra Notes - Printing the Subarray:
------------------------------------
To track and print the actual subarray giving max sum:
- Use variables: start, ansStart, ansEnd
- When resetting `sum` to nums[i], set start = i
- When updating `maxSum`, also set ansStart = start and ansEnd = i
- At the end, print elements from ansStart to ansEnd.

*/

// ---------------------- Code Implementation ----------------------

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        int maxSum = nums[0];
        int sum = nums[0];

        for (int i = 1; i < n; i++) {
            if (sum >= 0) {
                sum = sum + nums[i];
            } else {
                sum = nums[i];
            }
            if (sum > maxSum) {
                maxSum = sum;
            }
        }
        return maxSum;
    }
};

// ---------------------- Extended Version: Print Subarray ----------------------
void maxSubArrayWithPrint(vector<int>& nums) {
    int n = nums.size();
    int sum = 0;
    int maxSum = INT_MIN;

    int start = 0, ansStart = 0, ansEnd = 0;

    for (int i = 0; i < n; i++) {
        sum += nums[i];

        if (sum > maxSum) {
            maxSum = sum;
            ansStart = start;
            ansEnd = i;
        }

        if (sum < 0) {
            sum = 0;
            start = i + 1;
        }
    }

    cout << "Maximum Sum: " << maxSum << "\nSubarray: [ ";
    for (int i = ansStart; i <= ansEnd; i++) {
        cout << nums[i] << " ";
    }
    cout << "]\n";
}

