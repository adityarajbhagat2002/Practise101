/*
===========================================================================================
MERGE SORT - DIVIDE AND CONQUER STORY
===========================================================================================
Source: CodeStoryWithMIK (YouTube)
Concept: Recursion & Sorting
Complexity: Time O(n log n) | Space O(n)

-------------------------------------------------------------------------------------------
PROBLEM DESCRIPTION:
- Given an array, sort it in non-decreasing order.
- Strategy: Merge Sort uses the "Divide and Conquer" approach.
    1. Divide: Split the array into two halves.
    2. Conquer: Recursively sort both halves.
    3. Combine: Merge the two sorted halves into one sorted array.

-------------------------------------------------------------------------------------------
THE RECURSIVE STORY (Story to Code): [00:14:27]
1. Base Case: If the array has only one element (l >= r), it's already sorted. [00:16:22]
2. Find the middle index: mid = l + (r - l) / 2.
3. Trust Recursion:
   - Call mergeSort(l, mid) to sort the left half. [00:17:58]
   - Call mergeSort(mid + 1, r) to sort the right half. [00:18:10]
4. The Real Work (Merge): Once both halves are sorted, merge them back together. [00:18:29]

-------------------------------------------------------------------------------------------
COMPLEXITY ANALYSIS: [00:12:37]
- Time Complexity: O(n log n)
    - The tree depth is log(n) because we divide the array by 2 at each level.
    - At each level, the 'Merge' operation takes O(n) time.
- Space Complexity: O(n)
    - We create temporary arrays (L and R) during the merge process. [00:29:21]
    - Recursive stack space: O(log n).
===========================================================================================
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    // Helper function to merge two sorted subarrays [00:22:10]
    void merge(vector<int>& arr, int l, int m, int r) {
        int n1 = m - l + 1; // Size of left subarray
        int n2 = r - m;     // Size of right subarray

        // Create temporary vectors for storage [00:22:28]
        vector<int> L(n1), R(n2);

        // Fill temporary vectors with data
        int k = l;
        for (int i = 0; i < n1; i++) {
            L[i] = arr[k++];
        }
        for (int i = 0; i < n2; i++) {
            R[i] = arr[k++];
        }

        // Merge the temporary vectors back into arr[l..r] [00:25:44]
        int i = 0, j = 0;
        k = l;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr[k++] = L[i++];
            } else {
                arr[k++] = R[j++];
            }
        }

        // Copy remaining elements of L[], if any [00:27:27]
        while (i < n1) {
            arr[k++] = L[i++];
        }

        // Copy remaining elements of R[], if any
        while (j < n2) {
            arr[k++] = R[j++];
        }
    }

    void mergeSort(vector<int>& arr, int l, int r) {
        // Base Case: Array with 0 or 1 element is already sorted [00:16:22]
        if (l >= r) {
            return;
        }

        int mid = l + (r - l) / 2; // Calculate midpoint to prevent overflow [00:15:16]

        // Recursive calls - The "Trust" part [00:17:58]
        mergeSort(arr, l, mid);       // Sort left half
        mergeSort(arr, mid + 1, r);   // Sort right half

        // Merge the sorted halves [00:19:05]
        merge(arr, l, mid, r);
    }
};

/*
-------------------------------------------------------------------------------------------
DRY RUN VISUALIZATION (n=4):
Input: [3, 2, 1, 5]
1. Split: [3, 2] and [1, 5]
2. Split Left: [3] and [2] -> Merge to [2, 3]
3. Split Right: [1] and [5] -> Merge to [1, 5]
4. Final Merge: [2, 3] + [1, 5] -> Compare (2,1), (2,5), (3,5) -> Result: [1, 2, 3, 5]
-------------------------------------------------------------------------------------------
*/