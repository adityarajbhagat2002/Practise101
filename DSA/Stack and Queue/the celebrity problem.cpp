https://www.geeksforgeeks.org/problems/the-celebrity-problem/1


/*
===========================================================================================
PROBLEM: The Celebrity Problem
===========================================================================================

-------------------------------------------------------------------------------------------
1. DEFINITION OF A CELEBRITY: [00:01:19]
-------------------------------------------------------------------------------------------
- Everyone knows him. (Column count for celebrity index must be N-1)
- He knows no one. (Row count for celebrity index must be 0)
- Note: Diagonal is always 0 because a person doesn't "know" themselves in this context.

-------------------------------------------------------------------------------------------
2. APPROACH 1: NAIVE (Extra Space) [00:02:13]
-------------------------------------------------------------------------------------------
- Logic: Use two arrays to keep track of:
    1. knowMe[i]: How many people know person 'i'.
    2. Iknow[i]: How many people person 'i' knows.
- Intuition: Traverse the entire N x N matrix. If M[i][j] == 1, increment Iknow[i] and knowMe[j].
- Complexity: [00:07:22]
    - Time: O(N^2) to traverse the matrix.
    - Space: O(2N) to store the two arrays.
*/

#include <vector>
using namespace std;

class SolutionNaive {
public:
    int celebrity(vector<vector<int>> &M) {
        int n = M.size();
        vector<int> knowMe(n, 0), Iknow(n, 0);
        
        for(int i=0; i < n; i++) {
            for(int j=0; j < n; j++) {
                if(M[i][j] == 1) {
                   
                    Iknow[i]++;

                    knowMe[j]++;
                }
            }
        }
        
        for(int i=0; i < n; i++) {
            // A celebrity is known by n-1 people and knows 0 people [00:05:08]
            if(knowMe[i] == n-1 && Iknow[i] == 0) {
                return i;  
            }
        }
        return -1;
    }
};

/*
-------------------------------------------------------------------------------------------
3. APPROACH 2: OPTIMIZED TWO-POINTER (Elimination Strategy) [00:07:49]
-------------------------------------------------------------------------------------------
- Logic: Start with two pointers, 'top' at 0 and 'down' at n-1. 
- Elimination Rule: [00:10:00]
    - If top knows down (M[top][down] == 1): top CANNOT be a celebrity. Move top++.
    - If down knows top (M[down][top] == 1): down CANNOT be a celebrity. Move down--.
    - If both don't know each other: Neither can be a celebrity. top++, down--.
- Intuition: At each step, we eliminate at least one person who cannot be the celebrity.
- Final Check: Since elimination only finds a *potential* candidate, we must verify the 
  candidate's row is all 0s and column is all 1s (except diagonal). [00:11:51]
- Complexity: [00:15:34]
    - Time: O(2N) -> O(N) (Elimination + Final Verification).
    - Space: O(1) (No extra arrays).
*/

class SolutionOptimized {
public:
    int celebrity(vector<vector<int>> &M) {
        int n = M.size();
        int top = 0, down = n-1;
        
        // Step 1: Eliminate candidates [00:12:35]
        while(top < down) {
            if(M[top][down] == 1) {
                top++; // Top knows someone, so top is not celebrity
            }
            else if(M[down][top] == 1) {
                down--; // Down knows someone, so down is not celebrity
            }
            else {
                // Neither knows the other, neither can be celebrity [00:13:43]
                top++;
                down--;
            }
        }
        
        // No candidate found
        if(top > down) return -1;
        
        // Step 2: Verification of the potential candidate (top) [00:14:15]
        for(int i=0; i < n; i++) {
            if(i == top) continue; // Skip diagonal [00:15:16]
            
            // it's like it is asking each time does I knows the top which should be 1 for top to be celebrity
            // and also does top knows i which should be 0 because celebrity doesn't know anyone  
            // but in this it is just checking the opposite to return -1 at any instrance it satisfies this statement 
            // it will return -1
            if( M[top][i] == 1 ||  M[i][top] == 0  ) {
                return -1;
            }
        }
        
        return top;
    }
};

/*
-------------------------------------------------------------------------------------------
4. KEY INSIGHTS:
-------------------------------------------------------------------------------------------
- There can be at most ONE celebrity in any group. [00:08:44]
- Proof: If X and Y are both celebrities, then X must know Y (everyone knows Y), 
  but X is a celebrity and knows no one. This is a contradiction! [00:09:05]
===========================================================================================
*/