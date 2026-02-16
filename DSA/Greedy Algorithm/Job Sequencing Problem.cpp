https://www.geeksforgeeks.org/problems/job-sequencing-problem-1587115620/1

/*
===========================================================================================
PROBLEM: JOB SEQUENCING PROBLEM (GeeksforGeeks)
===========================================================================================

-------------------------------------------------------------------------------------------
1. LOGIC AND INTUITION: [00:04:44]
-------------------------------------------------------------------------------------------
- The Goal: Maximize profit by picking the best jobs within their deadlines.
- Greedy Strategy: 
    1. Sort jobs by PROFIT in descending order. We want the "money-makers" first.
    2. For each job, schedule it on its LAST POSSIBLE DAY (its deadline). [00:06:02]
- Why do we schedule late? 
  If a job has a deadline of 5, and we do it on Day 1, we might block a job that 
  ONLY had a deadline of Day 1. By doing it on Day 5, we leave Day 1-4 free. [00:12:05]

-------------------------------------------------------------------------------------------
2. SPACE AND TIME COMPLEXITY: [00:12:16]
-------------------------------------------------------------------------------------------
- Time: O(N log N) for sorting + O(N * maxDeadline) for the nested loops.
- Space: O(maxDeadline) to store the schedule slots.

-------------------------------------------------------------------------------------------
3. CODE IMPLEMENTATION (C++):
-------------------------------------------------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
  public:
    // Custom structure to hold Job details if needed, 
    // but here we use the vectors provided in the signature.
    
    // Helper function to sort based on profit in descending order [00:15:24]
    static bool comparison(const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second; 
    }

    vector<int> jobSequencing(vector<int> &deadline, vector<int> &profit) {
        int n = deadline.size();
        
        // 1. Create a vector of pairs {deadline, profit} to keep them linked [00:15:14]
        vector<pair<int, int>> jobs;
        int max_dead = 0;
        for (int i = 0; i < n; i++) {
            jobs.push_back({deadline[i], profit[i]});
            // Track the maximum deadline to size our "time slots" array [00:15:32]
            max_dead = max(max_dead, deadline[i]);
        }

        // 2. Sort jobs based on profit in DESCENDING order [00:05:15]
        sort(jobs.begin(), jobs.end(), comparison);

        // 3. Initialize a 'slot' array to keep track of occupied days [00:15:37]
        // -1 indicates the day is free. Size is max_dead + 1 for 1-based indexing.
        vector<int> slot(max_dead + 1, -1);

        int countJobs = 0;    // To store total number of jobs done
        int totalProfit = 0;  // To store total profit earned

        // 4. Iterate through all sorted jobs (starting with highest profit) [00:16:01]
        for (int i = 0; i < n; i++) {
            // 5. Try to find a free slot for this job, starting from its DEADLINE [00:16:08]
            // We move backwards from deadline -> Day 1 to save early slots for other jobs.
            for (int j = jobs[i].first; j > 0; j--) {
                // If the slot on day 'j' is free (-1)
                if (slot[j] == -1) {
                    slot[j] = i;            // Occupy the slot with the current job index
                    countJobs++;            // Increment count of jobs completed
                    totalProfit += jobs[i].second; // Add this job's profit to total
                    break;                  // Job scheduled! Move to the next job in the list [00:16:25]
                }
            }
        }

        // 6. Return the required format: {number of jobs, maximum profit}
        return {countJobs, totalProfit};
    }
};

/*
-------------------------------------------------------------------------------------------
4. KEY TAKEAWAYS FROM VIDEO:
-------------------------------------------------------------------------------------------
- Always sort by profit first, not by deadline. [00:04:45]
- The "Slot" array is like a calendar. Once a day is filled, it's gone.
- The time complexity is dominated by the nested loop if deadlines are large. [00:12:44]
===========================================================================================
*/


//Optimized code but read if time (DISJOINT SET)

class Solution {
public:

    static bool comp(const pair<int,int> &a, const pair<int,int> &b){
        return a.second > b.second;   // sort by profit descending
    }

    int find(int x, vector<int>& parent){
        if(parent[x] == x)
            return x;
        return parent[x] = find(parent[x], parent);
    }

    void unite(int u, int v, vector<int>& parent){
        parent[v] = u;
    }

    vector<int> jobSequencing(vector<int> &deadline, vector<int> &profit) {

        int n = deadline.size();

        vector<pair<int,int>> jobs;

        for(int i=0;i<n;i++){
            jobs.push_back({deadline[i], profit[i]});
        }

        sort(jobs.begin(), jobs.end(), comp);

        int maxdeadline = 0;
        for(int i=0;i<n;i++){
            maxdeadline = max(maxdeadline, deadline[i]);
        }

        // DSU parent array
        vector<int> parent(maxdeadline + 1);

        for(int i=0;i<=maxdeadline;i++)
            parent[i] = i;

        int countjobs = 0;
        int totalprofit = 0;

        for(int i=0;i<n;i++){

            int availableSlot = find(jobs[i].first, parent);

            if(availableSlot > 0){
                countjobs++;
                totalprofit += jobs[i].second;

                // mark this slot filled, move to previous slot
                unite(find(availableSlot - 1, parent), availableSlot, parent);
            }
        }

        return {countjobs, totalprofit};
    }
};
