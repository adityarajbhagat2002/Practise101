/*
Reverse Pairs

Problem Name:
Reverse Pairs

Problem Statement:
Given an array of integers, count the number of pairs (i,j) such that i<j and arr[i]>2×arr[j].
Example:
Input: [40, 25, 19, 12, 9, 6, 2]
Reverse pairs:
For 2: (6,2), (9,2), (12,2), (19,2), (25,2), (40,2)
For 6: (12,6), (19,6), (25,6)
and so on…
Total pairs for the above: 15

Logic & Intuition:
Like the "Count Inversions" problem, but the condition is stricter: the left element must be greater than twice the right.
Brute Force: Try every pair, check the condition, increment counter — O(n2).
Optimal Solution: Use a modified Merge Sort to count reverse pairs while merging: each time merging two sorted halves, efficiently count how many arr[i]>2×arr[j] using two pointers.
Why Merge Sort?
At each merge step, both halves are sorted, which allows linear scanning to count qualifying pairs.

Edge Cases:
Empty array, single element (result is 0).
Arrays with all equal elements (may result in zero or multiple reverse pairs).
Already sorted ascending/descending arrays.
Large and negative numbers (ensure multiplication doesn’t overflow).

Steps:
Brute Force:
Loop i from 0 to n-2.
For each i, loop j from i+1 to n-1.
If arr[i]>2×arr[j], increment counter.
Optimal - Modified Merge Sort:
Recursively divide the array.
For each pair of sorted subarrays, count reverse pairs:
For each i in left, seek the smallest j in right so that all values before j satisfy arr[i]>2×arr[j].
Use a pointer to avoid repeatedly checking same elements.
Merge as in normal merge sort.
Sum counts from left half, right half, between, recursively.

Why It Works:
Sorted halves from merge sort allow binary search or linear pointer optimizations when counting pairs.
For each left element, we only need to check forward in right half — no need to re-examine left-side elements.

Space and Time Complexity:
Brute Force:
Time: O(n2), Space: O(1)
Merge Sort Based:
Time: O(nlogn) (each merge and counting step is linear, log n levels)
Space: O(n) (for temporary arrays during merging)

Code
Brute Force Approach:
*/
int reversePairsBrute(vector<int>& arr) {
    int n = arr.size(), count = 0;
    for(int i = 0; i < n-1; ++i)
        for(int j = i+1; j < n; ++j)
            if(arr[i] > 2LL * arr[j]) // use LL to avoid overflow!
                count++;
    return count;
}

/*
Optimal (Merge Sort Based):
*/
class Solution {
public:
    int merge(vector<int>& arr, int low, int mid, int high) {
        int count = 0;
        int j = mid + 1;
        // Count reverse pairs
        for (int i = low; i <= mid; i++) {
            while (j <= high && arr[i] > 2LL * arr[j]) // use LL!
                j++;
            count += (j - (mid + 1));
        }
        // Merge step (same as merge sort)
        vector<int> temp;
        int left = low, right = mid + 1;
        while (left <= mid && right <= high) {
            if (arr[left] <= arr[right])
                temp.push_back(arr[left++]);
            else
                temp.push_back(arr[right++]);
        }
        while (left <= mid)
            temp.push_back(arr[left++]);
        while (right <= high)
            temp.push_back(arr[right++]);
        for (int k = low; k <= high; k++)
            arr[k] = temp[k - low];
        return count;
    }

    int mergeSort(vector<int>& arr, int low, int high) {
        if (low >= high) return 0;
        int mid = low + (high - low) / 2;
        int count = mergeSort(arr, low, mid);
        count += mergeSort(arr, mid + 1, high);
        count += merge(arr, low, mid, high);
        return count;
    }

    int reversePairs(vector<int>& arr) {
        return mergeSort(arr, 0, arr.size() - 1);
    }
};

/*
Extra Notes:
Always use 2LL * arr[j] to handle potential integer overflow.
The merge sort logic for reverse pairs is an elegant extension of inversion counting.
Be candid about array modifications — create copies if original array must not be altered (important for interviews).
Highly asked by top tech companies for high-level interviews.
Practice both brute-force and optimal version for confidence in both logic and implementation.
*/
