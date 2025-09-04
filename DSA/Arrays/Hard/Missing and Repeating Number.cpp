/*
Find the Missing and Repeating Number

Problem Name:
Find the Missing and Repeating Number

Problem Statement:
Given an array of size n containing numbers from 1 to n, find the one missing number and one repeating number in the array.

Example:
Input: [3, 1, 2, 5, 3]
Output:
Repeating = 3
Missing = 4

---

Logic and Intuition:
- The numbers are from 1 to n, one number repeats, one number is missing.
- Brute Force: Check for each number from 1 to n how many times it occurs in the array.
- Better Approach (Hashing): Use a frequency array to count occurrences.
- Optimal Approaches:
    - Mathematical approach using formulas for sum and sum of squares.
    - XOR-based method exploiting properties of XOR operation.

---

Edge Cases:
- Array size 1.
- Repeated number is the first or last element.
- Missing number is 1 or n.
- Multiple duplicates or missing (handle gracefully if out of spec).
- Unsigned/signed integers—watch for overflow.

---

Steps to Solve:

Brute Force:
- For each number from 1 to n, count appearances in the array.
- Identify missing (count = 0) and repeating (count = 2).

Hashing:
- Use a frequency array of size n+1 initialized to 0.
- Increment count for each number in the input.
- Identify the missing and repeating based on frequency counts.

Mathematical Approach:
- Sum of numbers from 1 to n = n(n+1)/2.
- Sum of squares of numbers from 1 to n = n(n+1)(2n+1)/6.
- Calculate sum and sum of squares of array elements.
- Let repeating number = X, missing number = Y.
- Use two equations derived from sums and sums of squares to solve for X and Y.

XOR Approach:
- XOR all elements in the array and numbers from 1 to n.
- The result is XOR of missing and repeating numbers.
- Identify any set bit in the XOR result.
- Divide array elements and numbers from 1 to n into two categories based on set bit.
- XOR within categories gives missing and repeating numbers.

---

Why It Works:
- Frequencies accurately show missing and repeating elements.
- Mathematical formulas leverage properties of arithmetic progressions.
- XOR properties allow isolation of differing bits between missing and repeating numbers.

---

Time and Space Complexity:
Approach                 Time Complexity    Space Complexity
Brute Force              O(n²)             O(1)
Hashing                  O(n)              O(n)
Mathematical Approach    O(n)              O(1)
XOR Approach             O(n)              O(1)

Mathematical and XOR approaches are preferred for their time-space efficiency.

---

Code (Mathematical Approach):
*/
#include <vector>
#include <cmath>
using namespace std;

class Solution {
public:
    vector<int> findTwoElement(vector<int> &arr) {
        long long n = arr.size();
        long long sum_n = (n * (n + 1)) / 2;
        long long sum_sq_n = (n * (n + 1) * (2 * n + 1)) / 6;

        long long sum_arr = 0, sum_sq_arr = 0;
        for (int num : arr) {
            sum_arr += (long long)num;
            sum_sq_arr += (long long)num * (long long)num;
        }

        long long val1 = sum_arr - sum_n;          // X - Y
        long long val2 = sum_sq_arr - sum_sq_n;    // X² - Y²

        val2 = val2 / val1;    // X + Y

        long long X = (val1 + val2) / 2;
        long long Y = val2 - X;

        return {(int)X, (int)Y};  // Repeating, Missing
    }
};

/*
Code (XOR Approach):
*/
#include <vector>
using namespace std;

class SolutionXOR {
public:
    vector<int> findTwoElement(vector<int> &arr) {
        int n = arr.size();
        int xor_val = 0;
        for (int i = 0; i < n; i++) {
            xor_val ^= arr[i];
            xor_val ^= (i + 1);
        }

        // Find rightmost set bit
        int set_bit = xor_val & ~(xor_val - 1);

        int x = 0, y = 0;
        for (int i = 0; i < n; i++) {
            if (arr[i] & set_bit)
                x ^= arr[i];
            else
                y ^= arr[i];

            if ((i + 1) & set_bit)
                x ^= (i + 1);
            else
                y ^= (i + 1);
        }

        // Determine which is missing and which is repeating
        for (int i = 0; i < n; i++) {
            if (arr[i] == x)
                return {x, y};
            if (arr[i] == y)
                return {y, x};
        }

        return {};
    }
};

/*
Extra Notes:
- Mathematical method is straightforward and elegant but may suffer from overflow; use long long.
- XOR method is clever and uses bit manipulation; more robust against overflow.
- Hashing approach is simpler to implement but uses extra space.
- Brute force is simple but inefficient.
- Always clarify if input array modification is allowed before using in-place approaches.
- Useful for interviews to discuss multiple approaches emphasizing trade-offs.
*/
