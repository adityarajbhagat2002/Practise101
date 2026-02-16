https://leetcode.com/problems/maximum-nesting-depth-of-the-parentheses/description/
/*
===========================================================================================
MAXIMUM NESTING DEPTH OF THE PARENTHESES - COMPLETE GUIDE
===========================================================================================
Source: LeetCode 1614 / CodeStoryWithMIK (YouTube)
Companies: Facebook, Google, Amazon

-------------------------------------------------------------------------------------------
PROBLEM STATEMENT:
A string is a Valid Parentheses String (VPS) if it is empty, a single character (not 
parentheses), or matches the pattern (A) or AB where A and B are VPS.

The nesting depth of string `s` is the maximum number of nested parentheses.
- "" has depth 0
- "()(())()" has depth 2
- "()((()())())" has depth 4

Example:
Input:  s = "(1+(2*3)+((8)/4))+1"
Output: 3
Explanation: The digit 8 is inside 3 nested parentheses.

-------------------------------------------------------------------------------------------
APPROACH 1: Stack-Based Approach
Logic:
1. When we see an opening bracket '(', it increases the current nesting depth.
2. When we see a closing bracket ')', it decreases the current nesting depth.
3. We can use a `stack<char>` to track the current active brackets.
4. For every '(', push it onto the stack. For every ')', pop from the stack.
5. The maximum size of the stack at any point represents the maximum nesting depth.

APPROACH 2: Counter-Based Approach (Space Optimized)
Logic:
1. Since we only need the count of nested brackets and don't need to match different 
   types of brackets (like '[' or '{'), a stack is not strictly necessary.
2. Use a simple integer `openBracket` to track current depth.
3. Increment for '(', decrement for ')'.
4. Track the maximum value of `openBracket` during the traversal.

-------------------------------------------------------------------------------------------
COMPLEXITY ANALYSIS:
-------------------------------------------------------------------------------------------
Approach         | Time Complexity | Space Complexity | Notes
-------------------------------------------------------------------------------------------
1. Stack Approach| O(N)            | O(N)             | Storing brackets in a stack.
2. Counter Appr. | O(N)            | O(1)             | Just using two integer variables.
-------------------------------------------------------------------------------------------
===========================================================================================
*/

#include <iostream>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

// --- APPROACH 1: Using Stack ---
class Solution1 {
public:
    int maxDepth(string s) {
        stack<char> st;
        int result = 0;

        for(char &ch : s) {
            if(ch == '(') {
                st.push(ch);
            } else if(ch == ')') {
                st.pop();
            }
            // stack.size() returns size_t (unsigned), so we typecast to int for max()
            result = max(result, (int)st.size());
        }

        return result;
    }
};

// --- APPROACH 2: Space Optimized (No Stack) ---
class Solution2 {
public:
    int maxDepth(string s) {
        int openBracket = 0;
        int result = 0;

        for(char &ch : s) {
            if(ch == '(') {
                openBracket++;
            } else if(ch == ')') {
                openBracket--;
            }
            // The maximum value the counter reaches is the max depth
            result = max(result, openBracket);
        }

        return result;
    }
};

/*
-------------------------------------------------------------------------------------------
DRY RUN (Approach 2):
Input: s = "(1+(2*3)+((8)/4))"

Char | openBracket | result | Action
-------------------------------------
 (   |      1      |   1    | result = max(0, 1)
 1   |      1      |   1    | No change
 +   |      1      |   1    | No change
 (   |      2      |   2    | result = max(1, 2)
 2   |      2      |   2    | ...
 )   |      1      |   2    | Decrement depth
 +   |      1      |   2    | ...
 (   |      2      |   2    | ...
 (   |      3      |   3    | result = max(2, 3)
 8   |      3      |   3    | ...
 )   |      2      |   3    | ...
 /   |      2      |   3    | ...
 )   |      1      |   3    | ...
 )   |      0      |   3    | ...

Final Result: 3
-------------------------------------------------------------------------------------------
*/