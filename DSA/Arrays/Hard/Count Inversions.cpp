/*
Count Inversions in Array - Complete Guide

Problem Name:
Count Inversions

Problem Statement:
Given an array of integers, count the number of inversion pairs in the array.
An inversion is a pair (i, j) such that:
 - i < j
 - arr[i] > arr[j]

Example:
Input: [5, 3, 2, 4, 1]
Inversions: (5,3), (5,2), (5,4), (5,1), (3,2), (3,1), (2,1), (4,1)
Output: 8

Logic & Intuition:
- Naive Approach:
  Check every pair (i, j), increment count if arr[i] > arr[j].
  Time complexity is O(N^2), impractical for large arrays.
  
- Efficient Approach (Merge Sort Based):
  Use modified merge sort to count inversions during merging:
  * While merging two sorted halves, if element in left > element in right,
    all elements after current left element till mid form inversions with right's element.
  * Count inversions from left half, right half, and merge step recursively.

Steps:
1. Divide the array into halves recursively.
2. Recursively count inversions in left and right halves.
3. Merge two sorted halves while counting cross-inversions.
4. Return total inversion count (left + right + cross).

Why it works:
- In merge step, arrays are sorted; counting how many elements are greater than right-side values becomes simple.
- Reduces complexity by avoiding checking every pair explicitly.
  
Edge Cases:
- Empty or single-element arrays have 0 inversions.
- Already sorted ascending array has 0 inversions.
- Descending sorted array has maximum inversions.
- Arrays with duplicates, counting carefully.
- Large input arrays requiring O(N log N) solution.

Time Complexity:
- Naive: O(N^2)
- Merge Sort Based: O(N log N)

Space Complexity:
- O(N) auxiliary space used in merge step.

/*
---

1. Brute Force Approach:

- Double nested loops over array.
- For each i < j, if arr[i] > arr[j], increment count.

Time Complexity: O(N^2)
Space Complexity: O(1)
*/
Code:

#include <vector>
using namespace std;

long long inversionCountBrute(vector<int>& arr) {
    long long count = 0;
    int n = arr.size();
    for (int i = 0; i < n -1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (arr[i] > arr[j])
                count++;
        }
    }
    return count;
}

---
/*
2. Optimal - Using Merge Sort:

- Recursively split array in halves.
- Count inversions in left and right halves.
- Count cross-inversions during merge step.
- Merge sorted halves.
*/
Code:

#include <vector>
using namespace std;

class Solution {
public:
    long long merge(vector<int>& arr, int left, int mid, int right) {
        vector<int> temp(right - left + 1);
        int i = left, j = mid + 1, k = 0;
        long long invCount = 0;

        while (i <= mid && j <= right) {
            if (arr[i] <= arr[j]) {
                temp[k++] = arr[i++];
            } else {
                invCount += (mid - i + 1);
                temp[k++] = arr[j++];
            }
        }

        while (i <= mid) temp[k++] = arr[i++];
        while (j <= right) temp[k++] = arr[j++];

        for (int idx = 0; idx < (int)temp.size(); idx++)
            arr[left + idx] = temp[idx];

        return invCount;
    }

    long long mergeSort(vector<int>& arr, int left, int right) {
        long long invCount = 0;
        if (left < right) {
            int mid = left + (right - left) / 2;
            invCount += mergeSort(arr, left, mid);
            invCount += mergeSort(arr, mid + 1, right);
            invCount += merge(arr, left, mid, right);
        }
        return invCount;
    }

    long long inversionCount(vector<int>& arr) {
        return mergeSort(arr, 0, (int)arr.size() - 1);
    }
};

---
/*
Extra Notes:
- Handle integer overflow with long long count.
- Can be modified to track inversion pairs but more complex.
- Classic divide and conquer problem.
*/
