https://leetcode.com/problems/roman-to-integer/description/


/*
===========================================================================================
ROMAN TO INTEGER - COMPLETE GUIDE
===========================================================================================
Source: LeetCode 13
Companies: Amazon, Apple, Microsoft, Bloomberg

-------------------------------------------------------------------------------------------
PROBLEM STATEMENT:
Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.
Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000

Roman numerals are usually written largest to smallest from left to right. However, 
the numeral for four is not IIII. Instead, it is IV (one before five). 
This same principle applies to 9 (IX), 40 (XL), 90 (XC), 400 (CD) and 900 (CM).

Example:
Input:  s = "LVIII"
Output: 58 (L=50, V=5, III=3)

Input:  s = "MCMXCIV"
Output: 1994 (M=1000, CM=900, XC=90, IV=4)

-------------------------------------------------------------------------------------------
APPROACH: Backward Traversal (Right to Left)
Logic:
1. Map all Roman characters to their corresponding integer values using a Hash Map.
2. Initialize `sum` with the value of the last character of the string.
3. Iterate through the string from the second-to-last character down to the first (right to left).
4. **Subtraction Rule:** If the current character's value is **smaller** than the character 
   to its right, subtract it from the total sum (e.g., in IV, I < V, so sum = 5 - 1 = 4).
5. **Addition Rule:** If the current character's value is **greater than or equal** to the 
   character to its right, add it to the sum (e.g., in VI, V > I, so sum = 1 + 5 = 6).

-------------------------------------------------------------------------------------------
COMPLEXITY ANALYSIS:
-------------------------------------------------------------------------------------------
Approach         | Time Complexity | Space Complexity | Notes
-------------------------------------------------------------------------------------------
Right-to-Left    | O(N)            | O(1)             | Single pass. Map size is fixed (7).
-------------------------------------------------------------------------------------------
===========================================================================================
*/

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int romanToInt(string s) {
        unordered_map<char, int> mp;

        // Roman numeral mapping
        mp = {
            {'I', 1},
            {'V', 5},
            {'X', 10},
            {'L', 50},
            {'C', 100},
            {'D', 500},
            {'M', 1000}
        };

        // Initialize sum with the last character
        int sum = mp[s.back()];

        // Traverse backwards from the second last element
        for (int i = s.size() - 2; i >= 0; i--) {
            // If current value is less than the value to its right
            if (mp[s[i]] < mp[s[i + 1]]) {
                sum = sum - mp[s[i]];
            } 
            // Otherwise, add it
            else {
                sum = sum + mp[s[i]];
            }
        }

        return sum;
    }
};

/*
-------------------------------------------------------------------------------------------
DRY RUN:
Input: s = "IV"

1. mp = {'I':1, 'V':5}
2. sum = mp['V'] = 5
3. Loop i = 0 (char 'I'):
   - mp['I'] (1) < mp['V'] (5) is TRUE.
   - sum = sum - 1 => 5 - 1 = 4
4. Loop ends.
Result: 4

Input: s = "MCMXCIV"
Char (Right to Left): V(5), I(1<5), C(100), X(10<100), M(1000), C(100<1000), M(1000)
Sum Calculation: 5 - 1 + 100 - 10 + 1000 - 100 + 1000 = 1994
-------------------------------------------------------------------------------------------
*/