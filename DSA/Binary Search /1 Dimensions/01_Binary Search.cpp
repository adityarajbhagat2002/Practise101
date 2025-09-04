/*
Binary Search – Full Notes

Problem Name:
Binary Search (Search for Target in Sorted Array)

Problem Statement:
Given a sorted array of size n and a target value, find the index of the target using binary search. If not present, return -1.

Logic and Intuition:
Binary Search is used for searching in a sorted search space (typically arrays, but the idea generalizes).
Instead of scanning every element (linear search), divide the space in half at every step until the target is found or the space is exhausted.
At every step, compare the target with the middle element:
- If equal, found!
- If less, move the search to the left half.
- If greater, move the search to the right half.
Key Property: Always applicable only on sorted data.

Real Life Analogy:
Looking up a word in a dictionary (alphabetically sorted). Rather than checking page by page, you open in the middle and continue halving the search space.

Edge Cases:
- Target not in array (return -1).
- Target at very first or last position.
- Array of size 1 (and target may/may not be present).
- Arrays with very large boundaries (risk of overflow in mid calculation).
- Duplicates: In the standard binary search, returns any valid index of the target (often the first occurrence if you break on match).

Steps:
1. Initialize: low = 0, high = n - 1.
2. Check search space: While low <= high:
   - Compute mid = low + (high - low) / 2 (prevents overflow).
   - If nums[mid] == target, return mid.
   - If nums[mid] < target, search right half: low = mid + 1.
   - If nums[mid] > target, search left half: high = mid - 1.
3. Stop: If low > high, target not present; return -1.

Recursive Version:
- At each call, check base condition (low > high).
- Recurse on appropriate half.
- See code below for direct implementation.

Why It Works:
- Each division reduces the search space by half.
- On sorted input, correct half always contains (or excludes) the target.
- Logs the number of operations: worst case is log₂(n) steps.
- Overflow Caution: Use mid = low + (high - low) / 2 instead of (low + high) / 2 especially for large data.

Time and Space Complexity:
- Time Complexity: O(log N) — Each step halves the search interval.
- Space Complexity: O(1) for iterative, O(log N) stack for recursive (due to recursive calls).

*/

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        int low = 0;
        int high = n - 1;
        return binarySearch(nums, low, high, target);
    }

    int binarySearch(vector<int>& nums, int low, int high, int target) {
        int mid = low + (high - low) / 2;

        if (low > high) return -1;
        if (nums[mid] == target) return mid;
        else if (target > nums[mid]) return binarySearch(nums, mid + 1, high, target);
        else return binarySearch(nums, low, mid - 1, target);
    }
};

/*
Extra Notes:
- Iterative Version is more space-efficient (O(1)), but recursion is clear and concise for conceptual illustration.
- For very large search spaces (e.g., int boundaries), always use mid = low + (high - low) / 2 to avoid overflow.
- Binary search is a foundational algorithm and forms the basis for more advanced searching and optimization techniques.
- Commonly used for problems involving the “first/last occurrence,” “smallest/largest satisfying condition,” or searching in a monotonic answer space.
- Practice tips: Always check for off-by-one errors in your search boundaries (low, high).
*/
