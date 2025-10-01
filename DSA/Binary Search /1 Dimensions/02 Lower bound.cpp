/*
Lower Bound

Definition:
The smallest index such that arr[index] >= target. The array must be sorted.

Examples:
For arr = [1, 2, 2, 3, 5, 8, 15, 19], 
lower_bound(8) → index 5
lower_bound(9) → index 6 (element 15)
lower_bound(20) → arr.size() (not found, return n)

Logic & Intuition:
If you find an element >= target, store its index as a possible answer but keep searching to the left for a smaller such index.
If no such element exists, return n.

Steps:
Initialize low = 0, high = n-1, ans = n.
While low <= high:
    Compute mid = low + (high - low)/2
    If arr[mid] >= target, set ans = mid, move high = mid - 1 (search left).
    Else, move low = mid + 1 (search right).
Return ans.

Why It Works:
Always searches left when a candidate is found, guaranteeing to find the smallest such index.
If not found, returns n, indicating insertion at end.

Time/Space Complexity:
O(log n) time, O(1) space.

Extra Notes:
C++ STL: std::lower_bound or (for arrays) with pointer arithmetics.

Code:
*/

int lowerBound(vector<int>& arr, int target) {
    int n = arr.size();
    int low = 0, high = n - 1;
    int ans = n;  // Default to n when no element found

    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(arr[mid] >= target) {
            ans = mid;      // Potential candidate
            high = mid - 1; // Try to find smaller index
        } else {
            low = mid + 1;
        }
    }
    return ans;  // If ans == n, target would be inserted at end
}
