/*
Floor and Ceil in Sorted Array

Floor: Largest number in the array ≤ x.
Ceil: Smallest number in the array ≥ x.

Examples:
- For arr = [10, 20, 30, 40, 50], x = 25:
  - Floor = 20
  - Ceil = 30
- For arr = [10, 20, 25, 30, 40], x = 25:
  - Floor = 25
  - Ceil = 25

Logic & Intuition:
- Both can be found using modified binary search.
- Floor: search for the largest element less than or equal to x.
- Ceil: search for the smallest element greater than or equal to x.

Steps for Floor:
1. Initialize low = 0, high = n - 1, ans = -1 (means floor not found).
2. While low <= high:
   - mid = low + (high - low)/2
   - If arr[mid] <= x:
     - ans = arr[mid] (candidate for floor)
     - low = mid + 1 (try to find larger floor)
   - Else:
     - high = mid - 1 (floor must be in left half)
3. Return ans.

Steps for Ceil:
1. Initialize low = 0, high = n - 1, ans = -1 (means ceil not found).
2. While low <= high:
   - mid = low + (high - low)/2
   - If arr[mid] >= x:
     - ans = arr[mid] (candidate for ceil)
     - high = mid - 1 (try to find smaller ceil)
   - Else:
     - low = mid + 1 (ceil must be in right half)
3. Return ans.

Code Implementation:
*/

int floorInSortedArray(const vector<int>& arr, int x) {
    int low = 0, high = (int)arr.size() - 1;
    int ans = -1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] <= x) {
            ans = arr[mid];
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    
    return ans;
}

int ceilInSortedArray(const vector<int>& arr, int x) {
    int low = 0, high = (int)arr.size() - 1;
    int ans = -1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] >= x) {
            ans = arr[mid];
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    
    return ans;
}

/*
Notes:
- Use 'mid = low + (high - low)/2' to avoid overflow.
- Floor and Ceil search vary only by comparison direction.
- Returns -1 if floor or ceil does not exist in array.
- Both run in O(log n) time and O(1) extra space.
- Can be used to solve range query and insertion problems efficiently.
*/
