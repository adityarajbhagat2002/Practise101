https://leetcode.com/problems/isomorphic-strings/description/
/*
===========================================================================================
ISOMORPHIC STRINGS - COMPLETE GUIDE
===========================================================================================
Source: LeetCode 205 / CodeStoryWithMIK (YouTube)
Companies: LinkedIn, Amazon, Google, Uber

-------------------------------------------------------------------------------------------
PROBLEM STATEMENT:
Given two strings `s` and `t`, determine if they are isomorphic.
Two strings `s` and `t` are isomorphic if the characters in `s` can be replaced to get `t`.

Rules:
1. All occurrences of a character must be replaced with another character.
2. No two characters may map to the same character (Bijective mapping).
3. A character can map to itself.
4. The order of characters must be preserved.

Example:
Input:  s = "egg", t = "add"
Output: true (e -> a, g -> d)

Input:  s = "foo", t = "bar"
Output: false (f -> b, o -> a, but then 'o' cannot map to 'r' because it's already mapped to 'a')

-------------------------------------------------------------------------------------------
APPROACH: Double Mapping (Using Two Hash Maps)
Logic:
- We need to ensure a "one-to-one" relationship between characters of `s` and `t`.
- map1: Stores mapping from `s[i] -> t[i]`.
- map2: Stores mapping from `t[i] -> s[i]`.
- As we iterate through the strings:
    1. If `s[i]` was already mapped to something other than `t[i]`, return false.
    2. If `t[i]` was already mapped to something other than `s[i]`, return false.
- Why two maps? To prevent two different characters from `s` mapping to the same character in `t` 
  (e.g., s="ab", t="aa"). 

-------------------------------------------------------------------------------------------
COMPLEXITY ANALYSIS:
-------------------------------------------------------------------------------------------
Approach         | Time Complexity | Space Complexity | Notes
-------------------------------------------------------------------------------------------
Double Mapping   | O(N)            | O(1)             | We traverse the string once. 
                                                        Space is O(256) which is constant.
-------------------------------------------------------------------------------------------
===========================================================================================
*/

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        // map1 stores mapping of characters from s to t
        unordered_map<char,char> map1;
        // map2 stores mapping of characters from t to s
        unordered_map<char,char> map2;

        int n = s.size();

        for(int i = 0; i < n; i++){
            char ch1 = s[i];
            char ch2 = t[i];

            // If ch1 is already mapped and its mapping is not ch2
            // OR if ch2 is already mapped and its mapping is not ch1
            if((map1.find(ch1) != map1.end() && map1[ch1] != ch2) ||
               (map2.find(ch2) != map2.end() && map2[ch2] != ch1)){
                return false;
            }

            // Establish the bidirectional mapping
            map1[ch1] = ch2;
            map2[ch2] = ch1;
        }

        return true;
    }
};

/*
-------------------------------------------------------------------------------------------
DRY RUN EXAMPLE:
Input: s = "foo", t = "bar"

Index | ch1 (s) | ch2 (t) | map1 (s->t) | map2 (t->s) | Action
-------------------------------------------------------------------------------------------
0     |   'f'   |   'b'   | {'f': 'b'}  | {'b': 'f'}  | Map f <-> b
1     |   'o'   |   'a'   | {'o': 'a'}  | {'a': 'o'}  | Map o <-> a
2     |   'o'   |   'r'   | map1['o']=a |             | Conflict! (a != r)
-------------------------------------------------------------------------------------------
Result: False
-------------------------------------------------------------------------------------------
*/