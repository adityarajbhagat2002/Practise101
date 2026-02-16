https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/description/


/*
===========================================================================================
TOPIC: TWO POINTERS & SLIDING WINDOW
PROBLEM: MAXIMUM POINTS YOU CAN OBTAIN FROM CARDS
===========================================================================================
Source: take U forward (Striver - L2)
Pattern: Sliding Window (Variable Ends)
Complexity: 
- Time: O(2 * k) -> Each pointer moves at most k times.
- Space: O(1)   -> No extra data structures used.

-------------------------------------------------------------------------------------------
WINDOW INTUITION: THE "SHRINK & EXPAND" STRATEGY
- Problem Constraint: We can only pick from the ends (Front or Back).
- Fixed Total Picks: We must pick exactly 'k' elements.
- Initial Window: We start by picking all 'k' cards from the leftmost side.
- Window Shift:
    1. Shrink: We remove one card from the right-end of our "Left Window."
    2. Expand: We add one card from the right-end of the "Original Array."
- Goal: By shifting cards from the 'Left Sum' to the 'Right Sum' one by one, 
  we evaluate every possible combination of Front + Back picks in O(k) time.



-------------------------------------------------------------------------------------------
POINTER COORDINATION:
- Left Pointer (i): Starts at (k-1) and moves toward 0. It "releases" cards.
- Right Pointer (rightIndex): Starts at (n-1) and moves toward (n-k). It "grabs" cards.
===========================================================================================
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int n = cardPoints.size();
        int leftsum = 0;
        int rightsum = 0;
        int maxPoints = 0;

        // 1. Initial Window: Pick all 'k' cards from the left end
        // Window Range: [0 ... k-1]
        for (int i = 0; i < k; i++) {
            leftsum += cardPoints[i];
        }
        
        // This is our first possible score
        maxPoints = leftsum;

        // 2. Sliding the Window: 
        // We "shrink" the left side and "expand" the right side
        int rightIndex = n - 1;
        
        // i starts at the last picked card from the left (k-1)
        for (int i = k - 1; i >= 0; i--) {
            // Remove the i-th card from our left picks
            leftsum -= cardPoints[i];
            
            // Add a card from the very end of the array
            rightsum += cardPoints[rightIndex];
            
            // Move right pointer inward for the next iteration
            rightIndex--;
            
            // Update the maximum points found so far
            maxPoints = max(maxPoints, leftsum + rightsum);
        }

        return maxPoints;
    }
};

/*
-------------------------------------------------------------------------------------------
DRY RUN EXAMPLE (cardPoints = [1, 2, 3, 4, 5, 6, 1], k = 3):
-------------------------------------------------------------------------------------------
Step 0: Initial Left Sum (1+2+3) = 6. Max = 6.
Step 1: Remove 3 (LeftSum=3), Add 1 (RightSum=1). Total = 4. Max = 6.
Step 2: Remove 2 (LeftSum=1), Add 6 (RightSum=7). Total = 8. Max = 8.
Step 3: Remove 1 (LeftSum=0), Add 5 (RightSum=12). Total = 12. Max = 12.
Final Result: 12
-------------------------------------------------------------------------------------------
*/


