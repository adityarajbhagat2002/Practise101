https://leetcode.com/problems/remove-outermost-parentheses/description/
/*
===========================================================
Remove Outermost Parentheses - Complete Guide
===========================================================

Problem Name:
1021. Remove Outermost Parentheses

Problem Statement:
Given a valid parentheses string s, remove the outermost parentheses
of every primitive parentheses string in the decomposition of s.

Definitions:
- A valid parentheses string is balanced.
- A string is primitive if it cannot be split into two non-empty
  valid parentheses strings.
- The input string can be decomposed into multiple primitive parts.

Example:
Input:  "(()())(())"
Primitives: "(()())" + "(())"
After removing outermost parentheses:
Output: "()()()"

-----------------------------------------------------------

Key Insight:
- Parentheses nesting level (depth) tells us whether a parenthesis
  is outermost or not.
- Outermost parentheses occur when:
    '(' takes depth from 0 -> 1
    ')' takes depth from 1 -> 0
- These must be removed.

-----------------------------------------------------------

Logic & Intuition:
- Traverse the string once.
- Maintain a counter `level` representing current nesting depth.
- Rules:
  1. For '(':
     - If level > 0, include it.
     - Then increment level.
  2. For ')':
     - Decrement level first.
     - If level > 0, include it.

This ensures:
- Outermost '(' is skipped (level == 0).
- Outermost ')' is skipped (level becomes 0 after decrement).

-----------------------------------------------------------

Why the order matters:
- '(' is checked BEFORE increment because it *enters* a level.
- ')' is checked AFTER decrement because it *exits* a level.

-----------------------------------------------------------

Time Complexity:
- O(N), where N is the length of the string.
- Each character is processed once.

Space Complexity:
- O(N) for the result string.
- O(1) auxiliary space.

-----------------------------------------------------------

Edge Cases:
- "()()" → "" (each primitive loses both parentheses)
- "(())" → "()"
- Single primitive strings
- Large input size up to 10^5

===========================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string removeOuterParentheses(string s) {
        string result = "";
        int level = 0;  // current nesting depth

        for (char ch : s) {
            if (ch == '(') {
                // If already inside parentheses, keep it
                if (level > 0)
                    result += ch;
                // Enter a deeper level
                level++;
            } 
            else { // ch == ')'
                // Exit a level first
                level--;
                // If still inside parentheses, keep it
                if (level > 0)
                    result += ch;
            }
        }

        return result;
    }
};

/*
-----------------------------------------------------------
Dry Run Example:
Input: "(()())(())"

Char   Level(before)   Action        Level(after)   Result
-----------------------------------------------------------
(          0            skip '('          1            ""
(          1            keep '('          2            "("
)          2            keep ')'          1            "()"
(          1            keep '('          2            "()("
)          2            keep ')'          1            "()()"
)          1            skip ')'          0            "()()"
(          0            skip '('          1            "()()"
(          1            keep '('          2            "()()("
)          2            keep ')'          1            "()()()"
)          1            skip ')'          0            "()()()"

Output: "()()()"
-----------------------------------------------------------
*/

