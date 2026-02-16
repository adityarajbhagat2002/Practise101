https://www.geeksforgeeks.org/problems/n-meetings-in-one-room-1587115620/1

/*
===========================================================================================
PROBLEM: N MEETINGS IN ONE ROOM (GeeksforGeeks)
===========================================================================================

-------------------------------------------------------------------------------------------
1. LOGIC AND INTUITION: [00:03:19]
-------------------------------------------------------------------------------------------
The core idea is GREEDY. To fit the maximum number of meetings in one room:
- We should pick meetings that finish as early as possible. 
- Why? Because an early-finishing meeting leaves the maximum time available for 
  other meetings to occur afterward. [00:09:00]

-------------------------------------------------------------------------------------------
2. STEPS OF THE ALGORITHM: [00:04:03]
-------------------------------------------------------------------------------------------
1. Create a custom structure/class to store 'start time', 'end time', and 'original position'.
2. Sort all meetings based on their END TIME in ascending order. [00:15:04]
3. If two meetings have the same end time, sort them by their original position (1-based index). [00:15:52]
4. The first meeting in the sorted list will always be performed.
5. For subsequent meetings, if the current meeting's START TIME is GREATER than the 
   END TIME of the last performed meeting, perform it and update the limit. [00:16:53]

-------------------------------------------------------------------------------------------
3. SPACE AND TIME COMPLEXITY: [00:09:09]
-------------------------------------------------------------------------------------------
- Time Complexity: O(N log N) 
    - O(N) to store meetings in the structure.
    - O(N log N) to sort the meetings. [00:09:24]
    - O(N) to iterate and count valid meetings.
- Space Complexity: O(N) to store the meeting data in a vector/array. [00:10:05]

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
    // Structure to bundle meeting details together [00:14:34]
    struct meeting {
        int start; // Starting time of the meeting
        int end;   // Finishing time of the meeting
        int pos;   // Original 1-based index of the meeting
    };

    // Comparator function to sort meetings by ending time [00:15:32]
    static bool comp(meeting m1, meeting m2) {
        // If finishing times are different, pick the one that ends earlier
        if (m1.end < m2.end) return true;
        else if (m1.end > m2.end) return false;
        // If finishing times are same, pick the one with the smaller original index [00:05:37]
        else if (m1.pos < m2.pos) return true;
        return false;
    }

    int maxMeetings(vector<int>& start, vector<int>& end) {
        int n = start.size(); // Total number of meetings
        
        // Step 1: Create a list of meeting objects [00:14:41]
        vector<meeting> m(n);
        for (int i = 0; i < n; i++) {
            m[i].start = start[i];      // Assign start time
            m[i].end = end[i];          // Assign end time
            m[i].pos = i + 1;           // Store 1-based index [00:03:05]
        }

        // Step 2: Sort meetings using the custom comparator [00:15:04]
        sort(m.begin(), m.end(), comp);

        int count = 1;              // The first sorted meeting is always selected [00:16:19]
        int limit = m[0].end;       // End time of the current ongoing meeting [00:16:39]

        // Step 3: Iterate through the rest of the meetings [00:16:45]
        for (int i = 1; i < n; i++) {
            // If the next meeting starts STRICTLY AFTER the current one ends [00:01:00]
            if (m[i].start > limit) {
                count++;            // Increment meeting count
                limit = m[i].end;   // Update the limit to the current meeting's end time [00:17:13]
            }
        }

        return count; // Total maximum meetings possible
    }
};

/*
-------------------------------------------------------------------------------------------
5. KEY TAKEAWAYS:
-------------------------------------------------------------------------------------------
- The "Limit" represents when the room becomes free. [00:06:13]
- A meeting can only start if its start time > limit (not equal, as per problem constraints). [00:00:30]
- This is a standard Interval Scheduling problem solvable via Greedy approach.
===========================================================================================
*/