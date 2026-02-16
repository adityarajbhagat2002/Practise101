https://leetcode.com/problems/kth-largest-element-in-an-array/
/*
===========================================================================================
PROBLEM: Kth Largest Element in an Array (LeetCode 215)
===========================================================================================

-------------------------------------------------------------------------------------------
1. LOGIC AND INTUITION: [00:02:08]
-------------------------------------------------------------------------------------------
- To find the Kth largest element, we can use a Min-Heap of size K.
- GREEDY STRATEGY: 
  - If we maintain a Min-Heap of size K, the smallest element among those K elements 
    will always be at the top. [00:02:54]
  - By the time we process the entire array, the Min-Heap will contain the K largest 
    elements of the array.
  - The top of this Min-Heap will be the smallest of these K largest elements, 
    which is exactly the Kth largest element! [00:04:48]

-------------------------------------------------------------------------------------------
2. WHY MIN-HEAP? [00:05:07]
-------------------------------------------------------------------------------------------
- A Max-Heap would put the largest at the top, but we want to discard "smaller" elements 
  to keep only the "K largest". 
- In a Min-Heap, the smallest element is "sacrificed" (popped) whenever the size exceeds K.

-------------------------------------------------------------------------------------------
3. TIME AND SPACE COMPLEXITY: [00:05:44]
-------------------------------------------------------------------------------------------
- Time Complexity: O(N * log K)
    - N is the number of elements in the array.
    - log K is the cost of push/pop operations in a heap of size K. [00:06:13]
- Space Complexity: O(K) 
    - We only store K elements in the priority queue at any given time. [00:06:08]

-------------------------------------------------------------------------------------------
4. CODE IMPLEMENTATION (C++):
-------------------------------------------------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <queue> // Required for priority_queue

using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        // Step 1: Initialize a Min-Heap [00:02:14]
        // priority_queue in C++ is a Max-Heap by default. 
        // We use greater<int> to transform it into a Min-Heap.
        priority_queue<int, vector<int>, greater<int>> pq;

        // Step 2: Iterate through all numbers in the input array [00:05:50]
        for(int &num : nums) {
            // Push current number into the heap [00:02:45]
            pq.push(num);

            // Step 3: Maintain the heap size at K [00:03:04]
            // If size exceeds K, pop the smallest element (the top) [00:03:14]
            if(pq.size() > k) {
                pq.pop(); // Smallest element among current elements is removed [00:03:19]
            }
        }

        // After the loop, the heap contains the K largest elements.
        // The top is the smallest among those K, which is the Kth largest. [00:04:36]
        return pq.top();
    }
};

/*
-------------------------------------------------------------------------------------------
5. DRY RUN EXAMPLE: [00:02:35]
-------------------------------------------------------------------------------------------
Input: nums = [3, 2, 1, 5, 6, 4], k = 2

1. Push 3: Heap = {3}
2. Push 2: Heap = {2, 3} (Min-Heap: 2 is top)
3. Push 1: Heap = {1, 2, 3}. Size > 2, Pop(1). Heap = {2, 3}
4. Push 5: Heap = {2, 3, 5}. Size > 2, Pop(2). Heap = {3, 5}
5. Push 6: Heap = {3, 5, 6}. Size > 2, Pop(3). Heap = {5, 6}
6. Push 4: Heap = {4, 5, 6}. Size > 2, Pop(4). Heap = {5, 6}

Final Top: 5 (The 2nd largest element!) [00:04:48]
===========================================================================================
*/