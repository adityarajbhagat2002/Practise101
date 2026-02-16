https://www.geeksforgeeks.org/problems/next-larger-element-1587115620/1

/*
===========================================================================================
PROBLEM: Next Greater Element (NGE)
===========================================================================================

-------------------------------------------------------------------------------------------
1. LOGIC & INTUITION: [00:05:33]
-------------------------------------------------------------------------------------------
- To find the next greater element to the RIGHT, we should traverse the array from BACK to FRONT. [00:05:43]
- By traversing backwards, when we are at index `i`, we already know all elements to its right.
- We use a Monotonic Stack to store elements in a decreasing order (from bottom to top). [00:11:41]
- The "Light Pole" Analogy: [00:07:25]
    - If you are standing at an index and looking right, you can only see elements taller than 
      the ones in front of them. Shorter elements are "hidden" and irrelevant for future taller elements.

-------------------------------------------------------------------------------------------
2. ALGORITHM: [00:13:24]
-------------------------------------------------------------------------------------------
1. Initialize an empty stack and a result array `nge` of size N.
2. Loop from `i = n-1` down to `0`:
   a. While the stack is NOT empty AND `stack.top()` <= `arr[i]`:
      - Pop from the stack (these elements are not greater and won't be NGE for anyone to the left). [00:14:12]
   b. If the stack is empty:
      - `nge[i] = -1` (no greater element found on the right). [00:14:26]
   c. Else:
      - `nge[i] = stack.top()` (the current top is the first element greater than `arr[i]`). [00:14:43]
   d. Push `arr[i]` onto the stack. [00:15:03]

-------------------------------------------------------------------------------------------
3. COMPLEXITY ANALYSIS: [00:15:14]
-------------------------------------------------------------------------------------------
- Time Complexity: O(2N) ≈ O(N) [00:15:40]
    - Each element is pushed onto the stack once and popped at most once.
- Space Complexity: O(N) [00:17:34]
    - For the stack and the result array.

-------------------------------------------------------------------------------------------
4. CODE IMPLEMENTATION (C++):
-------------------------------------------------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    vector<int> nextLargerElement(vector<int>& arr) {
        int n = arr.size();
        // Pre-allocate size n to avoid manual reversing later
        vector<int> ans(n); 
        stack<int> st;
        
        // Traverse from back to front [00:05:43]
        for(int i = n - 1; i >= 0; i--) {
            
            // Pop elements that are smaller or equal [00:14:12]
            while(!st.empty() && st.top() <= arr[i]) {
                st.pop();
            }
            
            // Find the NGE [00:14:26]
            if(st.empty()) {
                ans[i] = -1; // Fill at index 'i' to keep correct order
            } else {
                ans[i] = st.top();
            }
            
            // IMPORTANT: Push the current element EVERY time [00:15:03]
            st.push(arr[i]);
        }
        
        return ans;
    }
};

/*
-------------------------------------------------------------------------------------------
5. DRY RUN: [00:06:14]
-------------------------------------------------------------------------------------------
Input: [6, 0, 8, 1, 3]
1. i=4 (3): Stack empty -> nge[4]=-1. Push 3. Stack: [3]
2. i=3 (1): Top(3) > 1 -> nge[3]=3. Push 1. Stack: [3, 1]
3. i=2 (8): Top(1) <= 8 (pop), Top(3) <= 8 (pop). Stack empty -> nge[2]=-1. Push 8. Stack: [8]
4. i=1 (0): Top(8) > 0 -> nge[1]=8. Push 0. Stack: [8, 0]
5. i=0 (6): Top(0) <= 6 (pop), Top(8) > 6 -> nge[0]=8. Push 6. Stack: [8, 6]
Result: [8, 8, -1, 3, -1] [00:02:11]
===========================================================================================
*/