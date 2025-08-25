// ****************************************************************************************
// Problem: Rotate Image (Rotate Matrix by 90 Degrees Clockwise)
// Language: C++
// Includes explanations and code for both Brute and Optimal approaches
// ****************************************************************************************

Note :- Do dry run for all matrix problems take your time but do dry run to understand the formulas and how they work


/*
Problem Statement:
------------------
Given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise) in-place.

Example:
Input:
[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
Output:
[
 [ 7, 4, 1 ],
 [ 8, 5, 2 ],
 [ 9, 6, 3 ]
]

---

Brute Force Approach: (Do the Dry run for both better and optimal approaches to understand the formulas)
---------------------
Intuition:
- Create a new matrix `ans` of the same size.
- Each element `matrix[i][j]` in the original matrix moves to position `ans[j][n - 1 - i]`.
- This new matrix `ans` will be the rotated image.

Mapping:
- `(i, j)` → `(j, n - 1 - i)`

Example:
Original: matrix = 1 → ans = 1
Original: matrix = 2 → ans = 2


Complexity:
- Time: O(n^2)
- Space: O(n^2) (extra matrix required)

---

Optimal Approach:
-----------------
Idea:
- A rotation by 90 degrees clockwise can be achieved by two steps on the original matrix:
  1. Transpose the matrix (swap matrix[i][j] with matrix[j][i]).
  2. Reverse each row.

Why this works:
- Transpose converts rows to columns.
- Reversing rows shifts columns in place, completing the rotation.

---

Diagonal Concept (Transpose step):
---------------------------------
- Transpose means flip the matrix over its main diagonal.
- The main diagonal is elements where row == column (i == j).
- To avoid double swapping, swap elements only where column > row (j > i).

Illustration:
Original indices:
| i\j | 0 | 1 | 2 | 3 |
|-----|---|---|---|---|
| 0   | * | a | b | c |
| 1   | d | * | e | f |
| 2   | g | h | * | i |
| 3   | j | k | l | * |

After transpose, swap pairs (i,j) with (j,i) where j > i:
- Swap a (0,1) with d (1,0)
- Swap b (0,2) with g (2,0)
- Swap c (0,3) with j (3,0)
- Swap e (1,2) with h (2,1)
- Swap f (1,3) with k (3,1)
- Swap i (2,3) with l (3,2)

---

Example Walkthrough:

Original:
1 2 3  
4 5 6  
7 8 9  

After transpose:
1 4 7  
2 5 8  
3 6 9  

After reversing each row:
7 4 1  
8 5 2  
9 6 3  

---

Complexity Analysis:
- Both approaches have O(n^2) time complexity.
- Brute uses O(n^2) space, Optimal uses O(1) extra space.

---
Code:
*/


// Brute Force Approach (uses extra matrix)
class SolutionBrute {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        vector<vector<int>> ans(n, vector<int>(n));
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                ans[j][n - 1 - i] = matrix[i][j];
            }
        }
        
        matrix = ans; // Copy back
    }
};

// Optimal Approach (In-place)
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        // Transpose
        for (int i = 0; i < n - 1; ++i) {
            for (int j = i + 1; j < n; ++j) {
                swap(matrix[i][j], matrix[j][i]);
            }
        }
        // Reverse each row
        for (int i = 0; i < n; ++i) {
            reverse(matrix[i].begin(), matrix[i].end());
        }
    }
};

/* 
Summary:
- Brute force creates a new matrix to achieve rotation with straightforward element mapping.
- Optimal approach rotates in-place by transposing and then reversing each row.
- This ensures O(1) extra space while maintaining O(n^2) time complexity.
- Understanding the diagonal (main diagonal) as the pivot for transpose is key.

*/