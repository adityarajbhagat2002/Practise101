https://leetcode.com/problems/majority-element/description/


// Majority Element (LeetCode 169)
// ✅ Find the element that appears more than n/2 times in an array.
// Assumes such majority element always exists.

/*
Problem:
--------
Given an integer array nums of size n, return the majority element — the element that appears more than ⌊n/2⌋ times.

It is guaranteed that the majority element always exists.

---

Solution 1: Using Hash Map for Frequency Counting

Logic:
------
- Use a hash map (unordered_map or std::map) to count how many times each element appears.
- Iterate through the array, incrementing the count for each element.
- Then scan the map to find the element whose count is more than n/2.
- Return that element.

Time Complexity:
----------------
- O(n) average if using unordered_map (hash map) with O(1) average insertions/lookups.
- O(n log n) if using std::map (balanced BST) with O(log n) insertions/lookups.

Space Complexity:
-----------------
- O(n) for storing frequencies.

Code Implementation (Hash Map):

*/

#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> freq;
        int n = nums.size();

        for (int i = 0; i < n; i++) {
            freq[nums[i]]++;
        }

        for (auto& kv : freq) {
            if (kv.second > n / 2) {
                return kv.first;
            }
        }

        return -1;  // To satisfy compiler; problem guarantees majority element exists
    }
};

/*
---------------------------------------------------------------------------------------------------

Solution 2: Boyer-Moore Voting Algorithm (Optimal Approach)

Logic & Intuition:
------------------
- Concept of a **dominant element**: the majority element appears more times than all other elements combined.
- Maintain a candidate element and a count.
- If count is zero, pick the current element as the candidate.
- For each element:
  - If it matches the candidate, increment count.
  - Otherwise, decrement count.
- Because the majority element is dominant, it survives all cancellations and ends as the candidate.
- After one pass, verify the candidate by counting its occurrences to confirm correctness.

Why it works:
-------------
- Every increment cancels a matching element.
- Every decrement cancels a non-matching element.
- Since majority element frequency > sum of others, it cannot be fully canceled.

Time Complexity:
----------------
- O(n) — single pass to find candidate + single pass to verify.

Space Complexity:
-----------------
- O(1) — uses fixed variables (candidate and count).

Code Implementation (Boyer-Moore Voting):

*/

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int count = 0;
        int element;

        // Step 1: Find candidate for majority element
        for (int i = 0; i < nums.size(); i++) {
            if (count == 0) {
                element = nums[i];
                count = 1;
            }
            else if (nums[i] == element) {
                count++;
            }
            else {
                count--;
            }
        }

        // Step 2: Verify candidate (optional, problem guarantees existence)
        int checkcount = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == element) {
                checkcount++;
            }
            if (checkcount > nums.size() / 2) {
                return element;
            }
        }

        return -1;  // Fallback, should not happen as per problem statement
    }
};

/*
---------------------------------------------------------------------------------------------------

Summary:

- The **dominant element** (majority element) appears more than half of the total elements.
- Hash map approach counts frequencies explicitly, straightforward but uses extra space.
- Boyer-Moore Voting Algorithm leverages the dominant property to find the candidate using O(1) space and O(n) time.
- Boyer-Moore is preferred for performance and optimality.
- Hash map method is useful for understanding and when space is not a constraint.

Use case recommendation:
- Prefer Boyer-Moore Voting Algorithm for interviews and large inputs.
- Hash map method is simpler to implement and understand for beginners.

*/
