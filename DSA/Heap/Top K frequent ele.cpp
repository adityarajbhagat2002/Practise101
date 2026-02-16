https://leetcode.com/problems/top-k-frequent-elements/description/

/*
===========================================================================================
PROBLEM: Top K Frequent Elements (LeetCode 347)
===========================================================================================

-------------------------------------------------------------------------------------------
1. LOGIC AND INTUITION: [00:01:20]
-------------------------------------------------------------------------------------------
- We need to find elements with the highest frequencies.
- First, we use a Hash Map (unordered_map) to count the frequency of each number. [00:03:55]
- To find the "Top K", we use a Min-Heap (priority_queue with greater<int>). [00:06:30]
- Why Min-Heap? 
  - By keeping the heap size at K, the smallest frequency is always at the top.
  - When a new element comes, if its frequency is higher than the top, we pop the top 
    (the "least frequent" of our current top K) and push the new one. [00:06:51]

-------------------------------------------------------------------------------------------
2. TIME AND SPACE COMPLEXITY: [00:13:11]
-------------------------------------------------------------------------------------------
- Time Complexity: O(N log K)
    - Counting frequencies: O(N).
    - Heap operations: We iterate over 'M' unique elements (M <= N). Each push/pop in a 
      heap of size K takes O(log K). [00:13:27]
- Space Complexity: O(N + K)
    - O(N) for the frequency map.
    - O(K) for the priority queue. [00:13:41]

-------------------------------------------------------------------------------------------
3. CODE IMPLEMENTATION (C++):
-------------------------------------------------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // Step 1: Create a frequency map [00:03:55]
        // Key: Element, Value: Frequency
        unordered_map<int, int> mpp;
        for(auto &num : nums) {
            mpp[num]++; // Count how many times each number appears [00:10:07]
        }

        // Step 2: Initialize a Min-Heap [00:11:01]
        // We store pairs: {frequency, element_value}
        // Min-Heap ensures the element with the lowest frequency is at the top.
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        // Step 3: Iterate through the map and maintain only K elements in the heap [00:11:46]
        for(auto &it : mpp) {
            int element = it.first;
            int frequency = it.second;

            // Push the current {frequency, element} into the heap
            pq.push({frequency, element}); [00:12:05]

            // If heap size exceeds K, remove the element with the smallest frequency [00:12:12]
            if(pq.size() > k) {
                pq.pop(); // The 'least frequent' among the current K+1 is removed
            }
        }

        // Step 4: Extract the results from the heap [00:12:36]
        vector<int> ans;
        while(!pq.empty()) {
            // The heap now contains exactly the K most frequent elements.
            ans.push_back(pq.top().second); // We only need the element value [00:12:54]
            pq.pop();
        }

        return ans;
    }
};

/*
-------------------------------------------------------------------------------------------
4. DRY RUN: [00:07:22]
-------------------------------------------------------------------------------------------
Input: nums = [1,1,1,2,2,3], k = 2
1. Map: {1: 3, 2: 2, 3: 1}
2. Iterating Map:
   - Push {3, 1}: PQ = [{3, 1}]
   - Push {2, 2}: PQ = [{2, 2}, {3, 1}] (Size 2, OK)
   - Push {1, 3}: PQ = [{1, 3}, {2, 2}, {3, 1}] (Size 3, Pop Top!)
   - After Pop: PQ = [{2, 2}, {3, 1}]
3. Final Heap elements: 2 and 1.
Output: [2, 1] (or [1, 2])
===========================================================================================
*/