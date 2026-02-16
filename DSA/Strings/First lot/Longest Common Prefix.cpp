https://leetcode.com/problems/longest-common-prefix/description/

/*
===========================================================================================
LONGEST COMMON PREFIX - COMPLETE GUIDE
===========================================================================================
Source: LeetCode 14 / The Tech Coders (YouTube)
Companies: Amazon, Google, Adobe, Microsoft

-------------------------------------------------------------------------------------------
PROBLEM STATEMENT:
Write a function to find the longest common prefix string amongst an array of strings.
If there is no common prefix, return an empty string "".

Example:
Input:  strs = ["flower","flow","flight"]
Output: "fl"

-------------------------------------------------------------------------------------------
APPROACH 1: Vertical Scanning
Logic:
- We iterate through the characters of the first string (index `i`).
- For every character, we check all other strings at that same position `i`.
- If we find a mismatch between any two adjacent strings (`strs[j]` and `strs[j+1]`), 
  it means the commonality ends there.
- This approach is efficient because it stops as soon as it finds a mismatch.

APPROACH 2: Sorting Method
Logic:
- We sort the array of strings lexicographically.
- Sorting ensures that the most different strings (in terms of characters) are placed 
  at the two ends: the first index (`strs[0]`) and the last index (`strs[strs.size()-1]`).
- Any prefix common to both the first and the last string must be common to all 
  strings in between because they are sorted.
- We only need to compare these two strings.

-------------------------------------------------------------------------------------------
COMPLEXITY ANALYSIS:
-------------------------------------------------------------------------------------------
Approach         | Time Complexity           | Space Complexity | Notes
-------------------------------------------------------------------------------------------
1. Vertical Scan | O(S)                      | O(1)             | S = sum of all chars.
2. Sorting       | O(N * logN * M)           | O(1)             | N = # strs, M = length.
-------------------------------------------------------------------------------------------
===========================================================================================
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// --- APPROACH 1: Vertical Scanning ---
class VerticalScanning {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string ans="";
        for(int i=0;i<strs[0].size();i++){
            for(int j=0;j<strs.size()-1;j++){
                // If character mismatch, return current ans
                if(strs[j][i]!=strs[j+1][i]) return ans;
            }
            ans+=strs[0][i];
        }
        return ans;
    }
};



// --- APPROACH 2: Sorting Method ---
class SortingMethod {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string ans="";
        // Sort the strings lexicographically
        sort(strs.begin(),strs.end());
        
        int i=0;
        // Compare only the first and last string in the sorted array
        while(i<strs[0].size() && strs[0][i]==strs[strs.size()-1][i]){
            ans+=strs[0][i];
            i++;
        }

        return ans;
    }
};

/*
-------------------------------------------------------------------------------------------
DRY RUN (Approach 2):
Input: ["flower", "flow", "flight"]

1. Initial: ["flower", "flow", "flight"]
2. After sort(): ["flight", "flow", "flower"]
3. strs[0] = "flight", strs[last] = "flower"
4. Comparison Loop:
   - i=0: 'f' == 'f' (Match) -> ans = "f"
   - i=1: 'l' == 'l' (Match) -> ans = "fl"
   - i=2: 'i' == 'o' (Mismatch) -> Exit Loop
5. Return "fl"
-------------------------------------------------------------------------------------------
*/