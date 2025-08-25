// ****************************************************************************************
// Problem: Set Matrix Zeroes
// Language: C++
// Includes explanations for Brute, Better, and Optimal approaches
// ****************************************************************************************

/*
Problem Statement:
------------------
Given an m x n matrix, if an element is 0, set its entire row and column to 0. Do it in-place.

---

Brute Force Approach:
---------------------
Intuition:
- For each zero found, set its row and column to zero.
- But setting zeros immediately can cascade and cause incorrect zeros.

Naive Solution:
- Use a placeholder (e.g., -1) to mark positions to zero without immediate effect.
- After full pass, convert placeholders to zeros.

Problems:
- Placeholder may conflict with existing values.
- Multiple passes with high complexity.

Time Complexity:
- O((m*n)*(m+n)) due to nested scans.
Space Complexity:
- O(1) extra space (if placeholder used).

---

Better Approach Using Extra Space:
----------------------------------
Intuition:
- Use two arrays to store which rows and columns need zeroing.

Steps:
1. Scan matrix, mark rows and columns that contain zeros using two boolean arrays.
2. In a second pass, set matrix cells to zero if their row or column is marked.

Time Complexity:
- O(m*n)
Space Complexity:
- O(m + n)


Better Approach (Using Auxiliary Arrays):
- Use two arrays, one for rows and one for columns, to track which ones need zeroing.
- First pass: mark rows and columns that contain zeros.
- Second pass: zero out marked rows and columns.
- Time complexity: O(m*n)
- Space complexity: O(m + n)

Code for Better Approach:
*/
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m=matrix.size();
        int n=matrix[0].size();

        vector<int>row(m,0);
        vector<int>col(n,0);


        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(matrix[i][j]==0){
                    row[i]=1;
                    col[j]=1;
                }
            }
        }

        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){

                if(row[i]||col[j]){
                   
                   matrix[i][j]=0;

                }
            }
        }
        
    }
};

/*
-----------------------------------------------------------------

Optimal Approach:
- Use first row and first column as markers.
- Use two flags for whether the original first row or first column contain zeros.
- Mark zeros in the matrix itself, then zero out accordingly.
- Time complexity: O(m*n)
- Space complexity: O(1)

Refer to the previously provided optimal code for implementation details.

-----------------------------------------------------------------
Summary:
- Better approach uses extra O(m+n) space but simpler logic.
- Optimal approach minimizes space to O(1) using the matrix itself for markers.
- Both have the same time complexity O(m*n).




---

Optimal Approach (In-Place, O(1) Extra Space):
----------------------------------------------
Intuition:
- Use first row and first column of the matrix as markers.
- Additional flags track whether first row and first column should be zeroed.

Detailed Steps:
1. Check if first row contains zero → store in `firstRowZero`.
2. Check if first column contains zero → store in `firstColZero`.
3. Iterate through matrix (excluding first row and column):
   - If matrix[i][j]==0, mark row and column by setting matrix[i][0]=0 and matrix[0][j]=0.
4. Iterate again (excluding first row and column):
   - Set matrix[i][j]=0 if either row or column is marked.
5. If `firstRowZero` true, zero out entire first row.
6. If `firstColZero` true, zero out entire first column.

Why this order:
- Avoid prematurely zeroing first row/column, which affects markers.

Time Complexity:
- O(m*n)

Space Complexity:
- O(1)

---

Extra Explanation for Optimal Approach:
--------------------------------------
- Using the first row and column as marker arrays avoids extra space.
- Marking is done before actual zeroing to prevent contamination.
- Careful handling of first row and column is essential as they double as data and markers.
- `firstRowZero` and `firstColZero` ensure we don't lose info about original zeros in first row/column.
- Final zeroing of first row/column done at last to maintain correctness.

---

Example Dry Run (Optimal):
--------------------------
Input:
[
 [1,1,1],
 [1,0,1],
 [1,1,1]
]

- firstRowZero: false (no zero in first row)
- firstColZero: false (no zero in first column)
- Mark positions:
  - matrix[1][1]==0 → matrix[1][0]=0, matrix[0][1]=0
- Now matrix:
[
 [1,0,1],
 [0,0,1],
 [1,1,1]
]
- Zero matrix cells where row or column marked:
  - i=1, j=1: zeroed (already zero)
  - i=1, j=0: zeroed (marker)
  - i=0, j=1: zeroed (marker)
- Final step: firstRowZero, firstColZero false → no change.
- Output:
[
 [1,0,1],
 [0,0,0],
 [1,0,1]
]

---

Code Implementation (Optimal):

*/

#include <vector>
using namespace std;

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        bool firstRowZero = false, firstColZero = false;

        // Step 1: Check first row for zero
        for (int j = 0; j < n; j++) {
            if (matrix[0][j] == 0) {
                firstRowZero = true;
                break;
            }
        }

        // Step 2: Check first column for zero
        for (int i = 0; i < m; i++) {
            if (matrix[i][0] == 0) {
                firstColZero = true;
                break;
            }
        }

        // Step 3: Use first row and column as markers for rows and columns to zero
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0;  // mark row
                    matrix[0][j] = 0;  // mark column
                }
            }
        }

        // Step 4: Zero matrix cells based on marks
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }

        // Step 5: Zero first row if needed
        if (firstRowZero) {
            for (int j = 0; j < n; j++) {
                matrix[0][j] = 0;
            }
        }

        // Step 6: Zero first column if needed
        if (firstColZero) {
            for (int i = 0; i < m; i++) {
                matrix[i][0] = 0;
            }
        }
    }
};

/*
Summary:
- Brute force: high time complexity, placeholder needed, complex.
- Better: extra arrays mark rows and columns; straightforward, O(m+n) space.
- Optimal: use matrix itself as marker, carefully handle first row/col, O(1) space.
- Optimal approach best suits interview expectations.
*/ 
