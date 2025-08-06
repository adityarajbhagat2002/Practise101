// Leetcode 268: Missing Number
// ✅ Find the missing number from an array of size n with elements from 0 to n

// 🔸Solution 1: Using Sum Formula (n*(n+1)/2)
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int actualsum = 0;   // Sum from 0 to n
        int numssum = 0;     // Sum of elements in the given array
        int n = nums.size();

        // Step 1: Calculate the sum of first n natural numbers (0 to n)
        for(int i = 0; i <= n; i++){
            actualsum += i;
        }     

        // Step 2: Calculate the sum of elements present in the array
        for(int i = 0; i < n; i++){
            numssum += nums[i];
        }

        // Step 3: The difference gives the missing number
        return (actualsum - numssum);
    }
};

/*
Why This Works:
----------------
- Sum of numbers from 0 to n = n * (n + 1) / 2
- Missing number = total expected sum - sum of array elements

Example:
Input: nums = [3, 0, 1]
n = 3 → Total Sum = 6
Array Sum = 4
Missing = 6 - 4 = 2

Time Complexity: O(n)
Space Complexity: O(1)
*/


// 🔸Solution 2: Using XOR
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        int xor1 = 0, xor2 = 0;

        // XOR all numbers from 0 to n
        for(int i = 0; i <= n; i++) {
            xor1 ^= i;
        }

        // XOR all elements in the array
        for(int i = 0; i < n; i++) {
            xor2 ^= nums[i];
        }

        // Missing number = xor1 ^ xor2
        return xor1 ^ xor2;
    }
};

/*
Why This Works:
----------------
- XOR of a number with itself is 0: a ^ a = 0
- XOR of a number with 0 is the number itself: a ^ 0 = a
- So, XOR all from 0 to n and XOR all array elements → remaining number is the missing one

Example:
nums = [3, 0, 1]
xor1 = 0 ^ 1 ^ 2 ^ 3 = 0
xor2 = 3 ^ 0 ^ 1 = 2
Missing = xor1 ^ xor2 = 2

When To Use:
-------------
- Use this when you want O(1) space and slightly optimized logic
- Works well when overflow is a concern with large values (compared to sum formula)

Time Complexity: O(n)
Space Complexity: O(1)
*/
