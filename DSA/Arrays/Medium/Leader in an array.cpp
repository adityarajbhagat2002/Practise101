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
---------------
Input: [16, 17, 4, 3, 5, 2]

Traverse from right:
- Start: maxRight = INT_MIN
- i=5 (2): maxRight=INT_MIN < 2 ⇒ leader = 2; maxRight=2
- i=4 (5): 5 >= 2 ⇒ leader=5; maxRight=5
- i=3 (3): 3 < 5 ⇒ not leader
- i=2 (4): 4 < 5 ⇒ not leader
- i=1 (17): 17 >= 5 ⇒ leader=17; maxRight=17
- i=0 (16): 16 < 17 ⇒ not leader

Leaders collected = [2, 5, 17]
Reversed = [17, 5, 2] (for input order)

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
