https://leetcode.com/problems/online-stock-span/description/


/*
===========================================================================================
PROBLEM: Online Stock Span
===========================================================================================

-------------------------------------------------------------------------------------------
1. QUESTION EXPLANATION: [00:00:14]
-------------------------------------------------------------------------------------------
The stock span for a day is defined as the maximum number of consecutive days 
(starting from today and going backward) for which the stock price was less than or equal 
to today's price.

Example:
Prices: [100, 80, 60, 70, 60, 75, 85]
Spans:  [ 1,  1,  1,  2,  1,  4,  6]

-------------------------------------------------------------------------------------------
2. APPROACH 1: BRUTE FORCE [00:03:32]
-------------------------------------------------------------------------------------------
- Logic: Store all prices in a list. For every 'next' call, traverse backward 
  from the current index and count how many prices are <= the current price.
- Intuition: Simple linear search.
- Complexity:
    - Time: O(Days) for each next() call. [00:07:28]
    - Space: O(N) to store the history.
*/

#include <vector>
#include <stack>
#include <climits>

using namespace std;

class StockSpannerBrute {
    vector<int> prices;

public:
    StockSpannerBrute() {}

    int next(int price) {
        int span = 1;
        // Iterate backward through stored prices [00:06:18]
        for (int i = prices.size() - 1; i >= 0; i--) {
            if (prices[i] <= price) {
                span++;
            } else {
                break; // Stop at the first greater price [00:06:46]
            }
        }
        prices.push_back(price);
        return span;
    }
};

/*
-------------------------------------------------------------------------------------------
3. APPROACH 2: MONOTONIC STACK (Optimized) [00:08:13]
-------------------------------------------------------------------------------------------
- Logic: We are essentially looking for the "Previous Greater Element" (PGE). [00:10:06]
  The span is: (Current Index) - (Index of Previous Greater Element).
- Intuition: If a price is smaller than today's price, it will NEVER be the 
  Previous Greater Element for any future day. So, we can "pop" it from our 
  stack to save time. [00:13:16]
- Complexity:
    - Time: O(1) Amortized (each element is pushed and popped at most once). [00:18:08]
    - Space: O(N) in the worst case.
*/

class StockSpanner {
    // stack stores {price, index} [00:11:18]
    stack<pair<int, int>> st;
    int index;

public:
    StockSpanner() {
        index = -1; // Initialize index [00:15:40]
    }

    int next(int price) {
        index++; // Increment index for the new incoming price [00:16:15]

        // Pop elements while the stack top price is <= current price [00:16:24]
        while (!st.empty() && st.top().first <= price) {
            st.pop();
        }

        int ans;
        if (st.empty()) {
            // No previous greater element: span is from the very beginning [00:16:52]
            ans = index - (-1); //this is especially done for day 1 is counted as 1
        } else {
            // Span is distance to the previous greater element [00:17:00]
            ans = index - st.top().second;
        }

        // Push current price and its index for future days [00:17:08]
        st.push({price, index});

        return ans;
    }
};

/*
-------------------------------------------------------------------------------------------
4. DRY RUN (Optimized Approach): [00:11:02]
-------------------------------------------------------------------------------------------
Price: 100 | index: 0 | stack: empty -> push(100, 0) | span: 0 - (-1) = 1
Price: 80  | index: 1 | stack: (100,0) -> push(80, 1) | span: 1 - 0 = 1
Price: 60  | index: 2 | stack: (100,0),(80,1) -> push(60, 2) | span: 2 - 1 = 1
Price: 70  | index: 3 | stack: (100,0),(80,1) (popped 60) -> push(70, 3) | span: 3 - 1 = 2
Price: 60  | index: 4 | stack: ..., (70,3) -> push(60, 4) | span: 4 - 3 = 1
Price: 75  | index: 5 | stack: (100,0),(80,1) (popped 60, 70) -> push(75, 5) | span: 5 - 1 = 4
===========================================================================================
*/