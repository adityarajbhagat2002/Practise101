/*
===========================================================================================
SUBSETS (Power Set) - COMPLETE GUIDE
===========================================================================================
Source: LeetCode 78 / CodeStoryWithMIK (YouTube)
Companies: Microsoft, Amazon, Facebook, Google

-------------------------------------------------------------------------------------------
PROBLEM STATEMENT:
Given an integer array `nums` of unique elements, return all possible subsets (the power set).
The solution set must not contain duplicate subsets. Return the solution in any order.

Example:
Input:  nums = [1, 2, 3]
Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

-------------------------------------------------------------------------------------------
APPROACH: Recursion (Take / Not-Take)
Logic:
1. Every element in the input array has two choices:
   - Either it will be part of the current subset (Take).
   - Or it will not be part of the current subset (Not-Take).
2. We use a helper function `solve(index, nums, temp)` where:
   - `index`: Current element we are considering.
   - `temp`: A vector to store the current subset being formed.
3. Base Case: If `index` reaches the end of the array, the current `temp` is a complete 
   subset. Add it to our global `result`.
4. Recursive Steps:
   - **Take**: Push `nums[i]` to `temp`, then call `solve(i+1)`.
   - **Backtrack**: After the "Take" exploration, pop `nums[i]` from `temp`.
   - **Not-Take**: Call `solve(i+1)` without the current element in `temp`.

-------------------------------------------------------------------------------------------
COMPLEXITY ANALYSIS:
-------------------------------------------------------------------------------------------
Metric           | Complexity      | Explanation
-------------------------------------------------------------------------------------------
Time Complexity  | O(2^N * N)      | 2^N total subsets, and each takes O(N) to copy to result.
Space Complexity | O(N)            | Recursion stack depth and temp vector size.
-------------------------------------------------------------------------------------------
===========================================================================================
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> result;

    void solve(int i, vector<int>& nums, vector<int>& temp) {
        // Base Case: If we have processed all elements
        if (i >= nums.size()) {
            result.push_back(temp);
            return;
        }

        // --- OPTION 1: Take nums[i] ---
        temp.push_back(nums[i]);     // Include the element
        solve(i + 1, nums, temp);    // Explore further

        // --- BACKTRACKING Step ---
        temp.pop_back();             // Remove the element to try the 'Not-Take' path

        // --- OPTION 2: Not-Take nums[i] ---
        solve(i + 1, nums, temp);    // Explore without the element
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> temp;
        solve(0, nums, temp);
        return result;
    }
};

/*
-------------------------------------------------------------------------------------------
RECURSION TREE (Simplified for nums = [1, 2]):
                           solve(0, [])
                          /            \
                    TAKE 1             NOT-TAKE 1
                    /   \               /      \
               TAKE 2   NOT-TAKE 2   TAKE 2    NOT-TAKE 2
               [1, 2]     [1]         [2]         []
-------------------------------------------------------------------------------------------
*/