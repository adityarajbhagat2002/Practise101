/*
===========================================================================================
QUICK SORT - THE PARTITION STORY
===========================================================================================
Source: CodeStoryWithMIK (YouTube)
Concept: Divide and Conquer / Recursion
Complexity: Time O(n log n) [Avg], O(n^2) [Worst] | Space O(n) [Stack Space]

-------------------------------------------------------------------------------------------
PROBLEM DESCRIPTION:
- Quick Sort is a sorting algorithm that picks an element as 'pivot' and partitions 
  the array around the picked pivot.
- Steps:
    1. Pick a Pivot (e.g., the last element). [00:02:30]
    2. Partitioning: Rearrange the array so that elements smaller than pivot are 
       on the left, and larger elements are on the right. [00:03:05]
    3. Recursive Step: Apply the same logic to the left and right subarrays. [00:01:57]

-------------------------------------------------------------------------------------------
THE RECURSIVE STORY (Story to Code):
1. Base Case: If the range has one or zero elements (low >= high), it's already sorted. [00:43:08]
2. Pivot Position: Find the correct sorted position of the pivot using the partition function.
3. Conquer: 
   - Recursively sort the elements to the left of pivot: quickSort(low, pi - 1). [00:43:40]
   - Recursively sort the elements to the right of pivot: quickSort(pi + 1, high). [00:43:45]

-------------------------------------------------------------------------------------------
PARTITION LOGIC (Lomuto Partition): [00:45:15]
- We pick the last element as the pivot.
- 'pi' (partition index) tracks where the next smaller-than-pivot element should go.
- We iterate through the array: if current element <= pivot, we swap it with the element 
  at 'pi' and move 'pi' forward.
- Finally, swap the pivot into its correct spot (at 'pi').
===========================================================================================
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    // The main function that implements QuickSort
    void quickSort(vector<int>& arr, int low, int high) {
        // Base Case: If low is not less than high, range is sorted [00:43:08]
        if (low >= high) {
            return;
        }

        // Partition the array and get the pivot index [00:43:30]
        int pi = partition(arr, low, high);

        // Recursively sort elements before and after partition index
        quickSort(arr, low, pi - 1);  // Left side [00:43:40]
        quickSort(arr, pi + 1, high); // Right side [00:43:45]
    }

    // Function to place pivot at correct position and partition the array [00:45:15]
    int partition(vector<int>& arr, int low, int high) {
        // We pick the last element as the pivot [00:45:50]
        int pivotele = arr[high];
        
        // Index of the smaller element (where the pivot will eventually sit)
        int pi = low;

        // Compare each element with pivot [00:46:07]
        for (int i = low; i < high; i++) {
            // If current element is smaller than or equal to pivot [00:46:19]
            if (arr[i] <= pivotele) {
                // Swap it with the element at the current partition index
                swap(arr[i], arr[pi]);
                pi++; // Increment the partition index
            }
        }

        // Finally, swap the pivot element with the element at pi [00:46:55]
        // This puts the pivot in its correct sorted position
        swap(arr[pi], arr[high]);

        return pi; // Return the index of the pivot [00:47:13]
    }
};

/*
-------------------------------------------------------------------------------------------
COMPLEXITY ANALYSIS:
- Time Complexity:
    - Average/Best Case: O(n log n) - Occurs when the pivot divides the array into two equal halves.
    - Worst Case: O(n^2) - Occurs when the pivot is always the smallest or largest (e.g., sorted array).
- Space Complexity:
    - O(n) worst-case auxiliary space for the recursion stack.
-------------------------------------------------------------------------------------------
*/