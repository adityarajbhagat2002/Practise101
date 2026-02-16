// ****************************************************************************************
// Problem: Subarray Sum Equals K (LeetCode 560)
// Language: C++
// Contains: Brute Force, Slightly Better, and Optimal explanations
// Plus optimal code (prefix sum + hashmap)
// ****************************************************************************************

/*
Problem Statement:
------------------
Given an array of integers and an integer k,
find the number of continuous subarrays whose sum equals k.

----------------------------------------------------------------------------

Brute Force Approach:
---------------------
- Generate all possible subarrays.
- For every subarray, calculate sum and compare with k.
- If equal, increment count.

Steps:
1. Triple nested loop: 
   - Outer loop from i = 0 to n-1 (start index),
   - Middle loop from j = i to n-1 (end index),
   - Inner loop from i to j (calculate sum).
2. Count every subarray whose sum == k.

Time Complexity: O(n^3)
Space Complexity: O(1)

----------------------------------------------------------------------------

Slightly Better Approach:
-------------------------
- Avoid recalculating sum for each subarray.
- For every i (starting index), keep adding nums[j] to current sum as j increments.
- For every i, j (from i to n-1), sum = sum + nums[j]
- Count each time sum == k.

Time Complexity: O(n^2)
Space Complexity: O(1)

----------------------------------------------------------------------------

Optimal Approach: Prefix Sum + Hash Map
---------------------------------------
Core Idea:
- Use prefix sums to represent the sum up to each index.
- For every index, check if there was a previous prefix sum so that their difference is k.
- Use a hashmap to remember how many times each prefix sum has occurred.

Steps:
1. Initialize a hashmap "mpp" to store counts of each prefix sum. Set mpp[0] = 1 (to count subarrays starting from index 0).
2. Initialize variables: presum = 0 (prefix sum so far), count = 0 (result).
3. Traverse each element in nums:
   a. Update presum += nums[i].
   b. The target is (presum - k); if mpp[target] exists, add that count to 'count'.
   c. Increment mpp[presum].
4. Return count at the end.

Why this works:
- For every index, we instantly know how many subarrays ending at the current index sum to k (using map).
- This results in only one pass through the array and quick lookups/updates.

Time Complexity: O(n)
Space Complexity: O(n) (in worst case, all prefix sums different).

----------------------------------------------------------------------------

Dry Run Example:

nums = [1, 2, 3], k = 3

  i    nums[i]   presum    presum-k     mpp[presum-k]   count   mpp
  --------------------------------------------------------------
  0      1         1          -2            0             0    {0:1,1:1}
  1      2         3           0            1             1    {0:1,1:1,3:1}
  2      3         6           3            1             2    {0:1,1:1,3:1,6:1}

- At i=1, presum=3, presum-k=0, found in map, so count+=1.
- At i=2, presum=6, presum-k=3, found in map, so count+=1.

Subarrays: [1,2] and [3]

----------------------------------------------------------------------------

C++ Code (Optimal Approach):

*/

#include <vector>
#include <unordered_map>
using namespace std;



class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {

        unordered_map<int,int> mpp;   // Stores prefixSum -> how many times it occurred

        mpp[0] = 1;                   // Base case: prefix sum 0 occurs once before start

        int presum = 0;               // Running prefix sum
        int count = 0;                // Result

        // Traverse the array
        for(int i = 0; i < nums.size(); i++) {

            presum += nums[i];        // Add current element to prefix sum

            int remove = presum - k; // Required previous prefix sum

            // If that prefix sum existed before,
            // then those many subarrays ends here with sum k
            count += mpp[remove];

            // Store/update current prefix sum frequency
            mpp[presum]++;
        }

        return count;                // Return total count
    }
};


/*
Summary:
--------
- Brute force: Try all subarrays, O(n^3).
- Slightly better: O(n^2), carry sum forward.
- Optimal: Prefix sum with hash map in O(n) time.
- Powerful trick for counting subarrays with a target sum (or similar problems).
*/
