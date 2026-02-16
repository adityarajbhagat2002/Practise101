https://www.geeksforgeeks.org/problems/longest-k-unique-characters-substring0853/1


/*
===========================================================================================
PROBLEM: LONGEST K UNIQUE CHARACTERS SUBSTRING (GeeksforGeeks)
===========================================================================================

-------------------------------------------------------------------------------------------
1. LOGIC AND INTUITION:
-------------------------------------------------------------------------------------------
The goal is to find the longest substring that contains EXACTLY 'k' distinct characters.
Note: Striver's video (L6) explains "At Most K", but the "Exactly K" problem is solved 
using the same sliding window logic with a small modification in the result update. [00:01:19]

- Brute Force: Generate all substrings. Use a Set/Map to count unique characters. 
  If count == k, update maxLen. [00:03:06]
- Better (Sliding Window): Use two pointers. If unique characters > k, shrink 'left' 
  pointer using a 'while' loop until count == k. [00:15:53]
- Optimal (Sliding Window): Instead of a 'while' loop, use an 'if'. If count > k, 
  shift 'left' once. This ensures the window size never shrinks below the max found. [00:20:43]

-------------------------------------------------------------------------------------------
2. EDGE CASES:
-------------------------------------------------------------------------------------------
- k > total unique characters in string: The problem requires "exactly k", so return -1.
- String length < k: Return -1.
- k = 0: Not possible per constraints, but logically 0 or -1.

-------------------------------------------------------------------------------------------
3. STEPS (OPTIMAL APPROACH):
-------------------------------------------------------------------------------------------
1. Initialize `left = 0`, `right = 0`, `maxlen = -1`, and `unordered_map<char, int> mpp`.
2. Expand the window by moving `right` from 0 to n-1.
3. Add `s[right]` to the map.
4. If `mpp.size() > k`: (Invalid state - more than k distinct characters) [00:20:57]
    - Decrease frequency of `s[left]`.
    - If frequency becomes 0, remove the character from the map.
    - Increment `left` once to "slide" the window.
5. If `mpp.size() == k`: (Valid state - exactly k distinct characters)
    - Update `maxlen = max(maxlen, right - left + 1)`.
6. Return `maxlen`.

-------------------------------------------------------------------------------------------
4. WHY IT WORKS (THE "NON-SHRINKING" LOGIC):
-------------------------------------------------------------------------------------------
In the optimal approach, once we find a valid window of size 'X', we don't want to 
look at windows smaller than 'X'. By moving 'left' only once when invalid, we maintain 
that "at least X" size. If a larger valid window is found later, `maxlen` updates. [00:18:40]

-------------------------------------------------------------------------------------------
5. SPACE AND TIME COMPLEXITY:
-------------------------------------------------------------------------------------------
| Approach    | Time Complexity | Space Complexity |
| :---------- | :-------------- | :--------------- |
| Brute Force | O(N^2)          | O(256) ≈ O(1)    |
| Better      | O(2N)           | O(256) ≈ O(1)    |
| Optimal     | O(N)            | O(256) ≈ O(1)    |
Note: Space is O(1) because the map size is capped at 256 characters. [00:05:37]

-------------------------------------------------------------------------------------------
6. CODE (OPTIMAL IMPLEMENTATION):
-------------------------------------------------------------------------------------------
*/

#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int longestKSubstr(string s, int k) {
        int n = s.size();
        int left = 0, right = 0, maxlen = -1; // -1 handles the "not found" case
        unordered_map<char, int> mpp;

        while (right < n) {
            // Include current character [00:12:16]
            mpp[s[right]]++;

            // Optimal Shift: If unique characters > k, shift left ONCE [00:20:57]
            if (mpp.size() > k) {
                mpp[s[left]]--;
                if (mpp[s[left]] == 0) {
                    mpp.erase(s[left]);
                }
                left++;
            }

            // Update result only if window has EXACTLY k unique characters
            if (mpp.size() == k) {
                maxlen = max(maxlen, right - left + 1);
            }

            right++;
        }
        return maxlen;
    }
};

/*
-------------------------------------------------------------------------------------------
7. EXTRA NOTES:
-------------------------------------------------------------------------------------------
- Difference between "At Most K" and "Exactly K":
  Striver's L6 video primarily discusses "At Most K". For "Exactly K", we only 
  update the result when `mpp.size() == k`, and initialize `maxlen` to -1 to 
  signal if no such substring was ever found. [00:13:50]
===========================================================================================
*/