/*
Majority Element II: Problem Analysis, Approaches, and Solutions
================================================================
Based on TakeUForward's video "Majority Element II | Brute-Better-Optimal"

---------------------------------------------------------
Problem Statement:

- Given an integer array, find all elements that appear more than floor(n/3) times.
- For example, if n=8, floor(8/3)=2; return elements appearing more than 2 times.
- The answer can have at most two elements.

---------------------------------------------------------
Key Insights and Intuition:

- Maximum number of elements appearing more than floor(n/3) times is 2.
- Problem generalizes majority element (>n/2) to >n/3.
- Use voting/cancellation technique (Moore’s Voting) extended to two candidates.

---------------------------------------------------------
Approaches:

1. Brute Force
2. Better (Hash Map Frequency Count)
3. Optimal (Extended Moore's Voting Algorithm)

---------------------------------------------------------
# 1. Brute Force Approach

- For every element, count occurrences by traversing entire array.
- If count > floor(n/3), add to answer.
- Stop early if two such elements found (max possible).
- Time Complexity: O(n^2)
- Space Complexity: O(1) apart from output list.

Sample Code:
------------------------------------
#include <vector>
using namespace std;
*/
vector<int> majorityElementBruteForce(vector<int>& nums) {
    vector<int> ans;
    int n = nums.size();

    for (int i = 0; i < n; i++) {
        // Skip if element already added
        bool alreadyInAns = false;
        for (int val : ans) {
            if (val == nums[i]) {
                alreadyInAns = true;
                break;
            }
        }
        if (alreadyInAns) continue;

        int count = 0;
        for (int j = 0; j < n; j++) {
            if (nums[j] == nums[i]) count++;
        }

        if (count > n / 3) {
            ans.push_back(nums[i]);
            if (ans.size() == 2) break;  // Max two elements
        }
    }

    return ans;
}
------------------------------------
/*

---------------------------------------------------------
# 2. Better Approach Using Hash Map (Frequency Counting)

- Use unordered_map to store frequencies.
- Traverse map to get elements appearing more than floor(n/3).
- Stop collecting once you have two elements.
- Time Complexity: O(n) average
- Space Complexity: O(n)

Sample Code:
------------------------------------
#include <vector>
#include <unordered_map>
using namespace std;
*/
vector<int> majorityElementHashMap(vector<int>& nums) {
    vector<int> ans;
    int n = nums.size();
    unordered_map<int, int> freq;

    for (int num : nums) {
        freq[num]++;
    }

    for (auto& entry : freq) {
        if (entry.second > n / 3) {
            ans.push_back(entry.first);
            if (ans.size() == 2) break;  // Max two elements
        }
    }

    return ans;
}
------------------------------------
/*
---------------------------------------------------------
# 3. Optimal Approach - Extended Moore's Voting Algorithm

- Maintain two candidates and two counters.
- Single pass to find candidates by voting/cancellation.
- Second pass to verify candidate counts.
- Time Complexity: O(n)
- Space Complexity: O(1)

Edge Cases & Important Notes:
- Initialize candidates to distinct invalid values (such as INT_MIN).
- Ensure when assigning a candidate, it is not equal to the other candidate.
- Carefully use if-else ladder to avoid multiple increments per iteration.
- Verify counts in second pass.
- For n < 3, return unique elements directly.
*/
Updated Optimal Code:
------------------------------------
#include <vector>
#include <climits>
using namespace std;

class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        int count1 = 0, count2 = 0;
        int ele1 = INT_MIN;
        int ele2 = INT_MIN;
        int n = nums.size();

        for (int i = 0; i < n; i++) {
            if (count1 == 0 && nums[i] != ele2) {
                count1 = 1;
                ele1 = nums[i];
            } else if (count2 == 0 && nums[i] != ele1) {
                count2 = 1;
                ele2 = nums[i];
            } else if (ele1 == nums[i]) {
                count1++;
            } else if (ele2 == nums[i]) {
                count2++;
            } else {
                count1--;
                count2--;
            }
        }

        // Verification step
        vector<int> ans;
        count1 = 0; count2 = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] == ele1) count1++;
            else if (nums[i] == ele2) count2++;
        }

        int threshold = n / 3 + 1;
        if (count1 >= threshold) ans.push_back(ele1);
        if (count2 >= threshold) ans.push_back(ele2);

        return ans;
    }
};
------------------------------------
/*
---------------------------------------------------------
Summary of Time and Space Complexities

| Approach           | Time Complexity | Space Complexity | Notes                           |
|--------------------|-----------------|------------------|---------------------------------|
| Brute Force        | O(n^2)          | O(1)             | Nested loops                    |
| Hash Map Frequency | O(n) average    | O(n)             | Extra space for hash map        |
| Moore Voting (Opt) | O(n)            | O(1)             | Two passes, constant extra space |

---------------------------------------------------------
This completes the detailed notes, logical reasoning, edge case handling, and code implementations for Majority Element II problem covering all approaches with final optimal solution.
*/
