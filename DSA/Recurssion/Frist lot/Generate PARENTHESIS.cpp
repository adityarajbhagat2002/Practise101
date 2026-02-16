/*
===========================================================================================
GENERATE PARENTHESES - 2 APPROACHES
===========================================================================================
Source: CodeStoryWithMIK (YouTube Video 15)
Concept: Backtracking / State-Restricted Recursion
Complexity: 
- Approach 1: Time O(2^(2n) * n) | Space O(n)
- Approach 2: Time O(4^n / (n*sqrt(n))) | Space O(n) 

-------------------------------------------------------------------------------------------
PROBLEM DESCRIPTION:
- Given n pairs of parentheses, generate all combinations of well-formed strings.
- Total characters in any result string = 2 * n. [00:02:37]

-------------------------------------------------------------------------------------------
RECURSIVE INTUITION: [NEW]
1. The 2n Slots: We have 2n positions to fill.
2. Rule 1 (Open Limit): We can only use 'n' opening brackets. 
   - Constraint: If (open < n), we can still add '('. [00:28:43]
3. Rule 2 (Balance): We can only close a bracket if one is currently open.
   - Constraint: If (close < open), we can add ')'. [00:30:54]
4. Pruning: By following these rules, we never explore "invalid" paths (like starting 
   with ')' or having '())'), making the recursion significantly faster. [00:35:36]

-------------------------------------------------------------------------------------------
TIME & SPACE COMPLEXITY:
- Approach 1 (Brute): Generates all 2^(2n) combinations. Each string is validated 
  in O(n) time. Total: O(2^(2n) * n).
- Approach 2 (Smart): Generates only valid sequences. The number of valid sequences 
  is the n-th Catalan Number (~4^n / (n*sqrt(n))).
- Space: Both use O(n) for the recursion stack (depth of 2n). [00:37:26]
===========================================================================================
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<string> result;

    // --- APPROACH 1: BRUTE FORCE [00:14:18] ---
    bool isValid(string &str) {
        int count = 0;
        for (char &ch : str) {
            if (ch == '(') count++;
            else count--;
            if (count < 0) return false; // More ')' than '(' at some point
        }
        return count == 0;
    }

    void solveBrute(string& curr, int n) {
        if (curr.length() == 2 * n) {
            if (isValid(curr)) result.push_back(curr);
            return;
        }

        curr.push_back('(');
        solveBrute(curr, n);
        curr.pop_back(); // Backtrack

        curr.push_back(')');
        solveBrute(curr, n);
        curr.pop_back(); // Backtrack
    }

    // --- APPROACH 2: SMART BACKTRACKING (OPTIMIZED) [00:37:37] ---
    void solveSmart(string& curr, int n, int open, int close) {
        // Base Case: Reached maximum length 2n [01:14:35]
        if (curr.length() == 2 * n) {
            result.push_back(curr);
            return;
        }

        // Try adding '(' if we haven't used all n opens [00:33:37]
        if (open < n) {
            curr.push_back('(');
            solveSmart(curr, n, open + 1, close);
            curr.pop_back(); // Backtrack
        }

        // Try adding ')' if it won't exceed the current open count [00:34:21]
        if (close < open) {
            curr.push_back(')');
            solveSmart(curr, n, open, close + 1);
            curr.pop_back(); // Backtrack
        }
    }

    vector<string> generateParenthesis(int n) {
        result.clear();
        string curr = "";

        // Toggle Approach:
        // solveBrute(curr, n);
        solveSmart(curr, n, 0, 0);

        return result;
    }
};