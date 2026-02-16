https://leetcode.com/problems/rotting-oranges/description/

/*
===========================================================================================
PROBLEM: Rotten Oranges (Minimum Time to Rot All Oranges)
===========================================================================================

-------------------------------------------------------------------------------------------
1. QUESTION EXPLANATION: [00:00:13]
-------------------------------------------------------------------------------------------
You are given a 2D grid:
- 0: Empty cell
- 1: Fresh orange
- 2: Rotten orange
A rotten orange can rot its 4-directional neighbors (Up, Down, Left, Right) in 1 unit of time.
You need to find the MINIMUM time required to rot all fresh oranges. If it's impossible, return -1.

-------------------------------------------------------------------------------------------
2. INTUITION & STRATEGY: [00:06:20]
-------------------------------------------------------------------------------------------
- Why BFS? [00:06:28] Since rotting happens simultaneously in all directions, this is a 
  "Level-Order Traversal" problem. BFS explores all nodes at distance '1' first, then distance '2', 
  guaranteeing the minimum time.
- DFS would go deep into one path first, taking much longer (O(N*M) time per path), which doesn't 
  match the simultaneous nature of rotting. [00:06:52]

-------------------------------------------------------------------------------------------
3. CORE LOGIC: [00:07:30]
-------------------------------------------------------------------------------------------
- INITIALIZATION: Find all starting rotten oranges and push them into a Queue.
- TRACKING: We need to count total oranges to verify at the end if all became rotten. [00:19:25]
- SIMULTANEOUS PROCESSING: Use a nested loop or a time variable to track "levels" in BFS.

-------------------------------------------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    // Directions for 4-neighbors: {Up, Right, Down, Left} [00:15:33]
    vector<int> delRow = {-1, 0, 1, 0};
    vector<int> delCol = {0, 1, 0, -1};
    
    // Boundary check helper
    bool isValid(int &i, int &j, int &n, int &m) {
        if(i < 0 || i >= n) return false;
        if(j < 0 || j >= m) return false;
        return true;
    }
    
public:
    int orangesRotting(vector<vector<int>> &grid){
        int n = grid.size();
        int m = grid[0].size();
        
        int time = 0;   // Result: Minimum minutes
        int total = 0;  // Total fresh + rotten oranges [00:19:35]
        int count = 0;  // Count of oranges that actually rot
        
        // BFS Queue to store {row, col}
        queue<pair<int,int>> q;
        
        // Step 1: Initial Scan [00:13:45]
        for(int i=0; i < n; i++) {
            for(int j=0; j < m; j++) {
                // If it's an orange (fresh or rotten), count it
                if(grid[i][j] != 0) total++;
                
                // If it's already rotten, add to queue to start BFS [00:14:07]
                if(grid[i][j] == 2) {
                    q.push({i, j});
                }
            }
        }
        
        // Step 2: Multi-Source BFS [00:14:29]
        while(!q.empty()) {
            int k = q.size(); // Number of oranges rotting neighbors right now
            count += k;
            
            // Process current level (all oranges rotting at this specific minute)
            while(k--) {
                auto cell = q.front();
                q.pop();
                
                int row = cell.first;
                int col = cell.second;
                
                // Check all 4 neighbors [00:16:58]
                for(int i=0; i < 4; i++) {
                    int nRow = row + delRow[i]; 
                    int nCol = col + delCol[i]; 
                    
                    // If neighbor is valid and is a FRESH orange
                    if(isValid(nRow, nCol, n, m) && grid[nRow][nCol] == 1) {
                        grid[nRow][nCol] = 2; // Rot it!
                        q.push({nRow, nCol}); // Add to queue for next minute
                    }
                }
            }
            
            // Increment time only if more oranges were rotted in this step [00:18:22]
            if(!q.empty()) time++;
        }
        
        // Step 3: Final Verification [00:18:41]
        // If the number of oranges we processed equals the total oranges, return time.
        // Otherwise, some fresh oranges were unreachable. [00:05:16]
        if(total == count) return time;
        return -1;
    }
};

/*
-------------------------------------------------------------------------------------------
4. COMPLEXITY ANALYSIS: [00:20:50]
-------------------------------------------------------------------------------------------
- Time Complexity: O(N * M)
    - Initial scan takes O(N * M).
    - BFS visits each cell at most once. For each cell, 4 neighbors are checked.
- Space Complexity: O(N * M)
    - In the worst case, the queue can store all cells.

-------------------------------------------------------------------------------------------
5. DRY RUN EXAMPLE: [00:01:00]
-------------------------------------------------------------------------------------------
Grid: [[2,1,1], [1,1,0], [0,1,1]]
- Min 0: Q = {(0,0)}, Total Oranges = 7
- Min 1: (0,0) rots (0,1) and (1,0). Q = {(0,1), (1,0)}. Time = 1.
- Min 2: (0,1) rots (0,2). (1,0) rots (1,1). Q = {(0,2), (1,1)}. Time = 2.
... and so on until all reachable oranges are rotten.
===========================================================================================
*/