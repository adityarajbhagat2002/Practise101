
// 4 Sum Problem: All Approaches Cheat Sheet (TakeUForward)
// =======================================================

// Problem Statement:
// Find all unique quadruplets in an array that sum up to the given target.
// - Quadruplets must use four different indices.
// - No duplicate quadruplets in the final result.

// --------------------------------------------------
// Intuition & Constraints:
// --------------------------------------------------
// - Find all sets of 4 numbers that sum to target
// - Output must not have duplicates (sort and skip)
// - Indices must be distinct
// - Sorting helps with duplicate avoidance and pointer logic

// --------------------------------------------------
// 1. Brute Force Approach
// --------------------------------------------------
// - Use four nested loops to try all quadruplets
// - Sort each found quadruplet, insert into a set for uniqueness

#include <vector>
#include <set>
#include <algorithm>
using namespace std;

vector<vector<int>> fourSumBrute(vector<int>& nums, int target) {
    int n = nums.size();
    set<vector<int>> st;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            for (int k = j + 1; k < n; k++)
                for (int l = k + 1; l < n; l++) {
                    long long sum = nums[i];
                    sum += nums[j];
                    sum += nums[k];
                    sum += nums[l];
                    if (sum == target) {
                        vector<int> temp = {nums[i], nums[j], nums[k], nums[l]};
                        sort(temp.begin(), temp.end());
                        st.insert(temp);
                    }
                }
    return vector<vector<int>>(st.begin(), st.end());
}

// Time Complexity: O(n^4 * log m) where m = number of unique quadruplets
// Space Complexity: O(m*4), for the set

// --------------------------------------------------
// 2. Better (Hashing) Approach
// --------------------------------------------------
// - For each triplet (i, j, k), compute the needed 4th number (target - sum) and look up in a hash set.
// - Only consider values for l > k. Store quadruplets in a set to ensure uniqueness.

#include <unordered_set>

vector<vector<int>> fourSumHash(vector<int>& nums, int target) {
    int n = nums.size();
    set<vector<int>> st;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            for (int k = j + 1; k < n; k++) {
                unordered_set<int> hash;
                for (int l = k + 1; l < n; l++) hash.insert(nums[l]);
                int remain = target - nums[i] - nums[j] - nums[k];
                if (hash.count(remain)) {
                    vector<int> temp = {nums[i], nums[j], nums[k], remain};
                    sort(temp.begin(), temp.end());
                    st.insert(temp);
                }
            }
    return vector<vector<int>>(st.begin(), st.end());
}

// Time Complexity: O(n^3 * n * log m) ~= O(n^4)
// Space Complexity: O(n + m*4), hash set per triplet, set for result

// --------------------------------------------------
// 3. Optimal Approach (Two-pointer + Sorting)
// --------------------------------------------------
// - Sort the array
// - For every pair (i, j), use two pointers (k, l) to find quadruplets:
//   - Increase k if sum < target, decrease l if sum > target
//   - Skip duplicates for i, j, k, l

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        int n = nums.size();
        vector<vector<int>> ans;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < n; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            for (int j = i + 1; j < n; j++) {
                if (j > i + 1 && nums[j] == nums[j - 1]) continue;
                int k = j + 1;
                int l = n - 1;
                while (k < l) {
                    long long sum = nums[i];
                    sum += nums[j];
                    sum += nums[k];
                    sum += nums[l];
                    if (sum == target) {
                        vector<int> temp = {nums[i], nums[j], nums[k], nums[l]};
                        ans.push_back(temp);
                        k++; l--;
                        while (k < l && nums[k] == nums[k - 1]) k++;
                        while (k < l && nums[l] == nums[l + 1]) l--;
                    }
                    else if (sum < target) k++;
                    else l--;
                }
            }
        }
        return ans;
    }
};

// Time Complexity: O(n^3) (outer two loops, inner while runs in O(n))
// Space Complexity: O(m*4), only for output quadruplets, m = result count

// --------------------------------------------------
// Summary Table:
// --------------------------------------------------
// | Approach      | Time Complexity                | Space Complexity           |
// |---------------|-------------------------------|---------------------------|
// | Brute Force   | O(n^4 * log m)                 | O(m*4)                    |
// | Hashing       | O(n^4)                         | O(n + m*4)                |
// | Two-pointer   | O(n^3 + n log n)               | O(m*4)                    |

// Notes and Edge Cases:
// - Always skip duplicates for i, j, k, l to avoid repeated quadruplets.
// - Use sorting for efficient duplicate checks and index management.
// - Handle cases with fewer than 4 elements gracefully (return empty).
// - Avoid int overflow with long long for sum
// - No extra sets/hashmaps required in optimal code; only output is stored.

// All approaches, sample codes, time-space analysis, and edge/duplicate handling tips included above!
