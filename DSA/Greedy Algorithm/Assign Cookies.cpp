https://leetcode.com/problems/assign-cookies/description/
/*
===========================================================================================
PROBLEM: ASSIGN COOKIES (LeetCode)
===========================================================================================

-------------------------------------------------------------------------------------------
1. LOGIC AND INTUITION: [00:03:34]
-------------------------------------------------------------------------------------------
- The Goal: Maximize the number of satisfied children.
- Greedy Choice: Give the child the smallest cookie that is ≥ their greed factor. [00:04:14]
- By using the smallest sufficient cookie, we "greedily" save larger cookies for children who 
  actually need them (those with higher greed factors). [00:04:07]

-------------------------------------------------------------------------------------------
2. WHY SORTING IS REQUIRED: [00:04:27]
-------------------------------------------------------------------------------------------
Sorting both the greed array (children) and the size array (cookies) allows us to:
- Process the children with the smallest needs first. [00:04:30]
- Efficiently find the smallest available cookie that meets that need using two pointers.

-------------------------------------------------------------------------------------------
3. SPACE AND TIME COMPLEXITY: [00:09:33]
-------------------------------------------------------------------------------------------
- Time Complexity: O(N log N + M log M)
    - Sorting greed array (N children): O(N log N).
    - Sorting cookie array (M cookies): O(M log M).
    - Single pass while loop: O(M) because we iterate through cookies. [00:09:55]
- Space Complexity: O(1) (excluding the space taken by sorting algorithms). [00:10:03]

-------------------------------------------------------------------------------------------
4. CODE IMPLEMENTATION (C++):
-------------------------------------------------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        
        // Step 1: Sort both arrays to apply greedy logic
        sort(g.begin(), g.end());  // Sort children by greed
        sort(s.begin(), s.end());  // Sort cookies by size

        int n = g.size();  // Number of children
        int m = s.size();  // Number of cookies

        // Step 2: Initialize pointers and counter
        int left = 0;      // Pointer for children (g)
        int right = 0;     // Pointer for cookies (s)
        int count = 0;     // Number of satisfied children

        // Step 3: Traverse both arrays
        // Continue until we run out of children or cookies
        while (left < n && right < m) {

            // If current cookie can satisfy current child
            if (s[right] >= g[left]) {
                count++;     // Child is satisfied
                left++;      // Move to next child
                right++;     // Move to next cookie
            }
            else {
                // Cookie too small → discard it
                right++;     // Try next larger cookie
            }
        }

        // Step 4: Return total satisfied children
        return count;
    }
};

/*
-------------------------------------------------------------------------------------------
5. DRY RUN EXAMPLE: [00:05:06]
-------------------------------------------------------------------------------------------
Input: Greed (g) = [1, 3, 3], Cookies (s) = [1, 2, 4]
Sorted: g = [1, 3, 3], s = [1, 2, 4]

1. Cookie 1, Child 1: 1 >= 1? Yes. -> Child 1 satisfied (right=1). Move to Cookie 2.
2. Cookie 2, Child 2: 2 >= 3? No.  -> Child 2 not satisfied. Move to Cookie 4.
3. Cookie 4, Child 2: 4 >= 3? Yes. -> Child 2 satisfied (right=2). Move to Child 3.
                                     (Loop ends as no more cookies left).
Output: 2 satisfied children.
===========================================================================================
*/