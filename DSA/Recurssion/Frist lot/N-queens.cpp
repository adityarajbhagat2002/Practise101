/*
===========================================================================================
N-QUEENS: THE DUAL-APPROACH GUIDE
===========================================================================================
Source: CodeStoryWithMIK (YouTube Video 14)
Concept: Backtracking / Hashing / Optimization
Complexity: Time O(N!) | Space O(N^2)

-------------------------------------------------------------------------------------------
PROBLEM DESCRIPTION:
- Place N queens on an N x N board such that no two queens attack each other. [00:01:07]
- Constraints: One queen per Row, Column, and both Diagonals.

-------------------------------------------------------------------------------------------
RECURSIVE INTUITION: THE DIAGONAL CONSTANTS [NEW]
- Anti-Diagonal (/): Moving along this path means as Row increases, Col decreases. 
  Mathematically, their sum remains identical (Row + Col = Constant). 
  This creates a unique "ID" for every anti-diagonal.
- Main Diagonal (\): Moving along this path means both Row and Col increase/decrease 
  together. Mathematically, their displacement remains identical (Row - Col = Constant). 
  This creates a unique "ID" for every main diagonal.
- Efficiency: Storing these "IDs" in HashSets replaces an O(N) scan with an O(1) lookup.

-------------------------------------------------------------------------------------------
THE BACKTRACKING STORY:
1. Row Selection: Process row by row (0 to N-1). [00:06:50]
2. Safe Check: Use either traditional scanning (Appr 1) or HashSet IDs (Appr 2).
3. Decision: If (row, col) is safe, place 'Q' and recurse to row + 1.
4. Backtrack: Remove 'Q' (replace with '.') and unmark the IDs before trying next col.
===========================================================================================
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

class Solution {
public:
    vector<vector<string>> result;

    // --- APPROACH 1: TRADITIONAL VALIDATION [00:44:30] ---
    // Scans board manually in O(N) time.
    bool isSafe(vector<string>& board, int row, int col, int n) {
        // Check Column Upwards
        for (int i = row - 1; i >= 0; i--) {
            if (board[i][col] == 'Q') return false;
        }
        // Check Upper-Left Diagonal (\)
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 'Q') return false;
        }
        // Check Upper-Right Diagonal (/)
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
            if (board[i][j] == 'Q') return false;
        }
        return true;
    }

    // --- APPROACH 2: HASHSET OPTIMIZATION [01:04:15] ---
    // Uses constant properties for O(1) lookup.
    unordered_set<int> cols;
    unordered_set<int> diags;      // Row - Col = Constant
    unordered_set<int> antiDiags;  // Row + Col = Constant

    void solve(vector<string>& board, int row, int n, bool useOptimized) {
        if (row == n) {
            result.push_back(board);
            return;
        }

        for (int col = 0; col < n; col++) {
            if (useOptimized) {
                int dID = row - col;
                int adID = row + col;

                if (cols.count(col) || diags.count(dID) || antiDiags.count(adID)) 
                    continue;

                // Mark
                board[row][col] = 'Q';
                cols.insert(col); diags.insert(dID); antiDiags.insert(adID);

                solve(board, row + 1, n, true);

                // Backtrack (Unmark)
                board[row][col] = '.';
                cols.erase(col); diags.erase(dID); antiDiags.erase(adID);
            } 
            else {
                // Traditional Logic
                if (isSafe(board, row, col, n)) {
                    board[row][col] = 'Q';
                    solve(board, row + 1, n, false);
                    board[row][col] = '.'; // Backtrack
                }
            }
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        result.clear();
        vector<string> board(n, string(n, '.'));
        
        // Toggle 'true' for optimized O(1) check, 'false' for O(N) check
        solve(board, 0, n, true); 
        
        return result;
    }
};