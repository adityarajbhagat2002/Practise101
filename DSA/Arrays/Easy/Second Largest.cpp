https://www.geeksforgeeks.org/problems/second-largest3735/1

// Problem: Find the second largest element in the array
// Return -1 if it doesn't exist (i.e., all elements are equal or only one unique value)

class Solution {
  public:
    int getSecondLargest(vector<int> &arr) {
        int largest = INT_MIN;      // Will hold the largest element
        int sLargest = INT_MIN;     // Will hold the second largest element
        int n = arr.size();

        for (int i = 0; i < n; i++) {
            if (arr[i] > largest) {
                sLargest = largest;   // update second largest
                largest = arr[i];     // update largest
            } else if (arr[i] > sLargest && arr[i] != largest) {
                sLargest = arr[i];    // update only second largest
            }
        }

        return (sLargest == INT_MIN) ? -1 : sLargest;
    }
};

/*
Why This Works:
----------------
- We keep track of two values: `largest` and `second largest`
- When a number is greater than the current largest, we:
  → Move `largest` to `sLargest`
  → Update `largest` with the new number
- When a number is less than `largest` but greater than `sLargest`, it’s a new second largest
- This logic ensures we skip duplicates of the largest number

When To Use:
-------------
- You need to find the **second maximum distinct** element efficiently
- Array is unsorted and contains duplicates
- You need a solution in **one pass** (O(n) time)

Time Complexity: O(n)      // Single pass through the array
Space Complexity: O(1)     // Constant extra space used
*/