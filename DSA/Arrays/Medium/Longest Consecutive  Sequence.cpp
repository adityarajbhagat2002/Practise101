https://leetcode.com/problems/longest-consecutive-sequence/description/

// ****************************************************************************************
// Problem: Longest Consecutive Sequence (LeetCode 128)
// Language: C++
// Approach: Better Approach using Sorting
// ****************************************************************************************

/*
Problem Statement:
------------------
Given an unsorted array of integers, find the length of the longest consecutive elements sequence.
A consecutive sequence is a set of numbers that can be arranged as [x, x+1, x+2, ..., y], with no duplicates needed.
Return the length of the longest such sequence.

---

Brute Force Approach:
---------------------
Intuition:
- For every element, check if it starts a sequence (keep searching for next numbers using linear scan).
- For every number, try to build the longest streak by repeatedly checking (using another for loop) if nums[i]+1, nums[i]+2, ... exist in the array.
- Each of these checks is O(n), so total is O(n^2).

Steps:
1. Set 'longest' = 1.
2. For every index i from 0 to n-1:
    - Set count = 1, curr = nums[i].
    - For every next number, scan again for curr + 1. If found, increment count and curr.
    - Update longest = max(longest, count).
3. Return longest.

Complexity:
- Time: O(n^2) due to nested searches.
- Space: O(1).

---

Better Approach (with Sorting):
-------------------------------
Intuition:
- If the array is **sorted**, consecutive numbers appear next to each other.
- By walking through the sorted array, we can efficiently count streaks, skipping duplicates.
- Whenever we see nums[i] - 1 == lastsmallest, it means the streak continues.
- If nums[i] == lastsmallest, skip duplicate (don't count).
- Otherwise, reset count to 1 (start a new streak).
- Always update the longest streak as we go.

Steps:
1. Sort the array.
2. If it's empty, return 0.
3. Initialize count = 0, lastsmallest = INT_MIN, longest = 1. Let n = nums.size().
4. For each number:
    - If nums[i] - 1 == lastsmallest: increment count, update lastsmallest.
    - Else if nums[i] != lastsmallest: reset count to 1, update lastsmallest.
    - Update longest = max(longest, count).
5. Return longest.

Complexity:
- Time: O(n log n) for sort + O(n) for loop.
- Space: O(1) if sort in-place; otherwise, depends if sorting copy.

---

Example Dry Run:
----------------
Input: [100, 4, 200, 1, 3, 2]
- After sort: [1, 2, 3, 4, 100, 200]
- Streak: 1→2→3→4 (length 4), 100 (length 1), 200 (length 1)
- Max streak: 4

Handles duplicates:
Input: [1, 2, 2, 3]
- After sort: [1, 2, 2, 3]
- Streak: 1→2→3 (length 3) (skip duplicate 2)

---

Code Implementation:
--------------------
*/

#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        if (nums.empty()) return 0;
        
        int count = 0;
        int lastsmallest = INT_MIN;
        int longest = 1;
        int n = nums.size();

        for (int i = 0; i < n; i++) {
            if (nums[i] - 1 == lastsmallest) {
                count++;
                lastsmallest = nums[i];
            } else if (nums[i] != lastsmallest) {
                count = 1;
                lastsmallest = nums[i];
            }
            longest = max(longest, count);
        }
        return longest;
    }
};

/*
Summary:
- Brute force: for every number, repeatedly search for next consecutive numbers (O(n^2)).
- Better/sorting approach: 
    - Sort, then scan to count streaks (O(n log n)), skip duplicates.
    - Efficient, simple, and in-place.
- Optimal (hashset) approach is O(n) — ask for it when you want to add that.




Optimal Approach (Unordered Set / Hash Set, O(n)):
-------------------------------------------------
Intuition:
- The only numbers to start counting from are those that don't have a predecessor present (i.e., num-1 is not in the set).
- By inserting all numbers into a set, you can test in O(1) average whether a number exists.
- For every start point, "grow" the consecutive sequence as far as possible using the set for fast lookups.
- Update and return the maximum streak length found.

Steps:
1. Insert all elements into an unordered_set<int> for O(1) lookups.
2. For each element in the set:
    a) If (num-1) is not in the set, current is the start of a sequence.
    b) While (num+1) exists in the set, increment current streak length.
    c) Update largest streak as needed.
3. Return the largest streak found.

Complexity:
- Time: O(n) average case (every insert and lookup is O(1), each element is processed at most twice).
- Space: O(n) for the hash set.

---

Why It Works:
-------------
- Only starting at "true starts" (numbers with no left neighbor) avoids redundant work.
- Each sequence is counted only once, not from interior points, so no extra passes.
- Set ensures fast presence checks and handles duplicates naturally.

---

Dry Run Example:
----------------
Input: [100, 4, 200, 1, 3, 2]
Set: {1, 2, 3, 4, 100, 200}

- Consider 100: 99 not in set (start), check 101 (not in set) ⇒ streak = 1
- Consider 4: 3 in set → skip
- Consider 200: 199 not in set (start), check 201 (not in set) ⇒ streak = 1
- Consider 1: 0 not in set (start), 2 in set, 3 in set, 4 in set, 5 not in set ⇒ streak = 4
- 3, 2: Both have predecessor present (not starts), so skipped.

Longest streak found: 4

---

Code Implementation:
--------------------
*/

#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if(nums.empty()) return 0;
       
        int largest = 1;

        unordered_set<int> st;
        for(int i = 0; i < nums.size(); i++) {
            st.insert(nums[i]);
        }

        for(auto it : st) {
            // Only check for the start of a sequence
            if(st.find(it - 1) == st.end()) {
                int x = it;
                int count = 1; 
                while(st.find(x + 1) != st.end()) {
                    x = x + 1;
                    count = count + 1;
                }
                largest = max(largest, count);
            }
        }
        return largest;
    }
};

/*
Summary:
--------
- Brute force: O(n^2), linear search for every next number.
- Sorting: O(n log n), simple but not optimal.
- Optimal: Insert all into hash set, only extend sequences from their smallest element.
- Each number looked up O(1) times, no extra work, O(n) time and O(n) space.
- Handles duplicates and negative numbers automatically.
*/


//Using hash set as a optimal appraoch 

#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {

        // If the array is empty, there is no sequence
        if(nums.empty()) return 0;

        // HashSet to store all unique numbers
        unordered_set<int> st;

        // Insert all elements into the set
        // This removes duplicates and allows O(1) lookups
        for(int i = 0; i < nums.size(); i++) {
            st.insert(nums[i]);
        }

        int longest = 1;   // Stores the longest sequence length found

        // Loop through each number in the set
        for(auto it : st) {

            // Check if it is the START of a sequence
            // If (it - 1) does NOT exist, then this is a starting number
            if(st.find(it - 1) == st.end()) {

                int currentNum = it;   // Start of sequence
                int count = 1;         // Length of current sequence

                // Keep checking the next consecutive numbers
                while(st.find(currentNum + 1) != st.end()) {

                    currentNum = currentNum + 1;   // Move to next number
                    count = count + 1;             // Increase sequence length
                }

                // Update the longest sequence found so far
                longest = max(longest, count);
            }
        }

        // Return the maximum length of consecutive sequence
        return longest;
    }
};

//Time complexity is O(n) using a hash set for constant lookups, and space complexity is O(n) for storing elements.
//