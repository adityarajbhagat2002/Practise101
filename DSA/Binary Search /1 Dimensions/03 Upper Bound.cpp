/*
Upper Bound

Definition:
The smallest index such that arr[index] > target.

Examples:
For arr = [1, 2, 2, 3, 5, 8, 8, 10, 15, 19]
upper_bound(6) → index 5 (element 8)
upper_bound(12) → index 8 (element 15)
upper_bound(19) or greater → n

Logic & Intuition:
Very similar to lower bound, just use arr[mid] > target.
When found, move left to find smaller such index.

Steps:
Initialize low = 0, high = n-1, ans = n.
While low <= high:
    Compute mid = low + (high - low)/2
    If arr[mid] > target, set ans = mid, move high = mid - 1.
    Else, move low = mid + 1.
Return ans.

Why It Works:
Finds strictly greater values – fundamental for range queries and insertions.

Time/Space Complexity:
O(log n) time, O(1) space.

Extra Notes:
Only difference from lower bound is use of "greater than" instead of "greater than or equal".

Code:
*/

int upperBound(vector<int>& arr, int target) {
    int n = arr.size();
    int low = 0, high = n - 1;
    int ans = n;  // Default to n when no element found

    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(arr[mid] > target) {
            ans = mid;      // Potential candidate
            high = mid - 1; // Try to find smaller index
        } else {
            low = mid + 1;
        }
    }
    return ans; // If ans == n, no element greater than target
}
