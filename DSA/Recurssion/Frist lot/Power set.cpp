/*
===========================================================================================
POWER SET - ALL POSSIBLE SUBSEQUENCES
===========================================================================================
Source: CodeStoryWithMIK / GFG
Concept: Backtracking / Pick & Non-Pick Pattern
Complexity: 
- Time: O(2^n) to generate, plus O(2^n * log(2^n)) for final sorting.
- Space: O(n) [Recursion stack depth].

-------------------------------------------------------------------------------------------
PROBLEM DESCRIPTION:
- Given a string 's', find all possible subsequences in lexicographical order.
- A subsequence is formed by deleting zero or more characters from the original string.
- Example: "abc" -> ["a", "ab", "abc", "ac", "b", "bc", "c"]

-------------------------------------------------------------------------------------------
RECURSIVE INTUITION: [NEW]
1. Binary Choice: For every character in the string, we have exactly two options:
   - Include it: Add character to current string and move to next index.
   - Exclude it: Don't add character and move to next index.
2. The 2^n Factor: Since every character (total n) has 2 choices, we branch out 
   2 * 2 * 2... (n times), resulting in 2^n total leaf nodes in our recursion tree.
3. Leaf Nodes: Each leaf node in the recursion tree represents one unique subsequence.

-------------------------------------------------------------------------------------------
THE BACKTRACKING STORY:
1. Base Case: If (idx >= s.size()), we've reached the end of the input string.
   - If 'curr' is not empty, add it to our result.
2. Pick (Include): 
   - Add s[idx] to 'curr' -> solve(idx + 1) -> pop_back (Backtrack).
3. Non-Pick (Exclude): 
   - Simply call solve(idx + 1) without adding the character.
4. Sorting: GFG requires lexicographical order, so we sort the final result list.
===========================================================================================
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<string> result;

    void solve(string &s, string &curr, int idx) {
        // 1. Base Case: No more characters to process
        if (idx >= s.size()) {
            if (curr != "") {
                result.push_back(curr);
            }
            return;
        }

        // 2. Choice 1: INCLUDE s[idx] in the current subsequence
        curr.push_back(s[idx]);
        solve(s, curr, idx + 1);
        
        // 3. Backtrack: Remove s[idx] to explore the "Exclude" path
        curr.pop_back();

        // 4. Choice 2: EXCLUDE s[idx] from the current subsequence
        solve(s, curr, idx + 1);
    }

    vector<string> AllPossibleStrings(string s) {
        result.clear();
        string curr = "";

        solve(s, curr, 0);

        // Required by GFG for lexicographical order
        sort(result.begin(), result.end());
        
        return result;
    }
};