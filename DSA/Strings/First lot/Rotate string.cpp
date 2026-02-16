https://leetcode.com/problems/rotate-string/description/



/*
===========================================================================================
ROTATE STRING - COMPLETE GUIDE
===========================================================================================
Source: LeetCode 796 / CodeStoryWithMIK (YouTube)
Companies: Amazon, Microsoft, Google, Adobe

-------------------------------------------------------------------------------------------
PROBLEM STATEMENT:
Given two strings `s` and `goal`, return `true` if and only if `s` can become `goal` after 
some number of shifts on `s`.

A shift consists of moving the leftmost character of `s` to the rightmost position.
Example: s = "abcde" -> "bcdea" (1st shift) -> "cdeab" (2nd shift)

-------------------------------------------------------------------------------------------
APPROACH 1: Brute Force (Simulation)
Logic:
1. Check if lengths are equal. If not, return false.
2. Rotate the string `s` one character at a time using `std::rotate`.
3. After each shift, compare the result with `goal`.
4. If they match at any point, return true.
              rotate(start, middle, end)
              rotate(A, A+1, A+n)



APPROACH 2: Concatenation Trick (Optimized)
Logic:
1. If we concatenate `s` with itself (`s + s`), the new string contains ALL possible 
   rotations of `s` as substrings.
2. Example: s = "abcde", s+s = "abcdeabcde"
   "cdeab" is clearly visible inside "ab(cdeab)cde".
3. Simply check if `goal` is a substring of `s + s` using `.find()`.


🧠 What is rotate()?

rotate() rearranges elements in a range.

Syntax:
rotate(first, middle, last);


It rotates the range:

[first, last)


so that:

middle becomes the new first


👉 string::find() returns an index (number), not an iterator — it returns string::npos when the substring is not found.

Or even simpler:

👉 Use != string::npos to check string find(), not .end() like maps.

(That’s the key distinction 👍)

-------------------------------------------------------------------------------------------
COMPLEXITY ANALYSIS:
-------------------------------------------------------------------------------------------
Approach         | Time Complexity | Space Complexity | Notes
-------------------------------------------------------------------------------------------
1. Brute Force   | O(N^2)          | O(1)             | N shifts * O(N) string comparison.
2. Concatenation | O(N)            | O(N)             | String search is generally O(N).
-------------------------------------------------------------------------------------------
===========================================================================================
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// --- APPROACH 1: Brute Force ---
class Solution1 {
public:
    bool rotateString(string s, string goal) {
        int n = s.size();
        int m = goal.size();

        if (m != n) return false;

        // Perform rotation m times (length of string)
        for (int count = 0; count < m; count++) {
            // Rotates the string by 1 position to the left
            rotate(s.begin(), s.begin() + 1, s.end());

            if (s == goal) return true;
        }

        return false;
    }
};

// --- APPROACH 2: Concatenation Trick ---
class Solution2 {
public:
    bool rotateString(string s, string goal) {
        // Essential Check: Rotations must preserve length
        if (s.length() != goal.length()) {
            return false;
        }

        // Check if goal exists as a substring in (s + s)
        if ((s + s).find(goal) != string::npos) {
            return true;
        }

        return false;
    }
};

/*
-------------------------------------------------------------------------------------------
DRY RUN (Approach 2):
Input: s = "abcde", goal = "cdeab"

1. Length: s(5), goal(5) -> Matches.
2. Combined String: "abcdeabcde"
3. Searching for "cdeab":
   "a b [c d e a b] c d e"
         ^ Found at index 2
4. result != string::npos -> TRUE
-------------------------------------------------------------------------------------------
*/