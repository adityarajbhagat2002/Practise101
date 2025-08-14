// ********************************************************************************************
// Problem Name: Rearrange Array Elements by Sign
// LeetCode: Rearrange array so that positive and negative numbers alternate
// Language: C++
// ********************************************************************************************

/*
CASE 1: Equal number of positive and negative numbers (Even-sized array)
------------------------------------------------------------------------
Intuition & Logic:
------------------
- We know half of the elements are positive and half are negative.
- The rearranged array should start with a positive number at index 0, then alternate signs.
- This means:
    - Positive numbers go at even indices: 0, 2, 4, ...
    - Negative numbers go at odd indices: 1, 3, 5, ...
- By iterating once through 'nums':
    - If current element is positive → place at posIndex (even), then posIndex += 2.
    - If current element is negative → place at negIndex (odd), then negIndex += 2.
- This preserves **relative order** because we insert numbers in order of appearance.

Algorithm Steps:
----------------
1. Initialize `posIndex = 0` and `negIndex = 1`.
2. Create a result array `ans` of size `n`.
3. Loop through each number in `nums`:
   a) If > 0, place at ans[posIndex], increment posIndex by 2.
   b) Else, place at ans[negIndex], increment negIndex by 2.
4. Return `ans`.

Time Complexity:
----------------
- O(n): Single pass through nums of size n.

Space Complexity:
-----------------
- O(n): Extra output array of size equal to input.

Why This Works:
---------------
- Equal counts of positives and negatives prevent index overflow.
- Direct placement avoids extra passes or swaps.
- Maintains relative order separately for positives and negatives.
*/

// ---------------------- Code Implementation: Case 1 ----------------------

#include <vector>
using namespace std;

class SolutionCase1 {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n, 0);
        int posIndex = 0; // Even indices for positives
        int negIndex = 1; // Odd indices for negatives

        for (int i = 0; i < n; i++) {
            if (nums[i] < 0) {
                ans[negIndex] = nums[i];
                negIndex += 2;
            } else {
                ans[posIndex] = nums[i];
                posIndex += 2;
            }
        }
        return ans;
    }
};

/*
----------------------------------------------------------------------------------------------------
CASE 2: Unequal count of positive and negative numbers (Leftover elements allowed)
----------------------------------------------------------------------------------
Problem Variation:
------------------
- Same requirement: alternate positive and negative numbers as much as possible.
- When one sign runs out, append all remaining elements of the other sign at the end.

Intuition & Logic:
------------------
1. First, separate nums into two lists:
   - `positives`: all positive numbers in order
   - `negatives`: all negative numbers in order
2. Alternate inserting positives and negatives into the result array:
   - Start with a positive by default (`turnPos = true`)
   - Switch turn each time using `turnPos = !turnPos`
3. When one list is exhausted, append all remaining elements from the other.

Algorithm Steps:
----------------
1. Create two arrays: positives[] and negatives[] using one pass.
2. Initialize `i = 0`, `j = 0` for indexes in positives and negatives, and `turnPos = true`.
3. While both arrays have elements:
    - If turnPos is true → push positives[i++] to ans
    - Else → push negatives[j++] to ans
    - Flip turn: turnPos = !turnPos
4. Append leftover positives or negatives to ans.
5. Return result.

Time Complexity:
----------------
- O(n): Separate positives/negatives in one pass + merge in another pass.

Space Complexity:
-----------------
- O(n): Storage for positives, negatives, and result arrays.

Why This Works:
---------------
- Works for both balanced and unbalanced counts.
- Alternates as much as possible and ensures unused elements are preserved at the end.
- Maintains order within each category (positive/negative).
*/

// ---------------------- Code Implementation: Case 2 ----------------------

class SolutionCase2 {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        vector<int> positives, negatives;
        for (int num : nums) {
            if (num >= 0) positives.push_back(num);
            else negatives.push_back(num);
        }

        vector<int> ans;
        ans.reserve(nums.size());
        int i = 0, j = 0;
        bool turnPos = true; // Start with a positive number

        // Alternate placement while both lists have elements
        while (i < positives.size() && j < negatives.size()) {
            if (turnPos) {
                ans.push_back(positives[i++]);
            } else {
                ans.push_back(negatives[j++]);
            }
            turnPos = !turnPos; // Flip turn
        }

        // Append leftover positives
        while (i < positives.size()) {
            ans.push_back(positives[i++]);
        }
        // Append leftover negatives
        while (j < negatives.size()) {
            ans.push_back(negatives[j++]);
        }

        return ans;
    }
};

/*
Extra Notes:
------------
- In Case 1, fixed even/odd placement works only when positives == negatives.
- In Case 2, alternating using a boolean turn flag works for all cases.
- `turnPos` toggling is cleaner & easier to understand than checking index parity.
- If you want to start with a negative in Case 2, just set `turnPos = false` initially.
- Both cases preserve relative ordering for each sign group.
*/
