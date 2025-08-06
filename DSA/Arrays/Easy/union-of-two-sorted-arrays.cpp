https://www.geeksforgeeks.org/problems/union-of-two-sorted-arrays-1587115621/1

// Union of Two Sorted Arrays
// ✅ Finds union of two sorted arrays with duplicates, returns distinct elements in sorted order

class Solution {
  public:
    // a,b : the arrays
    // Function to return a list containing the union of the two arrays.
    vector<int> findUnion(vector<int> &a, vector<int> &b) {
        int i = 0, j = 0;
        int n = a.size(), m = b.size();
        vector<int> result;

        // Compare elements from both arrays using two pointers
        while (i < n && j < m) {
            int val;
            if (a[i] < b[j]) val = a[i++];          // Take smaller element from array a
            else if (a[i] > b[j]) val = b[j++];     // Take smaller element from array b
            else val = a[i], i++, j++;              // Both equal, take one and advance both

            // Add to result only if it's different from last added element
            if (result.empty() || result.back() != val)
                result.push_back(val);
        }

        // Add remaining elements from array a (if any)
        while (i < n) {
            if (result.empty() || result.back() != a[i])
                result.push_back(a[i]);
            i++;
        }

        // Add remaining elements from array b (if any)
        while (j < m) {
            if (result.empty() || result.back() != b[j])
                result.push_back(b[j]);
            j++;
        }

        return result;
    }
};

/*
Why This Works:
----------------
- Uses **two-pointer technique** to merge two sorted arrays efficiently
- At each step, picks the smaller element to maintain sorted order
- Avoids duplicates by checking if current element differs from last added
- Since both arrays are sorted, result will automatically be in sorted order
- Handles edge cases where one array is exhausted before the other


When To Use:
-------------
- When you need **union of two sorted arrays** with duplicate handling
- Merging two sorted datasets while maintaining order and uniqueness
- Alternative to using sets when you want to preserve the merge process
- Good for problems requiring sorted union without extra space for hashing


Time Complexity: O(n + m)     // Single pass through both arrays
Space Complexity: O(n + m)    // For result array (O(1) if not counting output)
*/
