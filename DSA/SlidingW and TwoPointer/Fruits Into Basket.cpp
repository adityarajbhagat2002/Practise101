https://leetcode.com/problems/fruit-into-baskets/description/

/*
===========================================================================================
PROBLEM: FRUIT INTO BASKETS (LeetCode 904)
===========================================================================================

-------------------------------------------------------------------------------------------
1. LOGIC AND INTUITION:
-------------------------------------------------------------------------------------------
The problem states: You have two baskets, and each basket can only hold ONE type of fruit. 
You must pick fruits from trees in a row (consecutive) without skipping. 
REPHRASED: "Find the length of the longest subarray that contains at most 2 unique numbers." [00:03:10]

- Brute Force: Check every subarray. Use a Set to track unique fruit types. [00:06:29]
- Better (Sliding Window): Use two pointers and a Map. If the Map size exceeds 2, 
  shrink the 'Left' pointer using a 'while' loop until only 2 types remain. [00:17:58]
- Optimal (Sliding Window): Instead of fully shrinking, move 'Left' only once if the 
  window is invalid. This ensures the window size never decreases. [00:26:48]

-------------------------------------------------------------------------------------------
2. EDGE CASES:
-------------------------------------------------------------------------------------------
- Array has only 1 type of fruit: Result is the length of the array.
- Array has only 2 types of fruits: Result is the length of the array.
- k=2 is fixed by the problem (two baskets), but the logic works for any 'k'.
- Empty array: Result is 0.

-------------------------------------------------------------------------------------------
3. STEPS (OPTIMAL APPROACH):
-------------------------------------------------------------------------------------------
1. Initialize `left = 0`, `right = 0`, `maxLen = 0`, and a `map<int, int> mpp` to store frequencies.
2. Iterate `right` from 0 to n-1:
3. Add the current fruit `fruits[right]` to the map and increment its frequency. [00:27:35]
4. If `mpp.size() > 2`: (Condition Violated) [00:27:51]
    - Decrease frequency of `fruits[left]`.
    - If frequency of `fruits[left]` becomes 0, remove it from the map. [00:28:14]
    - Move `left` forward by one (shifts the window instead of shrinking it).
5. If `mpp.size() <= 2`:
    - Update `maxLen = max(maxLen, right - left + 1)`. [00:28:47]
6. Return `maxLen`.

-------------------------------------------------------------------------------------------
4. WHY IT WORKS:
-------------------------------------------------------------------------------------------
Once we find a valid window of size 'X', we don't care about any valid windows smaller than 'X'. 
By using an `if` instead of a `while`, we "carry" the maximum window size forward. 
The window only grows when it finds a new segment that can accommodate a larger size while 
staying valid. [00:26:34]

-------------------------------------------------------------------------------------------
5. SPACE AND TIME COMPLEXITY:
-------------------------------------------------------------------------------------------
| Approach    | Time Complexity | Space Complexity |
| :---------- | :-------------- | :--------------- |
| Brute Force | O(N^2)          | O(3) ≈ O(1)      |
| Better      | O(2N)           | O(3) ≈ O(1)      |
| Optimal     | O(N)            | O(3) ≈ O(1)      |
Note: Space is O(1) because the map size is limited to 3 types at any moment. [00:21:28]

-------------------------------------------------------------------------------------------
6. CODE (OPTIMAL IMPLEMENTATION):
-------------------------------------------------------------------------------------------
*/

#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int left = 0;    // Left pointer of the sliding window
        int right = 0;   // Right pointer to expand the window
        int maxlen = 0;  // Stores the maximum fruits collected so far
        
        // Map to store {fruit_type : frequency} in the current window
        // Size of map represents the number of unique baskets used
        unordered_map<int, int> mpp; 

        int n = fruits.size();

        // [00:27:35] Expand the window by moving the right pointer
        while(right < n) {
            // Pick fruit at 'right' and increment its count in the map
            mpp[fruits[right]]++; 

            /* [00:27:51] OPTIMAL LOGIC:
               If map size > 2, we have more than 2 types of fruits.
               In the BETTER approach, we'd use 'while' to shrink the window.
               In the OPTIMAL approach, we use 'if' to just shift the window forward.
               This maintains the largest valid window size found so far.
            */
            if(mpp.size() > 2) {
                // Drop fruit at 'left' from the window
                mpp[fruits[left]]--; 

                // [00:28:14] If count reaches 0, remove the type from map to reduce map.size()
                if(mpp[fruits[left]] == 0) {
                    mpp.erase(fruits[left]);
                }
                // Move left forward by one (shifting the window)
                left++; 
            }

            /* [00:28:47] Only update maxlen if the window is currently valid (size <= 2)
               Since we shift the window, the distance (right-left+1) stays constant 
               until we find an even larger valid window.
            */
            if(mpp.size() <= 2) {
                maxlen = max(maxlen, right - left + 1);
            }
            
            // Move to next tree
            right++; 
        }
        
        // Return the length of the maximum subarray found
        return maxlen;
    }
};

/*
-------------------------------------------------------------------------------------------
8. DRY RUN (Step-by-Step)
-------------------------------------------------------------------------------------------
Input: fruits = [1, 2, 1, 2, 3]
n = 5

Step 1: right=0, left=0
   - Pick fruit 1: mpp = {1:1}
   - mpp.size(1) <= 2: maxlen = max(0, 0-0+1) = 1

Step 2: right=1, left=0
   - Pick fruit 2: mpp = {1:1, 2:1}
   - mpp.size(2) <= 2: maxlen = max(1, 1-0+1) = 2

Step 3: right=2, left=0
   - Pick fruit 1: mpp = {1:2, 2:1}
   - mpp.size(2) <= 2: maxlen = max(2, 2-0+1) = 3

Step 4: right=3, left=0
   - Pick fruit 2: mpp = {1:2, 2:2}
   - mpp.size(2) <= 2: maxlen = max(3, 3-0+1) = 4

Step 5: right=4, left=0
   - Pick fruit 3: mpp = {1:2, 2:2, 3:1}
   - mpp.size(3) > 2! Trigger IF condition:
     - mpp[fruits[left]] (fruit 1) -- => mpp = {1:1, 2:2, 3:1}
     - left++ (left = 1)
   - Current window is [2, 1, 2, 3] (invalid, mpp.size is still 3)
   - maxlen does not update (stays 4).

Result: 4
-------------------------------------------------------------------------------------------
*/

/*
-------------------------------------------------------------------------------------------
7. EXTRA NOTES:
-------------------------------------------------------------------------------------------
- Map vs Set: We use a Map because we need to know when a fruit type is completely 
  removed from the window (frequency becomes 0). A Set only tracks unique items. [00:09:49]
- This problem is a variation of "Longest Subarray with at most K distinct characters." 
  Here, K is fixed at 2.
- The difference between optimal and better is that in optimal we don't leave the longest window
 length where as in better approach where we use while loop we move the left pointer untill we get 
 new valid 
 In optimal we just move the left by one and right by one and check and yeah check only if it is 
 valid 


Feature,Better   Approach (O(2N)),                   Optimal Approach (O(N))
Window Logic,    Shrinking: Resets to a valid state , Non-Shrinking: Maintains max size.
Keyword,         Uses while (mpp.size() > 2),         Uses if (mpp.size() > 2)
MaxLen Update,   Updated after the while loop.,       Updated only if the current state is valid.
===========================================================================================
*/