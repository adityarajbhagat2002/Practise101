https://leetcode.com/problems/pascals-triangle/description/
/*
Pascal's Triangle: Types, Logic, Intuition, and Solutions
=========================================================
Based on TakeUForward's video "Pascal Triangle | Finding nCr in minimal time"

---------------------------------------------------------
Types of Pascal’s Triangle Questions

- Type 1: Find the Element at Row R and Column C
    - Given row (R) and column (C), return the value at that position in Pascal’s Triangle.
- Type 2: Print the Nth Row
    - Return or print the complete Nth row of Pascal’s Triangle.
- Type 3: Print the Entire Triangle up to N Rows
    - Generate and return/print Pascal’s Triangle with N rows, i.e., the full pattern.

---------------------------------------------------------
Logic, Tricks, and Intuition

Pascal’s Triangle Structure:
- Each row starts and ends with 1.
- Each inner element at position (i, j) is the sum of the two above:
    arr[i][j] = arr[i-1][j-1] + arr[i-1][j]
- Value at row r, col c = nCr(r-1, c-1) = (r-1)! / ((c-1)! * ((r-1)-(c-1))!)
- Pascal’s triangle entries correspond to binomial coefficients.

---------------------------------------------------------
Brute Force and Optimal Code Strategies

Type 1: Element at R, C

Brute Force:
- Generate the full triangle row by row and fetch (R, C).
- Drawback: Inefficient for large N, O(N^2) time and space.

Optimal (Trick):
- Direct computation:
    nCr(n, r) = n! / (r! * (n-r)!)
- To optimize:
    - result = 1
    - For i = 0 to r-1:
        result = result * (n-i) / (i+1)
- O(r) time, O(1) space.

Sample Code:
*/

long long nCr(int n, int r) {
    long long res = 1;
    for(int i = 0; i < r; i++) {
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}

/*
Use n = R-1, r = C-1 for Pascal’s indexing.

Type 2: Print the nth Row

Brute Force:
- For each column c in 1 to n, use nCr(n-1, c-1) to build the row, O(n^2).

Optimal (Trick):
- Next element can be derived from the previous:
    ans = 1 (first element)
    For each col from 1 to n-1:
        ans = ans * (n - col) / col
    Push ans to row.
- O(n) time, O(1) space per row.

Sample Code:
*/

#include <vector>
using namespace std;

vector<int> generateRow(int row) {
    long long ans = 1;
    vector<int> ansRow;
    ansRow.push_back(1);
    for(int col = 1; col < row; col++) {
        ans = ans * (row - col);
        ans = ans / col;
        ansRow.push_back(ans);
    }
    return ansRow;
}

/*
Type 3: Print the Entire Triangle up to N Rows

Brute Force:
- Nested loops: for each row, for each column, compute nCr for each, O(n^3).

Optimal (Trick):
- For each row from 1 to N, use optimized row-generation from Type 2.
- Store each row in an answer vector, yielding total O(N^2) time and space.

Sample Code:
*/

vector<vector<int>> generate(int numRows) {
    vector<vector<int>> ans;
    for(int i = 1; i <= numRows; i++) {
        ans.push_back(generateRow(i));
    }
    return ans;
}

/*
---------------------------------------------------------
Final C++ Code (modular, optimal)
*/

class Solution {
public:
    vector<int> generateRow(int row) {
        long long ans = 1;
        vector<int> ansRow;
        ansRow.push_back(1);
        for(int col = 1; col < row; col++) {
            ans = ans * (row - col);
            ans = ans / col;
            ansRow.push_back(ans);
        }
        return ansRow;
    }

    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> ans;
        for(int i = 1; i <= numRows; i++) {
            ans.push_back(generateRow(i));
        }
        return ans;
    }
};

/*
---------------------------------------------------------
Coding and Interview Notes

- Always use the largest integral type to avoid overflow (`long long`).
- For interviews, break logic into clear, modular functions (e.g., generateRow).
- Code for clarity and readability, not just function.

---------------------------------------------------------

All important types, methods, optimizations, tricks, formulas, as well as detailed sample code and 
coding tips from the video are covered above with clear transitions from brute force to optimal approaches.
*/
