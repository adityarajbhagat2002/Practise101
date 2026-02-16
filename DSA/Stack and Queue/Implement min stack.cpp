https://leetcode.com/problems/min-stack/

/*
===========================================================================================
PROBLEM: Min Stack (Design a stack with O(1) getMin)
===========================================================================================

-------------------------------------------------------------------------------------------
1. THE CHALLENGE: [00:00:13]
-------------------------------------------------------------------------------------------
A standard stack only gives us the Top element. If we want the Minimum, we would 
normally have to scan the whole stack (O(N)). To get it in O(1), we must store 
extra information during the push operation.

-------------------------------------------------------------------------------------------
2. APPROACH 1: THE PAIR METHOD (Intuitive) [00:01:55]
-------------------------------------------------------------------------------------------
- Logic: Each element in the stack "carries" the minimum value seen so far.
- Intuition: If the stack is [12, 15, 10], we store:
    - {12, 12} -> (12 is min)
    - {15, 12} -> (12 is still min)
    - {10, 10} -> (10 is the new min)
- Space: O(2N) 
*/

#include <iostream>
#include <stack>
#include <vector>
#include <climits>

using namespace std;

class MinStackPair {
private:
    // pair.first = actual value, pair.second = min at this level [00:02:03]
    stack<pair<int, int>> st;

public:
    void push(int val) {
        if (st.empty()) {
            st.push({val, val}); // First element is its own min [00:02:27]
        } else {
            // Compare current val with the "min so far" at the top [00:05:17]
            int currentMin = min(val, st.top().second);
            st.push({val, currentMin});
        }
    }

    void pop() { st.pop(); }

    int top() { return st.top().first; }

    int getMin() { return st.top().second; }
};

/*
-------------------------------------------------------------------------------------------
3. APPROACH 2: THE MATHEMATICAL TRICK (Space Optimized) [00:07:16]
-------------------------------------------------------------------------------------------
- Logic: Use a single integer stack. If a new minimum is found, store a 
  "modified value" instead of the actual value.
- Formula to Push: modified value = 2 * (New Value) - (Old Minimum) [00:09:47]
- Formula to Pop (Retrieve Old Min): 2 * (Current Min) - (Stored Value) [00:11:30]
- Intuition: The modified value acts as a marker. Whenever the value in the 
  stack is LESS than our current minimum, it’s a sign that the minimum was 
  updated at that point. [00:14:41]

- Space: O(N) 
*/



class MinStackOptimized {
private:
    stack<long long> st; // Use long long to handle formula overflow [00:15:46]
    long long mini;

public:
    MinStackOptimized() {
        mini = LLONG_MAX;
    }

    void push(int value) {
        long long val = value;
        if (st.empty()) {
            mini = val;
            st.push(val);
        } else {
            if (val < mini) {
                // We store a value smaller than 'val' to mark the change [00:16:37]
                st.push(2 * val - mini);
                mini = val; // Update the actual minimum
            } else {
                st.push(val); // Push normally
            }
        }
    }

    void pop() {
        if (st.empty()) return;
        long long topVal = st.top();
        st.pop();

        if (topVal < mini) {
            // This was a "marker" value. We must restore the previous min [00:18:00]
            mini = 2 * mini - topVal;
        }
    }

    int top() {
        if (st.empty()) return -1;
        long long topVal = st.top();
        
        // If topVal is a marker (topVal < mini), the actual value is mini [00:18:53]
        if (topVal < mini) return (int)mini;
        return (int)topVal;
    }

    int getMin() {
        return (int)mini;
    }
};

/*
-------------------------------------------------------------------------------------------
4. COMPARISON TABLE: [00:19:36]
-------------------------------------------------------------------------------------------
| Feature         | Pair Approach       | Optimized Approach |
|-----------------|---------------------|-------------------|
| Time Complexity | O(1)                | O(1)              |
| Space Complexity| O(2N)               | O(N)              |
| Complexity      | Low                 | High              |
| Risk            | None                | Integer Overflow  |

-------------------------------------------------------------------------------------------
5. DRY RUN (Optimized Approach): [00:08:00]
-------------------------------------------------------------------------------------------
1. Push(12): st:[12], mini:12
2. Push(15): st:[12, 15], mini:12 (15 > 12, push normal)
3. Push(10): st:[12, 15, 8], mini:10 
   (Formula: 2*10 - 12 = 8. Since 8 < 10, it's our marker.)
4. getMin(): returns 10.
5. Pop(): top is 8. 8 < 10, so restore mini = 2*10 - 8 = 12.
===========================================================================================
*/