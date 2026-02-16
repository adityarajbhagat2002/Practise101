https://leetcode.com/problems/longest-substring-without-repeating-characters/description/


/*
===========================================================================================
TOPIC: TWO POINTERS & SLIDING WINDOW
PROBLEM: LONGEST SUBSTRING WITHOUT REPEATING CHARACTERS
===========================================================================================
Source: take U forward (Striver - L3)
Pattern: Sliding Window (Variable Size) + Hashing for "Jumping" Optimization
Complexity: 
- Time: O(n)     -> Each character is visited once by the right pointer.
- Space: O(256) -> To store indices of 256 possible ASCII characters.

-------------------------------------------------------------------------------------------
WINDOW INTUITION: THE "NON-REPEATING" CONSTRAINT
- Constraint: Every character in our window [left, right] must be unique.
- Expansion: Move the 'right' pointer forward to explore longer substrings. [00:11:04]
- Violation: If cardPoints[right] is already in our hash table, it means we have a duplicate.
- Optimized Contraction (The "Jump"):
    - Normally, we'd move 'left' one by one until the duplicate is gone.
    - Optimization: Jump 'left' directly to (Last_Seen_Index + 1). [00:14:16]
    - Safety Check: Only jump if the last seen index is INSIDE our current window. [00:16:34]

-------------------------------------------------------------------------------------------
POINTER COORDINATION:
- Right Pointer (r): Scans through the string character by character. [00:19:12]
- Left Pointer (l): Jumps forward only when a character repeats within the current window.
- Hash Array: Stores the last recorded index of every character encountered.
===========================================================================================
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.size();

        // 1. Initialize Hash Array for 256 ASCII characters [00:18:35]
        // We use -1 to indicate we haven't seen the character yet.
        int hash[256];
        for (int i = 0; i < 256; i++) {
            hash[i] = -1;
        }

        int left = 0, right = 0, maxlen = 0;

        // 2. Expand the Window with the 'right' pointer [00:19:21]
        while (right < n) {
            // If the character was seen before
            if (hash[s[right]] != -1) {
                // IMPORTANT: Only jump 'left' if the character is within our active window
                // This prevents 'left' from moving backward. [00:16:34]
                if (hash[s[right]] >= left) {
                    left = hash[s[right]] + 1;
                }
            }

            // Calculate current valid window size [00:20:52]
            int len = (right - left + 1);
            maxlen = max(maxlen, len);

            // Record/Update the character's last seen index
            hash[s[right]] = right;
            
            // Move right to next character [00:21:15]
            right++;
        }

        return maxlen;
    }
};

/*
-------------------------------------------------------------------------------------------
DRY RUN EXAMPLE (s = "abcabcbb"):
-------------------------------------------------------------------------------------------
- r=0 ('a'): hash['a']=-1. maxlen=1. hash['a']=0.
- r=1 ('b'): hash['b']=-1. maxlen=2. hash['b']=1.
- r=2 ('c'): hash['c']=-1. maxlen=3. hash['c']=2.
- r=3 ('a'): hash['a']=0 (>= left 0). JUMP left = 0+1=1. maxlen=3. hash['a']=3.
- r=4 ('b'): hash['b']=1 (>= left 1). JUMP left = 1+1=2. maxlen=3. hash['b']=4.
- r=5 ('c'): hash['c']=2 (>= left 2). JUMP left = 2+1=3. maxlen=3. hash['c']=5.
Final Result: 3
-------------------------------------------------------------------------------------------
*/