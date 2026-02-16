https://leetcode.com/problems/merge-intervals/description/
/*
Merge Overlapping Intervals - Complete Guide

Problem:
Given a collection of intervals, merge all overlapping intervals and return the resulting 
list of disjoint intervals that cover all intervals in the input.

Example:
Input: [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]

----------------------------------------------------------
Intuition:
- Overlapping intervals can be merged into a single interval covering all their ranges.
- Sorting intervals by start time helps ordering intervals to process overlaps linearly.

----------------------------------------------------------
1. Brute Force Approach:

- Compare every interval with every other interval to check for overlaps.
- If overlapping, merge them by updating the start to min and end to max of both intervals.
- Continue merging until no further overlaps exist.

Time Complexity:
- Potentially O(N^3) due to multiple passes over intervals to merge all overlapping ones.

Space Complexity:
- O(N) for output storage.

*/
Code:

#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> mergeIntervalsBrute(vector<vector<int>>& intervals) {
    if(intervals.empty()) return {};

    int n = intervals.size();
    bool mergedAtLeastOnce;

    do {
        mergedAtLeastOnce = false;

        vector<bool> merged(n, false);
        vector<vector<int>> temp;

        for(int i = 0; i < n; ++i) {
            if(merged[i]) continue;
            int start = intervals[i][0];
            int end = intervals[i][1];
            merged[i] = true;

            for(int j = i + 1; j < n; ++j) {
                if(merged[j]) continue;
                // Check if intervals[i] overlaps with intervals[j]
                if(intervals[j][0] <= end && intervals[j][1] >= start) {
                    // Merge
                    start = min(start, intervals[j][0]);
                    end = max(end, intervals[j][1]);
                    merged[j] = true;
                    mergedAtLeastOnce = true;
                }
            }
            temp.push_back({start, end});
        }
        intervals = temp;
        n = intervals.size();

    } while(mergedAtLeastOnce);

    return intervals;
}
/*

----------------------------------------------------------
2. Optimal Approach:

- Sort intervals based on start.
- Iterate, and merge overlapping intervals by extending end of last merged interval.

Time Complexity:
- O(N log N) due to sorting, O(N) to merge.

Space Complexity:
- O(N) for output.

*/

Code:

#include <vector>
#include <algorithm>
using namespace std;

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {

        int n = intervals.size();            // Get number of intervals
        vector<vector<int>> ans;             // This will store merged intervals

        // If there are no intervals, return empty result
        if(n == 0) return ans;

        // Sort intervals based on starting value (and end if tie)
        sort(intervals.begin(), intervals.end());

        // Loop through each interval one by one
        for (int i = 0; i < n; i++) {

            // If ans is empty OR current interval does NOT overlap with last merged one
            if (ans.empty() || ans.back()[1] < intervals[i][0]) {

                // No overlap → push current interval as new
                ans.push_back(intervals[i]);
            } 
            else {
                // Overlap exists → merge by extending end point
                ans.back()[1] = max(ans.back()[1], intervals[i][1]);
            }
        }

        // Return merged list
        return ans;
    }
};

/*
----------------------------------------------------------
Edge Cases:
- Empty list: return empty.
- Intervals with same start or end.
- Intervals contained within others.
- No overlaps at all.
- Large inputs.

----------------------------------------------------------
Summary:
- Brute force merges in multiple passes, expensive but intuitive.
- Optimal sorts then merges in one pass, efficient and preferred.
*/
