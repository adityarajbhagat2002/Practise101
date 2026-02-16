/*
===========================================================================================
TOPIC: HEAP DATA STRUCTURE (MAX-HEAP)
===========================================================================================

-------------------------------------------------------------------------------------------
1. THEORETICAL NOTES FROM THE VIDEO
-------------------------------------------------------------------------------------------
* DEFINITION: [00:00:30]
  - A Heap is a "Complete Binary Tree" (CBT) that satisfies the Heap Property.
  - Complete Binary Tree: Every level is filled except possibly the last, which is filled 
    from left to right. [00:01:01]

* HEAP TYPES: [00:01:56]
  - Max-Heap: Parent node value >= Children node values. Root is the maximum.
  - Min-Heap: Parent node value <= Children node values. Root is the minimum.

* WHY HEAPS? [00:03:19]
  - They allow us to find the Max/Min element in O(1) time.
  - Insertion and Deletion are efficient at O(log N). [00:03:41]

* ARRAY REPRESENTATION (1-Based Indexing): [00:04:17]
  For any node at index 'i':
  - Parent Index      = i / 2
  - Left Child Index  = 2 * i
  - Right Child Index = 2 * i + 1

-------------------------------------------------------------------------------------------
2. CODE IMPLEMENTATION
-------------------------------------------------------------------------------------------
*/

#include <iostream>
#include <vector>

using namespace std;

class MaxHeap {
public:
    int arr[100]; // Array to store heap elements
    int size;     // Current number of elements in heap

    MaxHeap() {
        arr[0] = -1; // Index 0 is ignored for easier 1-based math [00:04:17]
        size = 0;
    }

    /*
     * INSERTION LOGIC: [00:07:55]
     * 1. Insert at the end of the array to maintain CBT property.
     * 2. Compare with parent; if larger, swap (Up-Heapify).
     * 3. Repeat until the correct position is found.
     */
    void insert(int val) {
        size = size + 1;       // Step 1: Increase size
        int index = size;      
        arr[index] = val;      // Add at the last position [00:08:02]

        // Step 2: Move the element up to satisfy Max-Heap property [00:08:23]
        while (index > 1) {
            int parent = index / 2; // Calculate parent index

            if (arr[parent] < arr[index]) {
                swap(arr[parent], arr[index]); // Swap if child is bigger [00:08:47]
                index = parent;                // Move pointer to parent
            } else {
                return; // Parent is already larger, heap property satisfied [00:09:15]
            }
        }
    }

    /*
     * DELETION LOGIC (Root Deletion): [00:13:28]
     * 1. Copy last element to root.
     * 2. Decrease size (removes the actual last element).
     * 3. Compare root with children; swap with the LARGER child (Down-Heapify).
     */
    void deleteFromHeap() {
        if (size == 0) {
            cout << "Heap is empty!" << endl;
            return;
        }

        // Step 1: Put last element into root [00:14:25]
        arr[1] = arr[size];
        
        // Step 2: Remove last element [00:14:37]
        size--;

        // Step 3: Propagate the new root down (Heapify Down) [00:14:54]
        int i = 1;
        while (i < size) {
            int leftIndex = 2 * i;
            int rightIndex = 2 * i + 1;
            int largest = i;

            // Check if Left child exists and is larger [00:15:08]
            if (leftIndex <= size && arr[largest] < arr[leftIndex]) {
                largest = leftIndex;
            }
            // Check if Right child exists and is even larger [00:15:32]
            if (rightIndex <= size && arr[largest] < arr[rightIndex]) {
                largest = rightIndex;
            }

            // If a child was larger, swap and continue down [00:16:41]
            if (largest != i) {
                swap(arr[i], arr[largest]);
                i = largest;
            } else {
                return; // Node is in its correct place [00:16:58]
            }
        }
    }

    void print() {
        for (int i = 1; i <= size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

/*
-------------------------------------------------------------------------------------------
3. COMPLEXITY SUMMARY: [00:17:22]
-------------------------------------------------------------------------------------------
- Time (Insert): O(log N)
- Time (Delete): O(log N)
- Space: O(N) to store the elements in the array.
===========================================================================================
*/