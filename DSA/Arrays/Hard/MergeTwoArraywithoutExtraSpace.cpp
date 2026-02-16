/*
Merge Two Sorted Arrays Without Extra Space - Complete Note

Problem:
Given two sorted arrays nums1 and nums2 of sizes m and n respectively, 
merge nums2 into nums1 such that nums1 becomes a fully sorted array of size m+n. 
Extra space beyond nums1 and nums2 is not allowed.

---

Logic and Intuition:
- Since nums1 has enough space at the end, merge from the back to avoid overwriting elements.
- Use two pointers starting from the ends of initialized parts of nums1 and nums2 and place the larger 
element at the end of nums1.
- If elements remain in nums2, copy them into nums1.
- Alternatively, the Gap method (Shell sort style) can be used by treating nums1 and nums2 as a single 
combined array and comparing/swapping elements with a gap, reducing the gap each iteration until sorted.

---

Approaches:

1. Two-pointer Merge from Back (Standard Approach):

- Initialize three pointers:
  - i = m-1 (end of initialized nums1)
  - j = n-1 (end of nums2)
  - k = m + n -1 (end of nums1 total space)
- Iterate while i and j >= 0:
  - Place larger of nums1[i] and nums2[j] at nums1[k].
  - Decrement pointers accordingly.
- Copy remaining nums2 elements if any.
- Remaining nums1 elements are already in place.

🔹 Problem at a glance
We want to merge nums2 into nums1, keeping things sorted.

But if we start filling nums1 from the front, we risk overwriting elements that we haven’t yet compared.

That’s why the trick is to start merging from the bac


⚡ Intuition:

Front merge = needs shifting → inefficient.

Back merge = just filling in free space → optimal.



*/
Code:

#include <vector>
using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m - 1;        // last element in nums1's initial part
        int j = n - 1;        // last element in nums2
        int k = m + n - 1;    // last position in nums1

        while(i >= 0 && j >= 0) {
            if(nums1[i] > nums2[j]) {
                nums1[k--] = nums1[i--];
            } else {
                nums1[k--] = nums2[j--];
            }
        }

        while(j >= 0) {
            nums1[k--] = nums2[j--];
        }
    }
};

/*

⚡ Intuition in one line:
We fill nums1 from the back by always placing the largest of the two candidates 
(nums1[i] vs nums2[j]) into nums1[k], ensuring sorted order without overwriting unprocessed values.


---

2. Gap Method (Shell Sort inspired):

- Treat nums1 and nums2 as one combined array.
- Initialize gap = ceil((m+n)/2).
- Compare and swap elements gap positions apart within and between arrays:
  - Compare nums1[i] and nums1[i+gap]
  - Compare nums1[i] and nums2[j] when gap crosses boundary
  - Compare nums2[j] and nums2[j+gap]
- Reduce gap by ceiling of half until gap is zero.

*/
Code:

#include <vector>
#include <algorithm>
using namespace std;

int nextGap(int gap) {
    if(gap <= 1)
        return 0;
    return (gap / 2) + (gap % 2);
}

void mergeGapMethod(vector<int>& nums1, int n, vector<int>& nums2, int m) {
    int gap = n + m;
    for(gap = nextGap(gap); gap > 0; gap = nextGap(gap)) {
        int i, j;

        // Compare in first array
        for(i = 0; i + gap < n; i++) {
            if(nums1[i] > nums1[i + gap])
                swap(nums1[i], nums1[i + gap]);
        }

        // Compare between both arrays
        for(j = gap > n ? gap - n : 0; i < n && j < m; i++, j++) {
            if(nums1[i] > nums2[j])
                swap(nums1[i], nums2[j]);
        }

        // Compare in second array
        if(j < m) {
            for(j = 0; j + gap < m; j++) {
                if(nums2[j] > nums2[j + gap])
                    swap(nums2[j], nums2[j + gap]);
            }
        }
    }
}
/*
---

Time Complexity:
- Two-pointer merge: O(m + n)
- Gap method: O((m + n) log(m + n)) approximately due to shell sort style gaps

Space Complexity:
- Both approaches: O(1) extra space (beyond input arrays)

---

Extra Notes:
- Two-pointer merge is simpler and common in practical scenarios.
- Gap method is elegant, avoids sorting after partial swaps, useful when constraints disallow extra memory.
- Both maintain arrays sorted after merging in-place.
*/
