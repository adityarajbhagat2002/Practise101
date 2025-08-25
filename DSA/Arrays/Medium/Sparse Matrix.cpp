// ****************************************************************************************
// Problem: Spiral Traversal of a Matrix
// Language: C++
// Optimal approach explanation and code included
// ****************************************************************************************

/*
Problem Statement:
------------------
Given an m x n matrix, return all elements of the matrix in spiral order.

Spiral order means starting at the top-left corner, traverse matrix in the order:
- left → right (top row)
- top → bottom (right column)
- right → left (bottom row)
- bottom → top (left column)
Repeat the process inward until all elements are traversed.

---

Intuition & Pattern:
--------------------
- The traversal follows 4 directional phases in a loop:
    1. Move from left to right along the current top row.
    2. Move from top to bottom down the current rightmost column.
    3. Move from right to left along the current bottom row.
    4. Move from bottom to top up the current leftmost column.
- After each full spiral pass, adjust boundaries inward:
    - top++ (top row completed)
    - right-- (right column completed)
    - bottom-- (bottom row completed)
    - left++ (left column completed)
- Continue until the adjusted boundaries cross.

---

Algorithm Steps:
----------------
1. Initialize boundaries:
   - top = 0
   - bottom = number of rows - 1
   - left = 0
   - right = number of columns - 1
2. While left <= right and top <= bottom:
   a) Traverse top row left → right; increment top.
   b) Traverse right column top → bottom; decrement right.
   c) If top <= bottom, traverse bottom row right → left; decrement bottom.
   d) If left <= right, traverse left column bottom → top; increment left.
3. Collect elements in a result vector and return.

---

Edge Cases:
-----------
- Single row or single column matrices.
- Rectangular (non-square) matrices.
- Empty matrices.

---

Complexity Analysis:
--------------------
- Time Complexity: O(m*n), every element visited once.
- Space Complexity: O(m*n), result storage.

---

Code Implementation:
--------------------
*/

#include <vector>
using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int n = matrix.size();
        if (n == 0) return {};
        int m = matrix[0].size();

        vector<int> ans;
        int left = 0, right = m - 1;
        int top = 0, bottom = n - 1;

        while (left <= right && top <= bottom) {
            // Traverse left to right along top row
            for (int i = left; i <= right; i++) {
                ans.push_back(matrix[top][i]);
            }
            top++;

            // Traverse top to bottom along right column
            for (int i = top; i <= bottom; i++) {
                ans.push_back(matrix[i][right]);
            }
            right--;

            // Traverse right to left along bottom row
            if (top <= bottom) {
                for (int i = right; i >= left; i--) {
                    ans.push_back(matrix[bottom][i]);
                }
                bottom--;
            }

            // Traverse bottom to top along left column
            if (left <= right) {
                for (int i = bottom; i >= top; i--) {
                    ans.push_back(matrix[i][left]);
                }
                left++;
            }
        }

        return ans;
    }
};

/*
Summary:
--------
- This approach efficiently produces the spiral traversal of the matrix.
- It operates in O(m*n) time, perfect for large input sizes.
- The movement logic follows consistent boundary checks and directional traversals.
- Edge cases like single rows or columns are naturally handled by boundary conditions.

*/
