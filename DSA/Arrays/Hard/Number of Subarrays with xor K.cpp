// Number of Subarrays with XOR == K (TakeUForward)
// ==================================================

// Problem Statement:
// Given an array and integer K, count the number of contiguous subarrays whose XOR equals K.

// ---------------------------------------------------------------------
// 1. Brute Force Approach
// ---------------------------------------------------------------------
// - Generate all subarrays using two nested loops.
// - For each subarray, compute XOR and compare with K.
// - Time: O(n^3) (for every i, all j, and recompute XOR for each subarray)
// - Space: O(1) (only a few vars for XOR and count)

#include <vector>
using namespace std;

int subarrayXorBrute(vector<int> &nums, int k)
{
    int n = nums.size();
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            int xr = 0;
            for (int l = i; l <= j; l++)
            {
                xr ^= nums[l];
            }
            if (xr == k)
                cnt++;
        }
    }
    return cnt;
}

// ---------------------------------------------------------------------
// 2. Better Approach
// ---------------------------------------------------------------------
// - Use two nested loops but keep a running XOR (xr) so you don't redo work.
// - Time: O(n^2) (inner loop recomputes only once per added element)
// - Space: O(1)

int subarrayXorBetter(vector<int> &nums, int k)
{
    int n = nums.size();
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        int xr = 0;
        for (int j = i; j < n; j++)
        {
            xr ^= nums[j];
            if (xr == k)
                cnt++;
        }
    }
    return cnt;
}

// ---------------------------------------------------------------------
// 3. Optimal Approach (Prefix XOR + Hash Map)
// ---------------------------------------------------------------------
// - Idea: If prefix XOR up to r is XR, and prefix XOR up to l-1 is prev, then
//     XR ^ prev == k  <==>  prev == XR ^ k
//   So, for every running XR, if (XR^k) has occurred as prefix before, there
//   exists a subarray ending here with XOR == k.
// - Use a map to count prefix XORs seen so far.
// - Time: O(n)
// - Space: O(n), for the hash map

class Solution {
  public:
    long subarrayXor(vector<int> &arr, int k) {
        int xr = 0;                   // Prefix XOR
        map<int, int> freq;           // Map to store frequencies of prefix XORs
        int n = arr.size();
        freq[xr] = 1;                 // Initialize freq with 0 XOR count as 1
        long count = 0;               // Result: number of subarrays with XOR = k
        
        for (int i = 0; i < n; i++) {
            xr = xr ^ arr[i];         // Update prefix XOR
            
            int x = xr ^ k;           // The required prefix XOR to satisfy condition
            
            // If x is present as a prefix XOR, add its frequency to count
            count += freq[x];
            
            // Increase frequency of current prefix XOR xr
            freq[xr]++;
        }
        
        return count;
    }
};
 // simple fomula is this   int x= xr^k;   xor of all the elements  and againg xor with K will give X which is the required for the sum do the dry run
// look into the notes a bit discriptive

// 🔹 Summary
// freq[0] = 1 → represents the empty prefix XOR before the array starts.

// It ensures that subarrays starting at the first element are correctly counted if their XOR equals k.

// This is a standard trick when using prefix XOR + hashmap for subarray XOR problems.
//
 /* Example test:
    nums = {4, 2, 2, 6, 4}, k = 6
    Expected output: 4

Edge Cases:
- Empty array returns 0.
- K = 0, must correctly count all subarrays with XOR 0.
- All elements same as K, each single-element subarray must be counted.
- Array with negative numbers (if allowed).

Key Intuitions
Brute force: Try every subarray — too slow for big inputs.

Better: Maintain running XOR as you expand subarrays to avoid redoing computations.

Optimal: Use prefix XOR and a frequency map to query how many ways you can "cancel out" earlier prefixes to get the desired result via the XOR property. This is fast, elegant, most asked in interviews, and requires careful hash map handling.

Edge Case Tips
Use freq=1 to allow subarrays that start from index 0.

Returns 0 on empty input.

Works for negatives since XOR is defined for all ints.

*/

// ---------------------------------------------------------------------
// Summary Table of Approaches
// ---------------------------------------------------------------------
// | Approach      | Time Complexity | Space Complexity |
// |---------------|----------------|------------------|
// | Brute Force   | O(n^3)         | O(1)             |
// | Better (prefix running) | O(n^2) | O(1)             |
// | Optimal (hash map) | O(n)           | O(n)             |
