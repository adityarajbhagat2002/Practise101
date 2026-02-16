https://leetcode.com/problems/maximum-product-subarray/description/

/*
Maximum Product Subarray - Complete Guide

Problem Name:
Maximum Product Subarray

Problem Statement:
Given an integer array `nums`, find the contiguous subarray (containing at least one number) which has the largest product, and return the product.

---

Logic and Intuition:
- The problem is similar to maximum subarray sum but complicated by the product operation.
- Key complications arise due to negative numbers and zeros:
  * Multiplying by zero resets the product.
  * Multiplying negative numbers can flip the product sign, affecting max/min product.
- Naive approach tests all subarrays (inefficient).
- Maintain prefix and suffix products while scanning from left to right and right to left respectively.
- Reset prefix/suffix to 1 if zero is encountered to restart the product calculation.
- Max product could be the max product of prefix or suffix at any point.

---

Steps:
1. Initialize prefix and suffix products as 1.
2. Traverse the array forward and backward simultaneously.
3. At each step, 
   - If prefix or suffix becomes zero, reset it to 1.
   - Multiply prefix by current forward element.
   - Multiply suffix by current backward element.
4. Keep track of the maximum among prefix, suffix, and the current max product.
5. Return the maximum product found.

---

Why It Works:
- Traversing prefix tracks max product considering start from beginning.
- Traversing suffix covers subarrays ending at the end.
- Considering zero resets avoids inclusion of zero in product subarray.
- Handles negative numbers effectively by evaluating both directions.

---

Edge Cases:
- Array with single element
- Zeros breaking the product chain
- Negative numbers including odd/even counts
- Entire array of negative numbers
- Large arrays to test performance

---

Time Complexity:
- O(N), single pass over array

Space Complexity:
- O(1), constant extra space

---
*/
Code (Prefix and Suffix Approach):
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        int prefix = 1;
        int suffix = 1;
        int maxProduct = INT_MIN;

        for (int i = 0; i < n; i++) {
            if (prefix == 0) prefix = 1;
            if (suffix == 0) suffix = 1;

            prefix *= nums[i];
            suffix *= nums[n - i - 1];

            maxProduct = max(maxProduct, max(prefix, suffix));
        }
        return maxProduct;
    }
};
/*
---

Extra Notes:
- Resetting prefix/suffix on zero is key to handling zeros correctly.
- This approach is simple yet captures the complexities introduced by negatives.
- Alternative classical approach is tracking max and min products in a single forward pass.
- Understanding zero and negative product behaviors is vital for these problems.
*/
