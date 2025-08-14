// Best Time to Buy and Sell Stock (LeetCode 121)
// ✅ Find the maximum profit from one buy-and-sell transaction
// Language: C++
// Approach: Greedy single-pass tracking of minimum price so far

/*
Problem:
--------
You are given an array 'prices' where prices[i] is the price of a stock on the i-th day.
You may choose a single day to buy one stock and a different day in the future to sell it.
Return the maximum profit you can achieve from this transaction.
If no profit is possible (prices falling), return 0.

Constraints:
------------
1 <= prices.length <= 10^5
0 <= prices[i] <= 10^4

---

Intuition & Logic:
------------------
- To maximize profit, for each day (sell day) we want to know the minimum stock price seen before it (buy day).
- The profit if sold today = prices[i] - minPriceSoFar.
- By keeping track of minPriceSoFar as we iterate, we can compute profit for each day in O(1) time.
- Update maximum profit whenever we find a higher profit.
- This works because we only buy before we sell (minPriceSoFar ≤ current day index).

Why It Works:
-------------
- At every step, you're considering the best "buy" seen so far and the current price as "sell".
- If prices go down, minPriceSoFar gets updated — so you always buy at the lowest possible rate before any sell day.
- Greedy nature: locally optimal choice (min buy so far) leads to global optimal profit for one transaction.

Algorithm Steps:
----------------
1. Initialize `mini` as prices[0] and `maxprofit` as 0.
2. Iterate from day 1 to last day:
   - cost = prices[i] - mini      -> potential profit by selling today.
   - maxprofit = max(maxprofit, cost)
   - mini = min(mini, prices[i])  -> update min price to buy for future days.
3. Return maxprofit.

---

Time Complexity:
----------------
- O(n) : Single loop through prices.

Space Complexity:
-----------------
- O(1) : Only constant extra variables used.

Edge Cases:
-----------
- Prices always decrease → maxprofit = 0
- Prices always increase → buy on day 0, sell on last day
- Single day prices → profit is 0

*/

// ---------------------- Core Code Implementation ----------------------

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int mini = prices[0];
        int maxprofit = 0;

        for (int i = 1; i < prices.size(); i++) {
            int cost = prices[i] - mini;               // profit if sold today
            maxprofit = max(maxprofit, cost);          // update max profit
            mini = min(mini, prices[i]);               // update min buying price
        }

        return maxprofit;
    }
};
