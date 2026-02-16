https://www.geeksforgeeks.org/problems/merge-k-sorted-arrays/1


/*
===========================================================================================
PROBLEM: MERGE K SORTED ARRAYS
===========================================================================================

-------------------------------------------------------------------------------------------
1. CORE LOGIC: [00:03:53]
-------------------------------------------------------------------------------------------
- At any point, the next smallest element in our final merged array must be one of the 
  "first available" elements from the K arrays.
- Instead of sorting everything (Brute Force), we maintain a Min-Heap of size K. [00:05:53]
- Each element in the heap will be a triplet: {value, array_index, element_index}. [00:12:46]
- Whenever we pop the smallest element from the heap:
    1. Add it to our result. [00:16:54]
    2. Replace it with the NEXT element from the SAME array it came from. [00:17:07]

-------------------------------------------------------------------------------------------
2. TIME & SPACE COMPLEXITY: [00:17:58]
-------------------------------------------------------------------------------------------
- Time Complexity: O(N log K)
    - N = Total number of elements across all arrays. [00:18:18]
    - log K = Cost of heap operations (size of heap is at most K). [00:18:44]
- Space Complexity: O(K)
    - The Min-Heap stores at most one element from each of the K arrays. [00:19:15]

-------------------------------------------------------------------------------------------
3. CODE IMPLEMENTATION (C++):
-------------------------------------------------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// We use a custom structure or pair nesting to store the data in the heap.
// Data: {value, {array_index, element_index}} [00:13:55]
typedef pair<int, pair<int, int>> node;

class Solution {
public:
    vector<int> mergeKArrays(vector<vector<int>> arr, int K) {
        // Step 1: Initialize Min-Heap [00:11:18]
        // Syntax for Min-Heap in C++ requires a container and a comparator. [00:11:24]
        priority_queue<node, vector<node>, greater<node>> minHeap;

        // Step 2: Push the first element of every array into the heap [00:14:32]
        for (int i = 0; i < K; i++) {
            // Check if array is not empty [00:15:23]
            if (!arr[i].empty()) {
                // {Value, {Array Number, Index in that array}}
                minHeap.push({arr[i][0], {i, 0}}); [00:15:33]
            }
        }

        vector<int> result;

        // Step 3: Process the heap until empty [00:15:56]
        while (!minHeap.empty()) {
            node current = minHeap.top();
            minHeap.pop(); // Remove the smallest global element [00:16:46]

            int val = current.first;          // The actual number [00:16:05]
            int arrayIdx = current.second.first; // Which array it came from [00:16:18]
            int elementIdx = current.second.second; // Its index in that array [00:16:35]

            result.push_back(val); // Add to merged result [00:16:54]

            // Step 4: If the array has more elements, push the next one [00:17:07]
            if (elementIdx + 1 < arr[arrayIdx].size()) {
                minHeap.push({
                    arr[arrayIdx][elementIdx + 1], // The next value
                    {arrayIdx, elementIdx + 1}      // Updated indices [00:17:35]
                });
            }
        }

        return result; // Final merged and sorted vector [00:17:45]
    }
};

/*
-------------------------------------------------------------------------------------------
4. DRY RUN: [00:07:05]
-------------------------------------------------------------------------------------------
Arrays: [[1, 5], [2, 4], [0, 9]]
1. Heap: {0, 1, 2} (first elements)
2. Pop 0 (from array 2). Push 9 (next in array 2). 
   Heap: {1, 2, 9}
3. Pop 1 (from array 0). Push 5 (next in array 0). 
   Heap: {2, 5, 9}
4. Pop 2 (from array 1). Push 4 (next in array 1). 
   Heap: {4, 5, 9}
... and so on until result is [0, 1, 2, 4, 5, 9]. [00:09:26]
===========================================================================================
*/


/*******************************************************
🔹 PRIORITY QUEUE TEMPLATE FORMAT (C++ STL NOTES)
*******************************************************

1️⃣ Actual Template Definition:

template<
    class T,
    class Container = vector<T>,
    class Compare = less<T>
>
class priority_queue;

It takes THREE template parameters:

    1. T         → Type of element
    2. Container → Underlying container (default = vector<T>)
    3. Compare   → Comparator (default = less<T>)

-------------------------------------------------------

2️⃣ Default Behavior

priority_queue<int> pq;

Actually means:

priority_queue<int, vector<int>, less<int>>

• Uses vector internally.
• Uses less<T>.
• This creates a MAX HEAP.
• Largest element is at the top.

-------------------------------------------------------

3️⃣ Creating a MIN HEAP

To create a min heap, we must explicitly specify BOTH:
• The container
• The comparator

Correct syntax:

priority_queue<int, vector<int>, greater<int>> minHeap;

Why?

Because template parameters must be filled in order:
<Type, Container, Comparator>

We cannot skip the container.

-------------------------------------------------------

4️⃣ Why This Is WRONG

priority_queue<int, greater<int>> pq;   ❌ INVALID

C++ interprets this as:

T = int
Container = greater<int>   ❌ (Wrong — this is not a container)

So it fails.

-------------------------------------------------------

5️⃣ Using With Custom Type (Example: node)

typedef pair<int, pair<int,int>> node;

Min Heap of node:

priority_queue<node, vector<node>, greater<node>> minHeap;

-------------------------------------------------------

6️⃣ Why vector Is Used?

A heap requires:
• Random access
• Dynamic resizing

vector provides both.

That’s why STL uses vector as default container.

-------------------------------------------------------

7️⃣ Quick Comparison Table

priority_queue<int>
→ Max Heap (default)

priority_queue<int, vector<int>, greater<int>>
→ Min Heap

-------------------------------------------------------

🔹 Final Rule To Remember

If you change the comparator,
you MUST also explicitly specify the container.

Default:
priority_queue<T>
= priority_queue<T, vector<T>, less<T>>

Min Heap:
priority_queue<T, vector<T>, greater<T>>

*******************************************************/
