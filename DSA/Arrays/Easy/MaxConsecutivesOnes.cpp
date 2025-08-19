// ****************************************************************************************
// Problem: Leaders in an Array
// Language: C++
// ****************************************************************************************

/*
Problem Statement:
------------------
Given an array of integers, find all the leader elements.
A leader is defined as an element that is strictly greater than all the elements to its right.
The last element is always a leader since there are no elements after it.

---

Intuition:
----------
- For each element, check if there is any element greater than it on its right.
- If no such element exists, then the current element is a leader.
- The last element is always a leader by this definition.

---

Brute Force Approach:
---------------------
Logic:
- For every element arr[i], scan all elements to the right (arr[j], j > i).
- If any arr[j] > arr[i], then arr[i] is not a leader.
- Otherwise, arr[i] is a leader.

Steps:
1. For each index i in [0..n-1]:
   - Assume arr[i] is a leader.
   - For each element on its right, if any element > arr[i], mark arr[i] as not leader.
   - If not marked, add arr[i] to the answer.

Time and Space Complexity:
- Time: O(n^2) due to nested loops.
- Space: O(n) for storing leaders, in worst case all can be leaders.

---

Optimal Approach (O(n)):
-----------------------
Intuition:
- The key question: Is arr[i] greater than all elements on its right?
- Start scanning from the right.
- Keep track of the maximum element seen so far (maxRight).
- Any element greater than maxRight is a leader.

Steps:
1. Initialize maxRight with a very small value (eg. INT_MIN).
2. Traverse the array from right to left.
3. For each element:
   - If arr[i] >= maxRight, arr[i] is a leader.
   - Update maxRight = max(maxRight, arr[i]).
4. Since we traverse from right, leaders are collected in reverse order.
5. Reverse the leaders array before returning to maintain input order.

Additional notes:
- If output should be sorted, then sort at the end before returning.
- The last element is always a leader.
- Works efficiently with duplicates and large arrays.

Time and Space Complexity:
- Time: O(n) for scanning + O(n log n) if sorting leaders is required.
- Space: O(n) for storing leaders.

---

Example Dry Run:
----------------
Suppose input: [10, 22, 12, 3, 6, 6, 7]

Step-by-step (traverse right to left):

Index | arr[i] | maxele (before) | Is Leader?   | ans (so far)     | maxele (after)
------|--------|-----------------|--------------|------------------|---------------
  6   |   7    | MIN             | Yes          | [7]              | 7
  5   |   6    | 7               | No           | [7]              | 7
  4   |   6    | 7               | No           | [7]              | 7
  3   |   3    | 7               | No           | [7]              | 7
  2   |  12    | 7               | Yes          | [7, 12]          | 12
  1   |  22    | 12              | Yes          | [7, 12, 22]      | 22
  0   |  10    | 22              | No           | [7, 12, 22]      | 22

Leaders collected (reverse order): [7, 12, 22]  
After reverse for original order: [22, 12, 7]

---

Code Implementation:

*/

#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    vector<int> leaders(vector<int>& arr) {
        vector<int> ans;
        int maxele = INT_MIN;
        int n = arr.size();

        // Traverse from right to left
        for (int i = n - 1; i >= 0; i--) {
            if (arr[i] >= maxele) {
                ans.push_back(arr[i]);
            }
            maxele = max(maxele, arr[i]);
        }
        reverse(ans.begin(), ans.end());  // Reverse to maintain original order
        return ans;
    }
};

/*
Summary:
- Brute force: check every element with elements to its right.
- Optimal: scan backwards, track max element, identify leaders.
- Time: O(n) optimal, O(n^2) brute.
- Space: O(n).
- Useful for interview to first mention brute force, then optimal.
*/
