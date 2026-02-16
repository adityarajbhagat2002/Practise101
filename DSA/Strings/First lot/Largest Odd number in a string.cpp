https://leetcode.com/problems/largest-odd-number-in-string/description/

/*
===========================================================================================
LARGEST ODD NUMBER IN STRING - COMPLETE GUIDE
===========================================================================================
Source: LeetCode 1903 / CodeStoryWithMIK (YouTube)
Companies: Amazon (Phone Interview / Initial Rounds)

-------------------------------------------------------------------------------------------
PROBLEM STATEMENT:
Given a string `num` representing a large integer, return the largest-valued odd integer 
(as a string) that is a non-empty substring of `num`, or an empty string "" if no odd 
integer exists.

Key Definitions:
- A substring is a contiguous sequence of characters within a string.
- An integer is odd if its last digit is odd (1, 3, 5, 7, 9).
- To maximize the value, we need the longest substring that ends in an odd digit.

Example:
Input:  "35427"
Process: 
- Scan from right. '7' is the first odd digit found.
- The largest odd substring starts from the beginning up to '7'.
Output: "35427"

Input:  "4206"
Output: "" (No odd digits present)
-------------------------------------------------------------------------------------------

APPROACH 1: Right-to-Left Linear Scan
Logic & Intuition:
1. Any number's "odd-ness" is determined solely by its last digit.
2. To get the LARGEST odd number, we should keep as many leading digits as possible.
3. Therefore, the moment we find an odd digit while scanning from the RIGHT, we know that 
   the substring from index 0 to that digit is the largest possible odd number.
4. We don't need to check further left because any other odd number found later would 
   be a shorter substring, hence smaller in value.

-------------------------------------------------------------------------------------------
COMPLEXITY ANALYSIS:
-------------------------------------------------------------------------------------------
Approach         | Time Complexity | Space Complexity | Notes
-------------------------------------------------------------------------------------------
1. Linear Scan   | O(N)            | O(1)* | N is string length.
-------------------------------------------------------------------------------------------
*Note: Auxiliary space is O(1). The space for the result substring is O(N).

===========================================================================================
*/

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    string largestOddNumber(string num) {
        int n = num.length();
        
        // Start from the end of the string (right to left)
        for (int i = n - 1; i >= 0; i--) {
            
            // Check if character at index i is an odd digit
            // Subtract '0' to convert char to its integer value
            if ((num[i] - '0') % 2 != 0) {
                
                // If odd, the largest odd number is from index 0 to i
                // substr(start_index, length) -> length is i + 1
                return num.substr(0, i + 1);
            }
        }
        
        // If the loop finishes without finding an odd digit
        return "";
    }
};

/*
-------------------------------------------------------------------------------------------
DRY RUN EXAMPLE:
Input: "3542"

Char | Index | (num[i]-'0')%2 != 0 | Action
-------------------------------------------------------------------------------------------
'2'  |   3   | (2 % 2 != 0) -> False| Continue
'4'  |   2   | (4 % 2 != 0) -> False| Continue
'5'  |   1   | (5 % 2 != 0) -> True | FOUND! Return num.substr(0, 1+1)
-------------------------------------------------------------------------------------------
Result: "35"
-------------------------------------------------------------------------------------------
*/