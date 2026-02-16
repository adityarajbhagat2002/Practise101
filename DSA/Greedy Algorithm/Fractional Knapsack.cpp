https://www.geeksforgeeks.org/problems/fractional-knapsack-1587115620/1
/*
===========================================================================================
PROBLEM: FRACTIONAL KNAPSACK (GeeksforGeeks)
===========================================================================================

-------------------------------------------------------------------------------------------
1. LOGIC AND INTUITION: [00:04:15]
-------------------------------------------------------------------------------------------
- The Goal: Maximize the total value in a knapsack with a weight capacity 'W'.
- Greedy Strategy: Calculate the "Value per Unit Weight" (Value/Weight) for each item. [00:04:39]
- Sort items in descending order of this ratio. We want to pick the "densest" value first.
- Unlike the 0/1 Knapsack, here we can take fractions of an item. [00:01:21]

-------------------------------------------------------------------------------------------
2. STEPS OF THE ALGORITHM: [00:08:42]
-------------------------------------------------------------------------------------------
1. Calculate the value-to-weight ratio for every item. [00:04:45]
2. Sort the items based on this ratio in descending order. [00:05:33]
3. Iterate through sorted items:
   - If the item's full weight fits in the bag, take it all and update current weight. [00:12:15]
   - If it doesn't fit completely, take only the remaining capacity's worth (fraction). [00:12:39]
4. Return the total accumulated value.

-------------------------------------------------------------------------------------------
3. SPACE AND TIME COMPLEXITY: [00:08:55]
-------------------------------------------------------------------------------------------
- Time Complexity: O(N log N) for sorting the items. The iteration is O(N).
- Space Complexity: O(N) to store items/ratios (or O(1) if sorting input directly). [00:09:03]

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
    // Custom comparator to sort items by Value/Weight ratio in descending order [00:11:26]
    // We use double to ensure precision during calculation [00:08:18]
    static bool comp(pair<int, int> &a, pair<int, int> &b) {
        double r1 = (double)a.first / a.second; // Ratio for item A
        double r2 = (double)b.first / b.second; // Ratio for item B
        return r1 > r2; // Sort in descending order [00:08:42]
    }

    double fractionalKnapsack(vector<int>& val, vector<int>& wt, int capacity) {
        int n = wt.size();
        
        // Step 1: Bundle value and weight together for sorting [00:11:11]
        vector<pair<int, int>> items;
        for (int i = 0; i < n; i++) {
            items.push_back({val[i], wt[i]});
        }

        // Step 2: Sort items based on their density (value per unit weight) [00:05:33]
        sort(items.begin(), items.end(), comp);

        int currWeight = 0;     // Tracks total weight currently in the knapsack
        double finalValue = 0;  // Tracks total accumulated value [00:11:42]

        // Step 3: Iterate through items greedily [00:11:55]
        for (int i = 0; i < n; i++) {
            // Case A: Entire item can fit in the knapsack [00:12:07]
            if (currWeight + items[i].second <= capacity) {
                currWeight += items[i].second; // Add full weight
                finalValue += items[i].first;  // Add full value
            }
            // Case B: Only a fraction of the item can fit [00:12:39]
            else {
                int rem = capacity - currWeight; // Calculate remaining capacity
                // Add value proportional to the remaining weight we can carry [00:02:23]
                finalValue += ((double)items[i].first / items[i].second) * rem;
                break; // Knapsack is now exactly full, so we stop [00:13:06]
            }
        }

        return finalValue; // Return maximum possible value [00:13:13]
    }
};

/*
-------------------------------------------------------------------------------------------
5. KEY TAKEAWAYS FROM VIDEO:
-------------------------------------------------------------------------------------------
- Sorting is the most important step. Without it, the greedy approach fails. [00:05:33]
- Fractions are only taken for the LAST item that fits. [00:07:34]
- Always use `double` for ratios to avoid precision loss (e.g., 5/2 = 2.5, not 2). [00:08:18]
===========================================================================================
*/