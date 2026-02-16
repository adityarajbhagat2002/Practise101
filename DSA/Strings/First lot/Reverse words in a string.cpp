https://leetcode.com/problems/reverse-words-in-a-string/description/

/*
===========================================================================================
REVERSE WORDS IN A STRING - COMPLETE GUIDE
===========================================================================================
Problem Name: 151. Reverse Words in a String
Difficulty: Medium
Companies: Amazon, Microsoft, MentorGraphics, MakeMyTrip, Google

-------------------------------------------------------------------------------------------
Problem Statement:
Given an input string 's', reverse the order of the words.
- A word is a sequence of non-space characters.
- Words are separated by at least one space.
- 's' may contain leading, trailing, or multiple spaces between words.
- Result should have only a single space between words and no extra spaces.

Example:
Input:  "  the sky  is blue "
Output: "blue is sky the"

-------------------------------------------------------------------------------------------
APPROACH 1: Using StringStream (The Tokenization Method)
Logic: 
1. Use `stringstream` to extract words. It automatically treats spaces as delimiters.
2. Read words one by one.
3. Prepend the new word to the front of the result string: `result = currentWord + " " + result`.
4. Trim the final trailing space.

APPROACH 2: Two-Pointer In-Place (The Optimal Method)
Logic:
1. Reverse the entire string: This puts words in the right order but characters in the wrong order.
2. Traverse the string and find words using pointers.
3. Reverse each word individually to restore correct character order.
4. Use a "right Pointer" (`r`) to shift words left and remove extra spaces.
5. Resize/Substr to the final length of `r`.

-------------------------------------------------------------------------------------------
COMPLEXITY ANALYSIS:
-------------------------------------------------------------------------------------------
Approach         | Time Complexity | Space Complexity | Notes
-------------------------------------------------------------------------------------------
1. StringStream  | O(N)            | O(N)             | Uses O(N) extra buffer space.
2. Two-Pointer   | O(N)            | O(1)             | O(1) in C++ (In-place modification).
-------------------------------------------------------------------------------------------
*Note: Space is O(1) in C++ because strings are mutable. In Java/Python, it's O(N).
===========================================================================================
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>

using namespace std;

class Solution {
public:
    // --- APPROACH 1: StringStream Implementation ---
    string reverseWords_Approach1(string s) {
        stringstream ss(s);
        string word;
        string result = "";

        while (ss >> word) {
            if (result == "") {
                result = word;
            } else {
                // Prepend word to reverse the sequence
                result = word + " " + result;
            }
        }
        return result;
    }

    // --- APPROACH 2: Optimal Two-Pointer In-Place (Your Implementation) ---
    string reverseWords(string s) {
        // Step 1: Reverse the whole string
        reverse(s.begin(), s.end());

        int i = 0;      // Read pointer
        int l = 0;      // Left pointer (start of word)
        int r = 0;      // Write pointer
        int n = s.length();

        while (i < n) {
            // Find a word (skip spaces)
            while (i < n && s[i] == ' ') i++;
            
            if (i >= n) break; 

            // Copy word to the 'r' position
            while (i < n && s[i] != ' ') {
                s[r] = s[i];
                r++;
                i++;
            }

            // Step 2: Reverse the current word to fix character order
            if (l < r) {
                reverse(s.begin() + l, s.begin() + r);
                
                // Add a space after the word
                s[r] = ' ';
                r++;
                l = r; // Update start for next word
            } 
            i++;
        }

        // Step 3: Trim the result
        if (r > 0) {
            s = s.substr(0, r - 1);
        } else {
            s = "";
        }
        
        return s;
    }
};

/*
-------------------------------------------------------------------------------------------
DRY RUN (Approach 2):
Input: "  hello world  "

1. Reverse All: 
   "  dlrow olleh  "

2. Finding "dlrow":
   - Read 'd','l','r','o','w'. Write to s[0..4].
   - Reverse s[0..4] -> "world"
   - Add space at s[5] -> "world "
   - Set l = 6, r = 6

3. Finding "olleh":
   - Read 'o','l','l','e','h'. Write to s[6..10].
   - Reverse s[6..10] -> "hello"
   - Add space at s[11] -> "world hello "
   - Set l = 12, r = 12

4. Final Cleanup:
   - r = 12. Return s.substr(0, 11).
   - Output: "world hello"
-------------------------------------------------------------------------------------------
*/