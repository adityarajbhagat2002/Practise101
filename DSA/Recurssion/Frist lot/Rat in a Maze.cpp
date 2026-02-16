/*
===========================================================================================
RAT IN A MAZE - THE RECURSIVE PATHFINDER
===========================================================================================
Source: CodeStoryWithMIK (YouTube Video 11)
Concept: Backtracking / Depth First Search (DFS)
Complexity: Time O(3^(n^2)) | Space O(n^2) [Stack Depth]

-------------------------------------------------------------------------------------------
PROBLEM DESCRIPTION:
- A rat starts at (0, 0) and must reach (n-1, n-1) in an n x n grid.
- maze[i][j] == 1 means path is open; maze[i][j] == 0 means it's a wall.
- The rat can move: Down (D), Left (L), Right (R), and Up (U). [00:01:59]
- Constraint: No cell can be visited more than once in a single path. [00:02:54]

-------------------------------------------------------------------------------------------
THE BACKTRACKING STORY:
1. Is it Safe? Before moving, check if the cell is within bounds and is a '1'. [00:05:59]
2. Mark Your Path: To avoid walking in circles, mark the current cell as '0' (visited) 
   before moving to the next one. [00:07:51]
3. Explore: Try all 4 directions in a specific order (usually Lexicographical: D, L, R, U).
4. Unmark (Backtrack): Once all directions are explored, mark the cell back to '1' 
   so other potential paths can use it. [00:13:17]

-------------------------------------------------------------------------------------------
TIME COMPLEXITY INTUITION: [00:32:25]
- Each cell has 4 directions, but since we don't go back to the cell we just came from,
  there are effectively 3 choices per cell.
- With n^2 cells, the complexity is approximately O(3^(n^2)).
===========================================================================================
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<string> result;

    // Helper to check if the rat can step on cell (i, j) [00:28:57]
    bool isSafe(int i, int j, int n, vector<vector<int>>& maze) {
        return (i >= 0 && i < n && j >= 0 && j < n && maze[i][j] == 1);
    }

    void solve(int i, int j, vector<vector<int>>& maze, int n, string &temp) {
        // 1. Base Case: If not safe (out of bounds or wall), stop this path [00:29:16]
        if (!isSafe(i, j, n, maze)) {
            return;
        }

        // 2. Destination Reached: Save the path and return [00:30:40]
        if (i == n - 1 && j == n - 1) {
            result.push_back(temp);
            return;
        }

        // 3. Mark the current cell as visited (0) to prevent cycles [00:19:28]
        maze[i][j] = 0;

        // 4. Explore all 4 directions [00:24:22]

        // Move Down
        temp.push_back('D');
        solve(i + 1, j, maze, n, temp);
        temp.pop_back(); // Backtrack string

        // Move Left
        temp.push_back('L');
        solve(i, j - 1, maze, n, temp);
        temp.pop_back(); // Backtrack string

        // Move Right
        temp.push_back('R');
        solve(i, j + 1, maze, n, temp);
        temp.pop_back(); // Backtrack string

        // Move Up
        temp.push_back('U');
        solve(i - 1, j, maze, n, temp);
        temp.pop_back(); // Backtrack string

        // 5. Backtrack cell: Mark it back as '1' for other paths [00:27:18]
        maze[i][j] = 1;
    }

    vector<string> ratInMaze(vector<vector<int>>& maze) {
        result.clear();
        int n = maze.size();
        
        // Edge case: Start or End is blocked
        if (n == 0 || maze[0][0] == 0 || maze[n-1][n-1] == 0) {
            return {};
        }

        string temp = "";
        solve(0, 0, maze, n, temp);
        return result;
    }
};
/*

CALL STACK FLOW : 
solve(0,0,"")
│
├── D → solve(1,0,"D")
│   │
│   ├── D → solve(2,0,"DD")
│   │   │
│   │   ├── D → solve(3,0,"DDD") ❌ blocked → return
│   │   ├── L → solve(2,-1,"DDL") ❌ out → return
│   │   ├── R → solve(2,1,"DDR")
│   │   │   │
│   │   │   ├── D → solve(3,1,"DDRD")
│   │   │   │   │
│   │   │   │   ├── D → solve(4,1,"DDRDD") ❌ out → return
│   │   │   │   ├── L → solve(3,0,"DDRDL") ❌ blocked → return
│   │   │   │   ├── R → solve(3,2,"DDRDR")
│   │   │   │   │   │
│   │   │   │   │   ├── D → solve(4,2,"DDRDRD") ❌ out → return
│   │   │   │   │   ├── L → solve(3,1,"DDRDRL") ❌ visited → return
│   │   │   │   │   ├── R → solve(3,3,"DDRDRR") ✅ DESTINATION
│   │   │   │   │   │
│   │   │   │   │   │  result.push_back("DDRDRR")
│   │   │   │   │   │
│   │   │   │   │   └── backtrack
│   │   │   │   └── backtrack
│   │   │   └── backtrack
│   │   └── backtrack
│   └── backtrack
│
├── L → solve(0,-1,"L") ❌ out → return
├── R → solve(0,1,"R") ❌ blocked → return
└── U → solve(-1,0,"U") ❌ out → return


*/
