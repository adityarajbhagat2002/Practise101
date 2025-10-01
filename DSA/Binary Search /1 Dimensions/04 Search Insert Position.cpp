/*
Search Insert Position

Problem:
Given sorted array (distinct values) and a target, return its index if present, or the index where it would be inserted to keep the array sorted.

Examples:
arr = [1, 2, 4, 7], target = 6 → insert at index 3.
arr = [1, 2, 4, 7], target = 2 → index = 1 (already present).

Logic & Intuition:
This is identical to the lower bound problem: return the smallest index with arr[index] >= target.

Steps:
Follow lower_bound logic above; return the final answer index.
If target found, its index is returned.
If not found, return where it should be inserted.

Why It Works:
Lower bound locates where equal-or-greater element occurs (or would occur if not present).

Extra Notes:
Used in LeetCode’s “Search Insert Position” and similar interview questions.

Code:
*/

int searchInsert(vector<int>& nums, int target) {
    int n = nums.size();
    int low = 0, high = n - 1;
    int ans = n;

    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(nums[mid] >= target) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return ans;
}
