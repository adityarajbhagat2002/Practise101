https://www.geeksforgeeks.org/problems/minimum-platforms-1587115620/1

/*
===========================================================================================
PROBLEM: MINIMUM PLATFORMS (GeeksforGeeks)
===========================================================================================

-------------------------------------------------------------------------------------------
1. LOGIC AND INTUITION: [00:06:29]
-------------------------------------------------------------------------------------------
- We are given arrival and departure times of all trains. 
- The goal is to find the maximum number of trains present at the station at any given time.
- TRICK: We don't need to know which train is leaving. We just need to know IF a train 
  has left before the next one arrives. [00:07:48]
- By sorting both arrival and departure arrays independently, we can simply track the 
  timeline of events (arrivals and departures). [00:06:58]

-------------------------------------------------------------------------------------------
2. WHY SORTING BOTH WORKS: [00:10:55]
-------------------------------------------------------------------------------------------
Sorting the departure array doesn't break the logic because we only care if *any* platform becomes 
free before the next train arrives. We don't care *which* train 
vacated it. This allows us to use two pointers to simulate the flow of time. [00:11:07]

-------------------------------------------------------------------------------------------
3. SPACE AND TIME COMPLEXITY: [00:13:54]
-------------------------------------------------------------------------------------------
- Time Complexity: O(N log N) for sorting both arrays. The while loop is O(2N).
- Space Complexity: O(1) as we sort the input arrays in place (or O(log N) depending 
  on the sorting algorithm's stack space). [00:14:14]

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
    int findPlatform(vector<int>& arr, vector<int>& dep) {
        int n = arr.size();

        // Step 1: Sort both arrays independently [00:06:58]
        // This helps us track the sequence of arrivals and departures over time.
        sort(arr.begin(), arr.end());
        sort(dep.begin(), dep.end());

        // Step 2: Initialize pointers and counters [00:14:43]
        // i points to arrivals, j points to departures.
        // We start i from 1 because the first train (at arr[0]) always needs a platform.
        int platformNeeded = 1; 
        int maxPlatforms = 1;
        int i = 1, j = 0;

        // Step 3: Process all arrival and departure events [00:15:09]
        while (i < n && j < n) {
            // If a train is arriving before or at the same time the oldest train leaves
            // Note: The problem states if arrival == departure, we need two platforms. [00:01:11]
            if (arr[i] <= dep[j]) {
                platformNeeded++; // One more platform is occupied
                i++;              // Move to the next arriving train
            } 
            // If a train leaves before the next one arrives
            else {
                platformNeeded--; // One platform becomes free [00:07:59]
                j++;              // Move to the next departing train
            }

            // Keep track of the maximum platforms needed at any point [00:15:58]
            if (platformNeeded > maxPlatforms) {
                maxPlatforms = platformNeeded;
            }
        }

        return maxPlatforms;
    }
};

/*
-------------------------------------------------------------------------------------------
5. DRY RUN EXAMPLE: [00:08:30]
-------------------------------------------------------------------------------------------
Input: arr[] = {900, 940, 950, 1100, 1500, 1800}, dep[] = {910, 1200, 1120, 1130, 1900, 2000}
Sorted Arrival:   900, 940, 950, 1100, 1500, 1800
Sorted Departure: 910, 1120, 1130, 1200, 1900, 2000

1. 900 arrives: Plat=1, Max=1
2. 910 departs: Plat=0, Max=1
3. 940 arrives: Plat=1, Max=1
4. 950 arrives: Plat=2, Max=2
5. 1100 arrives: Plat=3, Max=3
6. 1120 departs: Plat=2, Max=3
... and so on.
===========================================================================================
*/