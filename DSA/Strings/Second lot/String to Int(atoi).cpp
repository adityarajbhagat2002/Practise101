https://leetcode.com/problems/string-to-integer-atoi/description/

/*
===========================================================
String to Integer (atoi) - Complete Guide
===========================================================

Problem Name:
8. String to Integer (atoi)

Problem Statement:
Implement the function `myAtoi(string s)` which converts a string 
to a 32-bit signed integer (similar to C/C++’s `atoi` function).

The conversion should follow this algorithm:
1. Ignore any leading whitespace.
2. Check for an optional sign (‘-’ or ‘+’).
3. Read digits until a non-digit character or end of string.
4. Convert those digits into an integer.
5. Clamp the result within the 32-bit signed integer range [-2^31, 2^31-1].
6. Return the final integer.
  
Constraints:
- Only the space character ' ' is considered whitespace.
- If no valid conversion can be performed, return 0.
- If the integer is out of bounds, clamp to INT_MIN or INT_MAX.

Examples:
Input: s = "42"
Output: 42

Input: s = "   -42"
Output: -42

Input: s = "4193 with words"
Output: 4193

Input: s = "words and 987"
Output: 0

Input: s = "-91283472332"
Output: -2147483648

References:
Algorithm rules explained in problem description :contentReference[oaicite:0]{index=0}

-----------------------------------------------------------

Key Insight:
- Read characters sequentially from left to right.
- Stop parsing when hitting a non-digit after optional sign.
- Before converting digit by digit, handle overflow by checking
  if multiplication by 10 + digit would exceed INT limits.
- Perform clamping to INT_MIN or INT_MAX if overflow detected.

-----------------------------------------------------------

Logic & Intuition:
1. Skip all leading whitespace.
2. Detect sign (+ or -). Default is positive.
3. Parse digits and build the number.
4. Check for overflow on the fly:
   - If result > INT_MAX/10, next multiplication will overflow.
   - If result == INT_MAX/10 and next digit > 7 (or >8 if negative),
     then adding it will overflow.
5. Multiply with sign and return.

-----------------------------------------------------------

Time Complexity:
O(n), where n = length of string.

Space Complexity:
O(1), only a few variables are used.

Good one 👍 — isdigit() is a built-in C/C++ function that checks whether a character is a numeric digit (0–9).

-----------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int myAtoi(string s) {
        int n = s.size();
        int i = 0;

        // 1. Skip leading whitespaces
        while (i < n && s[i] == ' ') {
            i++;
        }

        // If string has only spaces
        if (i == n) return 0;

        // 2. Handle optional sign
        int sign = 1;
        if (s[i] == '-' || s[i] == '+') {
            if (s[i] == '-') sign = -1;
            i++;
        }

        // 3. Convert characters to number
        int result = 0;
        while (i < n && isdigit(s[i])) {
            int digit = s[i] - '0';

            // 4. Handle overflow preemptively
            if (result > INT_MAX / 10 ||
                (result == INT_MAX / 10 && digit > INT_MAX % 10)) {
                return (sign == 1) ? INT_MAX : INT_MIN;
            }

            result = result * 10 + digit;
            i++;
        }

        // 5. Apply sign
        return result * sign;
    }
};
