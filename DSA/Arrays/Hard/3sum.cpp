// 3 Sum Problem: Complete Approach Guide (TakeUForward)
// =====================================================

// Problem Statement:
// Find all unique triplets (i, j, k) in an array such that:
// - i ≠ j ≠ k
// - nums[i] + nums[j] + nums[k] == 0
// - No duplicate triplets (regardless of order)
// Output order does not matter.

// --------------------------------------------------------------------
// Core Intuition:
// - Try all combinations of three numbers where sum = 0.
// - Ensure triplets are unique and do not reuse elements.
// --------------------------------------------------------------------

// --------------------------------------------------------------------
// 1. Brute Force Approach
// --------------------------------------------------------------------
// - Try all triplets using three nested loops.
// - Check all combinations and collect sorted, unique triplets in a set.
// - Time Complexity: O(n^3 * log m), m = number of unique triplets
// - Space Complexity: O(m*3), where m = count of unique triplets

#include <vector>
#include <set>
#include <algorithm>
using namespace std;

vector<vector<int>> threeSumBrute(vector<int>& nums) {
    int n = nums.size();
    set<vector<int>> st;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                if (nums[i] + nums[j] + nums[k] == 0) {
                    vector<int> temp = {nums[i], nums[j], nums[k]};
                    sort(temp.begin(), temp.end());
                    st.insert(temp);
                }
            }
        }
    }
    return vector<vector<int>>(st.begin(), st.end());
}

// --------------------------------------------------------------------
// 2. Better (Hashing) Approach
// --------------------------------------------------------------------
// - For each pair (i, j), look for third number (-nums[i]-nums[j]) using a hash set.
// - Make sure all elements are distinct (different indices).
// - Store triplets sorted in a set for uniqueness.
// - Time Complexity: O(n^2 * log m), m = number of unique triplets
// - Space Complexity: O(n + m*3)

#include <unordered_set>

vector<vector<int>> threeSumHash(vector<int>& nums) {
    int n = nums.size();
    set<vector<int>> st;
    for (int i = 0; i < n; i++) {
        unordered_set<int> hash;
        for (int j = i + 1; j < n; j++) {
            int third = -nums[i] - nums[j];
            if (hash.count(third)) {
                vector<int> temp = {nums[i], nums[j], third};
                sort(temp.begin(), temp.end());
                st.insert(temp);
            }
            hash.insert(nums[j]);
        }
    }
    return vector<vector<int>>(st.begin(), st.end());
}

// --------------------------------------------------------------------
// 3. Optimal Two-Pointer Approach (Sorted)
// --------------------------------------------------------------------
// - Sort the array.
// - For every index 'i', use two pointers (j, k) to find triplets with sum == 0.
// - Skip duplicate values to avoid repeated triplets.
// - Time Complexity: O(n^2)
// - Space Complexity: O(m*3) where m = number of unique triplets, no extra set/hashmap.

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n=nums.size();
        vector<vector<int>> ans;
        sort(nums.begin(),nums.end());
        for(int i=0;i<n;i++){
            if(i>0 && nums[i]== nums[i-1]) continue;
            int j=i+1;
            int k=n-1;
            while(j<k){
                int sum= nums[i]+nums[j]+nums[k];
                if(sum<0){
                    j++;
                }
                else if(sum>0){
                    k--;
                }
                else{
                    vector<int> temp= {nums[i], nums[j], nums[k]};
                    ans.push_back(temp);
                    j++;
                    k--;
                    while(j<k && nums[j]==nums[j-1]) j++;
                    while(j<k && nums[k]==nums[k+1]) k--;
                }
            }
        }
        return ans;
    }
};

// --------------------------------------------------------------------
// Summary Table:
//
// | Approach      | Time Complexity            | Space Complexity         |
// |---------------|---------------------------|-------------------------|
// | Brute Force   | O(n^3 * log m)             | O(m*3)                  |
// | Hashing       | O(n^2 * log m)             | O(n + m*3)              |
// | Two-pointer   | O(n^2 + n log n)           | O(m*3)                  |
//
// - m = number of unique triplets found.
// - All approaches handle duplicates; optimal approach is preferred for interviews.
// --------------------------------------------------------------------

// Notes:
// - Always sort output triplets for consistent comparison.
// - Carefully skip duplicates for i, j, k to avoid repeated results.
// - For n < 3, return empty vector.
