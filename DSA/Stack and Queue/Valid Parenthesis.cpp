https://leetcode.com/problems/valid-parentheses/description/
/*
===========================================================================================
PROBLEM: Valid Parentheses (LeetCode 20)
===========================================================================================

-------------------------------------------------------------------------------------------
1. LOGIC AND INTUITION: [00:03:17]
-------------------------------------------------------------------------------------------
- We need to match every closing bracket with the most recent opening bracket.
- A Stack is the perfect data structure for this because it allows us to look at 
  the "last opening encountered." [00:03:49]
- Rules:
  1. If you see an opening bracket `(`, `[`, `{`, push it onto the stack. [00:04:43]
  2. If you see a closing bracket `)`, `]`, `}`, check the top of the stack:
     - If the stack is empty, there's no matching opener -> Return false. [00:09:46]
     - If the top matches the current closer, pop it and continue. [00:10:16]
     - If it doesn't match -> Return false. [00:11:00]
  3. After iterating through the string, the stack MUST be empty. [00:06:04]

-------------------------------------------------------------------------------------------
2. TIME AND SPACE COMPLEXITY: [00:11:27]
-------------------------------------------------------------------------------------------
- Time Complexity: O(N)
    - We traverse the string exactly once. [00:11:37]
- Space Complexity: O(N)
    - In the worst case (e.g., all opening brackets), we store all N characters in the stack. [00:11:44]

-------------------------------------------------------------------------------------------
3. CODE IMPLEMENTATION (C++):
-------------------------------------------------------------------------------------------
*/

#include <iostream>
#include <stack>
#include <string>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> st; // Stack to store opening brackets [00:08:53]

        for (char it : s) {
            // If it's an opening bracket, push it [00:09:12]
            if (it == '(' || it == '[' || it == '{') {
                st.push(it);
            } 
            else {
                // If it's a closing bracket, the stack must not be empty [00:09:46]
                if (st.empty()) return false;

                char ch = st.top(); // Get the last opening bracket
                st.pop();           // Remove it for comparison [00:10:16]

                // Check if the current closing bracket matches the last opener
                if ((it == ')' && ch == '(') || 
                    (it == ']' && ch == '[') || 
                    (it == '}' && ch == '{')) {
                    continue; // Match found, keep going [00:11:08]
                } else {
                    return false; // Mismatch [00:11:00]
                }
            }
        }

        // Final check: If stack is empty, all brackets matched [00:11:13]
        return st.empty(); 
    }
};

/*
-------------------------------------------------------------------------------------------
4. DRY RUN: [00:06:29]
-------------------------------------------------------------------------------------------
Input: s = "()[{}]"
1. '(' -> Push. Stack: ['(']
2. ')' -> Stack not empty. Top is '('. Match! Pop. Stack: []
3. '[' -> Push. Stack: ['[']
4. '{' -> Push. Stack: ['[', '{']
5. '}' -> Stack not empty. Top is '{'. Match! Pop. Stack: ['[']
6. ']' -> Stack not empty. Top is '['. Match! Pop. Stack: []
7. Loop ends. Stack is empty. Return true.
===========================================================================================
*/