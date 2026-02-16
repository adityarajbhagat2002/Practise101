https://leetcode.com/problems/max-consecutive-ones-iii/description/

/*
===========================================================================================
PROBLEM: MAX CONSECUTIVE ONES III (LeetCode 1004)
===========================================================================================

-------------------------------------------------------------------------------------------
1. LOGIC AND INTUITION:
-------------------------------------------------------------------------------------------
The problem asks for the maximum consecutive 1s after flipping 'k' zeros. 
REPHRASED: "Find the longest subarray that contains at most 'k' zeros."

- Brute Force: Check every possible subarray. If zeros > k, that subarray is invalid.
- Better (Sliding Window): Use two pointers. Expand 'Right'. If zeros exceed 'k', 
  shrink 'Left' until zeros are <= k again.
- Optimal (Sliding Window): Instead of shrinking 'Left' multiple times, move 'Left' 
  only once when invalid. This "preserves" the maximum window size found so far.



-------------------------------------------------------------------------------------------
2. EDGE CASES:
-------------------------------------------------------------------------------------------
- k = 0: The problem becomes "Find the longest sequence of existing 1s."
- k >= size of array: You can flip everything; result is the array length.
- Array is all 0s: Result is 'k'.
- Array is all 1s: Result is the array length.

-------------------------------------------------------------------------------------------
3. STEPS (OPTIMAL APPROACH):
-------------------------------------------------------------------------------------------
1. Initialize `left = 0`, `right = 0`, `zeros = 0`, and `maxLen = 0`.
2. Expand the window by moving `right` from 0 to n-1.
3. If `nums[right] == 0`, increment the `zeros` counter.
4. If `zeros > k`:
    - Check if `nums[left] == 0`. If yes, decrement `zeros`.
    - Move `left` forward by one step (to keep the window size constant).
5. If `zeros <= k`, update `maxLen = max(maxLen, right - left + 1)`.
6. Return `maxLen`.

-------------------------------------------------------------------------------------------
4. WHY IT WORKS (THE "NON-SHRINKING" WINDOW):
-------------------------------------------------------------------------------------------
In the 'Better' approach, we shrink 'left' to make the window valid again. 
However, once we find a valid window of size (e.g., 5), we no longer care about 
valid windows of size 4 or 3. 
By moving 'left' only once when invalid, we ensure our window size never decreases. 
It only stays the same (sliding) or grows (expanding).

-------------------------------------------------------------------------------------------
5. SPACE AND TIME COMPLEXITY:
-------------------------------------------------------------------------------------------
| Approach    | Time Complexity | Space Complexity |
| :---------- | :-------------- | :--------------- |
| Brute Force | O(N^2)          | O(1)             |
| Better      | O(2N)           | O(1)             |
| Optimal     | O(N)            | O(1)             |

-------------------------------------------------------------------------------------------
6. CODE (OPTIMAL IMPLEMENTATION):
-------------------------------------------------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    // Optimal Approach: Single Pass O(N)
    int longestOnes(vector<int>& nums, int k) {
        int n = nums.size();
        int left = 0, right = 0, maxlen = 0, zeros = 0;

        while (right < n) {
            // Expand phase
            if (nums[right] == 0) {
                zeros++;
            }

            // Greedy Shift: If zeros > k, we move left once.
            // We don't use 'while' because we want to maintain window size.
            if (zeros > k) {
                if (nums[left] == 0) {
                    zeros--;
                }
                left++;
            }

            // Update only if the current window is valid
            if (zeros <= k) {
                maxlen = max(maxlen, right - left + 1);
            }

            right++;
        }
        return maxlen;
    }
};

/*
-------------------------------------------------------------------------------------------
7. EXTRA NOTES (THEORY OF ALL APPROACHES):
-------------------------------------------------------------------------------------------
BRUTE FORCE THEORY:
We use two loops. i (start) and j (end). For every i, we move j until we count 
k+1 zeros. We then stop and move i to the next index. 
Complexity: O(N^2) because we re-scan elements for every start index.

BETTER APPROACH THEORY:
Instead of resetting 'j' for every 'i', we move 'left' and 'right' independently. 
If zeros > k, the inner 'while' loop moves 'left' until zeros <= k.
Even though it has a nested loop, each pointer travels N steps, making it O(2N).

OPTIMAL APPROACH THEORY:
The 'if' condition (shown in code above) ensures we never look at windows smaller 
than the best one found so far. This reduces the complexity to a strict O(N).
===========================================================================================

WHY OPTIMAL VS BETTTER FOR ALL QUESTIONS 
📘 NOTES – Sliding Window (Better vs Optimal)
🔹 Problem Pattern

We are solving:

Find the longest subarray that satisfies a condition
(here: at most k zeros)

This is a classic variable-size sliding window problem.

🟡 BETTER APPROACH (Shrink Until Valid)
Idea:

Expand right.

If window becomes invalid (zeros > k),
shrink left until it becomes valid again.

Update maxLen.

Template:
while (right < n) {

    // expand
    if (condition)
        count++;

    // shrink fully until valid
    while (invalid_condition) {
        if (nums[left] == something)
            count--;
        left++;
    }

    maxLen = max(maxLen, right - left + 1);
    right++;
}

Key Properties:

Window may shrink multiple times in one iteration.

Total left movements ≤ N.

Total right movements ≤ N.

Time = O(2N) → O(N).

Easy to understand.

Most common sliding window form.

🔵 OPTIMAL APPROACH (Non-Shrinking Window / Sliding Window)
Idea:

Instead of shrinking fully,
we move left only once when invalid.

if (invalid_condition) {
    if (nums[left] == something)
        count--;
    left++;
}

Key Insight:

Once we find a valid window of size X,
we don’t care about windows smaller than X.

So we:

Either grow window

Or slide it forward

Window size never aggressively shrinks.

🔥 Why Optimal Works

Because:

left and right both move at most N times.

Each element enters window once.

Each element leaves window once.

Total operations ≤ 2N.

Time = O(N).

🧠 Sliding Window Rules

✔ right always moves forward
✔ left never moves backward
✔ Maintain a condition (like count of zeros)
✔ Keep window valid

*/