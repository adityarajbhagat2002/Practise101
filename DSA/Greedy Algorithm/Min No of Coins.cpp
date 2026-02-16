https://www.geeksforgeeks.org/problems/-minimum-number-of-coins4426/1

/*
===========================================================================================
PROBLEM: MINIMUM NUMBER OF COINS (Indian Denominations)
===========================================================================================

-------------------------------------------------------------------------------------------
1. LOGIC AND INTUITION: [00:02:34]
-------------------------------------------------------------------------------------------
- The goal is to make change for 'N' using the fewest coins possible.
- GREEDY STRATEGY: Always pick the largest possible denomination that is less than or 
  equal to the remaining amount. [00:03:11]
- WHY IT WORKS: In systems like Indian Currency (1, 2, 5, 10, 20, 50, 100, 500, 2000), 
  the greedy approach is optimal. However, in some custom systems, you might need 
  Dynamic Programming. [00:08:06]

-------------------------------------------------------------------------------------------
2. STEPS OF THE ALGORITHM: [00:03:38]
-------------------------------------------------------------------------------------------
1. Define the sorted array of available denominations. [00:00:14]
2. Start from the largest denomination (right to left). [00:09:24]
3. While the current denomination can be subtracted from 'N':
   - Subtract the denomination from 'N'.
   - Add the denomination to our result list (or increment a counter). [00:09:43]
4. Move to the next smaller denomination and repeat until N becomes 0.

-------------------------------------------------------------------------------------------
3. SPACE AND TIME COMPLEXITY: [00:06:04]
-------------------------------------------------------------------------------------------
- Time Complexity: O(V), where V is the value. In the worst case (if we only had 1 Rs coins), we'd loop V times. However, with larger notes, it's much faster. [00:06:15]
- Space Complexity: O(1) if we only return the count, or O(N) to store the list of coins used. [00:06:46]

-------------------------------------------------------------------------------------------
4. CODE IMPLEMENTATION (C++):
-------------------------------------------------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    // This function returns the list of coins used to make the sum 'n'
    vector<int> minCoinsList(int n) {
        // Standard Indian Currency Denominations [00:00:14]
        int coins[] = {1, 2, 5, 10, 20, 50, 100, 200, 500, 2000};
        int s = sizeof(coins) / sizeof(coins[0]);
        
        vector<int> result;

        // Traverse denominations from largest to smallest [00:03:38]
        for (int i = s - 1; i >= 0; i--) {
            
            // While the current coin can be part of the change [00:09:43]
            while (n >= coins[i]) {
                n -= coins[i];           // Reduce the remaining amount
                result.push_back(coins[i]); // Store the coin used [00:05:53]
            }
            
            // Optimization: If n becomes 0, no need to check smaller coins
            if (n == 0) break;
        }
        
        return result;
    }

    // Simplified version to just find the COUNT of coins (as per your request)
    int findMin(int n) {
        int coins[] = {1, 2, 5, 10, 20, 50, 100, 200, 500, 2000};
        int s = 10;
        int count = 0;

        for (int i = s - 1; i >= 0; i--) {
            // Subtract as many of the current denomination as possible [00:04:20]
            while (n >= coins[i]) {
                n -= coins[i];
                count++; 
            }
        }
        return count;
    }
};

/*
-------------------------------------------------------------------------------------------
5. DRY RUN EXAMPLE: [00:03:38]
-------------------------------------------------------------------------------------------
Input: N = 49
1. Check 2000, 500, 100, 50 -> All > 49.
2. Check 20: 49 >= 20. New N = 29. Count = 1.
3. Check 20 again: 29 >= 20. New N = 9. Count = 2.
4. Check 10: 9 < 10.
5. Check 5: 9 >= 5. New N = 4. Count = 3.
6. Check 2: 4 >= 2. New N = 2. Count = 4.
7. Check 2 again: 2 >= 2. New N = 0. Count = 5. [00:05:40]
Result: 5 coins {20, 20, 5, 2, 2}
===========================================================================================
*/