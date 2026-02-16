https://www.geeksforgeeks.org/problems/maximum-sum-combination/1

/*
===========================================================================================
PROBLEM: K MAXIMUM SUM COMBINATIONS (GeeksforGeeks / InterviewBit)
===========================================================================================

-------------------------------------------------------------------------------------------
1. LOGIC AND INTUITION: [00:03:41]
-------------------------------------------------------------------------------------------
- Sorting: We sort both arrays A and B in descending order. This ensures that the largest 
  possible sum is always A[0] + B[0]. [00:04:10]
- Max-Heap: We use a Max-Heap to store potential sums along with the indices (i, j) that 
  created them. [00:05:42]
- Greedy Approach: Starting from (0, 0), the next largest sum could either come from 
  (i+1, j) or (i, j+1). We push these neighbors into the heap. [00:06:43]
- Avoiding Duplicates: Multiple paths can lead to the same index pair (e.g., (1,0) -> (1,1) 
  and (0,1) -> (1,1)). We use a 'Set' to keep track of visited index pairs. [00:05:07]

-------------------------------------------------------------------------------------------
2. TIME AND SPACE COMPLEXITY: [00:18:54]
-------------------------------------------------------------------------------------------
- Time Complexity: O(N log N + K log K)
    - Sorting: O(N log N).
    - Heap Operations: We perform K extractions, each taking O(log K). [00:19:18]
- Space Complexity: O(K)
    - Heap and Set store at most O(K) elements to find the top K combinations. [00:20:13]

-------------------------------------------------------------------------------------------
3. CODE IMPLEMENTATION (C++):
-------------------------------------------------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>

using namespace std;

class Solution {
public:
    vector<int> maxCombinations(int N, int K, vector<int> &A, vector<int> &B) {
        // Step 1: Sort both arrays in descending order [00:13:36]
        sort(A.begin(), A.end(), greater<int>());
        sort(B.begin(), B.end(), greater<int>());

        // Step 2: Max-Heap to store {sum, {index_i, index_j}} [00:12:37]
        // The heap will always give us the current maximum available sum.
        priority_queue<pair<int, pair<int, int>>> pq;

        // Step 3: Set to keep track of visited index pairs (i, j) [00:13:15]
        set<pair<int, int>> visited;

        // Step 4: Start with the largest possible sum [00:14:46]
        pq.push({A[0] + B[0], {0, 0}});
        visited.insert({0, 0});

        vector<int> result;

        // Step 5: Extract K elements from the heap [00:15:32]
        while (K--) {
            auto top = pq.top();
            pq.pop();

            int sum = top.first;
            int i = top.second.first;
            int j = top.second.second;

            result.push_back(sum); // Add current largest sum to result [00:16:33]

            // Step 6: Explore neighbors (i+1, j) and (i, j+1) [00:16:41]
            
            // Try incrementing index in array A
            if (i + 1 < N && visited.find({i + 1, j}) == visited.end()) {
                pq.push({A[i + 1] + B[j], {i + 1, j}});
                visited.insert({i + 1, j});
            }

            // Try incrementing index in array B
            if (j + 1 < N && visited.find({i, j + 1}) == visited.end()) {
                pq.push({A[i] + B[j + 1], {i, j + 1}});
                visited.insert({i, j + 1});
            }
        }

        return result;
    }
};

/*

/***********************************************
🔹 STEPS FOR TOP K MAXIMUM SUM COMBINATIONS
***********************************************

1. Sort both arrays in descending order.
   - This ensures the largest elements are at the front.

2. Use a Max Heap (priority queue).
   - Store elements as:
     (sum, (i, j))

3. Use a Set to track visited index pairs.
   - Prevents pushing the same (i, j) combination multiple times.

4. Push the initial maximum combination.
   - Push (A[0] + B[0], (0,0)) into the heap.
   - Mark (0,0) as visited.

5. Repeat K times:

   • Pop the largest sum from the heap.
   • Add it to the result array.

   From that popped pair (i, j):

     - Push (i+1, j) if:
         • i+1 < N
         • Not already visited

     - Push (i, j+1) if:
         • j+1 < N
         • Not already visited

     - Mark newly added pairs as visited.

6. Return the result array.

------------------------------------------------
🔹 Core Idea:

• Treat sums as a sorted 2D matrix.
• Always expand from the current largest sum.
• Only explore right and down neighbors.
• Avoid duplicates using a visited set.

------------------------------------------------
🔹 Interview Summary:

We treat the sum combinations as a sorted matrix and use a max heap 
to extract the next largest possible sum while expanding only 
valid neighboring states.

************************************************/


-------------------------------------------------------------------------------------------
4. DRY RUN: [00:07:42]
-------------------------------------------------------------------------------------------
Input: A = [4, 3, 2, 1], B = [6, 5, 2, 1], K = 3
1. Initial: Heap = { (10, [0,0]) }, Visited = { [0,0] }
2. Pop (10, [0,0]): Result = [10]. 
   Push neighbors: (4+5=9, [0,1]) and (3+6=9, [1,0]).
3. Pop (9, [0,1]): Result = [10, 9]. 
   Push neighbor: (4+2=6, [0,2]) and (3+5=8, [1,1]).
4. Pop (9, [1,0]): Result = [10, 9, 9]. 
   K is now 0. Loop ends.
Output: [10, 9, 9]
===========================================================================================
*/


/***********************************************Criss-Cross indexing logic **************************************************** */

/*🧠 WHY only (i+1, j) and (i, j+1)?

From grid:

Start at (0,0)
Only next biggest candidates are:
⬇ down
➡ right


Because:

• Moving right decreases B slightly
• Moving down decreases A slightly

All other cells are smaller than these.

So we explore in a controlled greedy way instead of all n² sums.

📌 Role of visited

Prevents pushing same cell twice:

Example:

(1,1) can be reached from:

(1,0) → right
(0,1) → down

So we track it to avoid duplicates.

⚡ Complexity

Heap operations:

👉 O(k log k)

Much faster than:

❌ brute force O(n² log n)

🎯 One-line intuition (interview ready)

We treat sums as a sorted matrix and use a max heap to always expand the next largest neighboring sum.

*/