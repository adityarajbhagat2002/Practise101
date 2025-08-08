https://www.geeksforgeeks.org/problems/longest-sub-array-with-sum-k0809/1

// Longest Subarray with Sum K
// ✅ Finds the length of the longest subarray whose sum equals a given value k

class Solution {
  public:
    // Function to return the length of the longest subarray with sum K
    int longestSubarray(vector<int>& arr, int k) {
        int maxlen = 0;                // Tracks the longest subarray found
        int sum = 0;                   // Cumulative prefix sum up to current index
        map<int, int> presum;          // Maps each prefix sum to its earliest occurrence index

        for (int i = 0; i < arr.size(); i++) {
            sum += arr[i];             // 1. Add current element to running sum

            /* 
            Case 1: If the current prefix sum equals k, then the subarray
            from index 0 to i has sum k. This is a candidate for max length.
            */
            if (sum == k) {
                maxlen = max(maxlen, i + 1);
            }

            /* 
            Case 2: Is there an earlier prefix sum, say at index prev, such that
            sum - presum[prev] == k?
            That would mean subarray (prev+1 ... i) sums to k.
            So, rem = sum - k; if rem appeared before, use its earliest index to calculate length.
            */
            int rem = sum - k;                         // What remainder (rem) would. indicate a valid subarray ending at i?
            if (presum.find(rem) != presum.end()) {
                int len = i - presum[rem];             // Length of such a subarray
                maxlen = max(maxlen, len);             // Update if it's longer
            }

            /*
            Map logic: 
            - We *only* store the first time each prefix sum appears.
            - Why? If a sum repeats, using its earliest index lets us form the longest subarray possible.
            */
            if (presum.find(sum) == presum.end()) {
                presum[sum] = i;    // Record this prefix sum and its index (if not already recorded)
            }
        }
        return maxlen;
    }
};

/*
========================
Why This Works (Detailed)
========================
- The prefix sum at i is: sum = arr[0] + ... + arr[i]
- If you ever find a previous prefix sum at index j (j < i) such that sum - presum[j] = k,
  it means subarray (j+1) to i sums to k.
- The map lets us check for existence of such prefix sums in O(1) time at each step.

-------------
Variable Intent:
-------------
sum    - The running cumulative sum as we iterate.
rem    - At current i, what earlier prefix sum is needed so that subarray ending at i sums to k?
presum - Tracks the FIRST index at which each prefix sum occurs (so we maximize possible subarray length).
maxlen - The length of the longest subarray found that sums to k.

-------------
Why Store Only First Occurrence?
-------------
- If a prefix sum reoccurs, skipping further updates ensures we always use the most *leftward* starting index,
  which produces the longest subarray.
- For example, if a sum appears at both index 2 and index 5, using index 2 gives more distance to the current i.

-------------
Visualization Example:
-------------
arr = [10, 5, 2, 7, 1, -10], k = 15

Step-by-step:
- i = 0: sum=10   → not k, store 10:0
- i = 1: sum=15   → sum==k! maxlen=2, store 15:1
- i = 2: sum=17   → rem=2 not found, store 17:2
- i = 3: sum=24   → rem=9 not found, store 24:3
- i = 4: sum=25   → rem=10 found at 0: subarray [5,2,7,1], len=4, maxlen=4
- i = 5: sum=15   → sum==k! maxlen=6 (entire array!)

-------------
When To Use:
-------------
- Needed for finding the length of the longest subarray with a given sum efficiently (including negatives).
- Useful for interview problems or real-world scenarios (like cumulative goals, balances, scanning scores, etc).
- Far more efficient than O(n^2) brute-force.

-------------
Time and Space Complexity:
-------------
Time:  O(n)    // Single pass
Space: O(n)    // Worst case, unique sum per index

-------------
Mistake to Avoid:
-------------
- Don't overwrite an existing prefix sum in the map; first occurrence is important for maximum length!
*/





/* 
*****************************The Sliding Window Technique*****************************

Note: The sliding window (two-pointer) approach only works efficiently when all array elements are **non-negative**.

How Sliding Window Works:

- Maintain a window with pointers `left` and `right`
- Expand `right` pointer and add arr[right] to `sum`
- When `sum` > k, move `left` forward subtracting arr[left] from `sum`
- When `sum` == k, check max length
- Proceed until end of array

Example Code:

*/

int longestSubarraySlidingWindow(vector<int>& arr, int k) {
    int n = arr.size();
    int left = 0, right = 0;
    int sum = 0;
    int maxlen = 0;

    while (right < n) {
        sum += arr[right];  // Expand window

        // Contract window if sum > k
        while (sum > k && left <= right) {
            sum -= arr[left];
            left++;
        }

        if (sum == k) {
            maxlen = max(maxlen, right - left + 1);
        }

        right++;
    }

    return maxlen;
}

/*
Summary:
- Sliding window uses O(1) space and O(n) time.
- Only valid for arrays without negative numbers (non-negative arrays).
- For arrays with negatives, use prefix sum + hashmap approach as above.
*/




