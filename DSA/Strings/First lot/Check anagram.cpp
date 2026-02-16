https://leetcode.com/problems/valid-anagram/

/*
===========================================================================================
VALID ANAGRAM - COMPLETE GUIDE
===========================================================================================
Source: LeetCode 242 / CodeStoryWithMIK (YouTube)
Companies: Uber, Google, Amazon, Microsoft

-------------------------------------------------------------------------------------------
PROBLEM STATEMENT:
Given two strings `s` and `t`, return `true` if `t` is an anagram of `s`, and `false` otherwise.

An Anagram is a word or phrase formed by rearranging the letters of a different word or 
phrase, typically using all the original letters exactly once.

Example:
Input:  s = "anagram", t = "nagaram"
Output: true

Input:  s = "rat", t = "car"
Output: false

-------------------------------------------------------------------------------------------
APPROACH 1: Sorting (Brute Force)
Logic:
1. If two strings are anagrams, they must contain the exact same characters with the same 
   frequencies.
2. If we sort both strings, they should become identical.
3. Simply sort `s` and `t`, then compare them.

APPROACH 2: Frequency Counting (Optimized)
Logic:
1. Use an integer array of size 26 (for 'a'-'z') to store frequencies.
2. Increment the count for each character in `s`.
3. Decrement the count for each character in `t`.
4. If the strings are anagrams, every value in the frequency array must be exactly 0.
5. Use `all_of` or a simple loop to verify if all elements are zero.

-------------------------------------------------------------------------------------------
COMPLEXITY ANALYSIS:
-------------------------------------------------------------------------------------------
Approach         | Time Complexity | Space Complexity | Notes
-------------------------------------------------------------------------------------------
1. Sorting       | O(N log N)      | O(1)             | Depends on sorting implementation.
2. Counting      | O(N)            | O(1)             | Array size is fixed (26).
-------------------------------------------------------------------------------------------
===========================================================================================
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// --- APPROACH 1: Sorting ---
class Solution1 {
public:
    bool isAnagram(string s, string t) {
        // Base case: different lengths cannot be anagrams
        if (s.size() != t.size()) return false;

        sort(s.begin(), s.end());
        sort(t.begin(), t.end());

        return (s == t);
    }
};


// --- APPROACH 2: Frequency Counting (Hash Array) ---
class Solution2 {
public:
    bool isAnagram(string s, string t) {
        // Base case: different lengths cannot be anagrams
        if (s.size() != t.size()) return false;

        vector<int> count(26, 0);
        
        // Count characters in s
        for(char &ch : s) {
            count[ch - 'a']++;
        }

        // Subtract counts for characters in t
        for(char &ch : t) {
            count[ch - 'a']--;
        }

        // Check if all counts returned to zero
       /*
===========================================================================================
VALID ANAGRAM - COMPLETE GUIDE
===========================================================================================
Source: LeetCode 242 / CodeStoryWithMIK (YouTube)
Companies: Uber, Google, Amazon, Microsoft

-------------------------------------------------------------------------------------------
PROBLEM STATEMENT:
Given two strings `s` and `t`, return `true` if `t` is an anagram of `s`, and `false` otherwise.

An Anagram is a word or phrase formed by rearranging the letters of a different word or 
phrase, typically using all the original letters exactly once.

Example:
Input:  s = "anagram", t = "nagaram"
Output: true

Input:  s = "rat", t = "car"
Output: false

-------------------------------------------------------------------------------------------
APPROACH 1: Sorting (Brute Force)
Logic:
1. If two strings are anagrams, they must contain the exact same characters with the same 
   frequencies.
2. If we sort both strings, they should become identical.
3. Simply sort `s` and `t`, then compare them.

APPROACH 2: Frequency Counting (Optimized)
Logic:
1. Use an integer array of size 26 (for 'a'-'z') to store frequencies.
2. Increment the count for each character in `s`.
3. Decrement the count for each character in `t`.
4. If the strings are anagrams, every value in the frequency array must be exactly 0.
5. Use `all_of` or a simple loop to verify if all elements are zero.

-------------------------------------------------------------------------------------------
COMPLEXITY ANALYSIS:
-------------------------------------------------------------------------------------------
Approach         | Time Complexity | Space Complexity | Notes
-------------------------------------------------------------------------------------------
1. Sorting       | O(N log N)      | O(1)             | Depends on sorting implementation.
2. Counting      | O(N)            | O(1)             | Array size is fixed (26).
-------------------------------------------------------------------------------------------
===========================================================================================
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// --- APPROACH 1: Sorting ---
class Solution1 {
public:
    bool isAnagram(string s, string t) {
        // Base case: different lengths cannot be anagrams
        if (s.size() != t.size()) return false;

        sort(s.begin(), s.end());
        sort(t.begin(), t.end());

        return (s == t);
    }
};


// --- APPROACH 2: Frequency Counting (Hash Array) ---
class Solution2 {
public:
    bool isAnagram(string s, string t) {
        // Base case: different lengths cannot be anagrams
        if (s.size() != t.size()) return false;

        vector<int> count(26, 0);
        
        // Count characters in s
        for(char &ch : s) {
            count[ch - 'a']++;
        }

        // Subtract counts for characters in t
        for(char &ch : t) {
            count[ch - 'a']--;
        }

        // Check if all counts returned to zero
        bool allZeros = all_of(count.begin(), count.end(), [](int element) {
            return element == 0;
        });
        
        return allZeros;
    }
};

/*


all_of(start_iterator, end_iterator, condition)


vector<int> v = {2, 4, 6, 8};

bool res = all_of(v.begin(), v.end(), [](int x) {
    return x % 2 == 0;
});

output is true 
-------------------------------------------------------------------------------------------
FOLLOW-UP (Unicode Characters):
If the input contains Unicode characters, a fixed-size array of 26 won't work.
Solution: Use a Hash Map (unordered_map<char, int>) instead of a fixed-size array.
This would increase the space complexity to O(Number of unique characters).

For unicode array a 128 sized array would work easily : FACT
-------------------------------------------------------------------------------------------
DRY RUN (Approach 2):
s = "cat", t = "act"

1. Init count[26] = {0, 0, ...}
2. Process 's': 'c'++ (count[2]=1), 'a'++ (count[0]=1), 't'++ (count[19]=1)
3. Process 't': 'a'-- (count[0]=0), 'c'-- (count[2]=0), 't'-- (count[19]=0)
4. Check all zeros: All elements are 0.
Result: True
-------------------------------------------------------------------------------------------
*/
    }
};

/*
-------------------------------------------------------------------------------------------
FOLLOW-UP (Unicode Characters):
If the input contains Unicode characters, a fixed-size array of 26 won't work.
Solution: Use a Hash Map (unordered_map<char, int>) instead of a fixed-size array.
This would increase the space complexity to O(Number of unique characters).
-------------------------------------------------------------------------------------------
DRY RUN (Approach 2):
s = "cat", t = "act"

1. Init count[26] = {0, 0, ...}
2. Process 's': 'c'++ (count[2]=1), 'a'++ (count[0]=1), 't'++ (count[19]=1)
3. Process 't': 'a'-- (count[0]=0), 'c'-- (count[2]=0), 't'-- (count[19]=0)
4. Check all zeros: All elements are 0.
Result: True
-------------------------------------------------------------------------------------------
*/