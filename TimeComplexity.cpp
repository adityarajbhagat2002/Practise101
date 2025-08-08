/*
✅ Understanding the 10⁷ / 10⁸ Time Complexity Benchmark
In competitive programming or coding interviews, a common rule of thumb is:

✅ Your solution should run within 1 second.
In 1 second, a modern processor can handle about 10⁷ to 10⁸ operations.

This is why when analyzing the time complexity of your algorithm, you’ll often see the goal is to make it efficient enough to run under this limit.

📌 Why 10⁷ or 10⁸ operations per second?
It’s based on:

Average processing speed of online judge platforms (e.g., Leetcode, Codeforces, etc.)

CPU cycles: Each operation (comparison, addition, loop iteration) can take several CPU cycles.

Online judges set time limits usually at 1 or 2 seconds per test case.

So you can assume:

Time	Maximum allowed operations
1 sec	~10⁷ – 10⁸
2 sec	~2×10⁷ – 2×10⁸

📊 Example of Time Complexities That Fit
Let’s say the input size is:

n = 10⁵ → OK for O(n log n) or O(n)

n = 10⁶ → OK for O(n) or O(n log n) with careful coding

n = 10⁹ → Must be O(1) or very optimized math/logic

💡 How to Use This Rule
Input Size	Acceptable Time Complexity
n ≤ 10³	O(n²), O(n log n), O(n) fine
n ≤ 10⁵	O(n log n), O(n) ✅
n ≤ 10⁶	O(n), ideally no nested loops
n > 10⁶	O(log n) or O(1) only

So if you see constraints like 1 ≤ n ≤ 10⁵, your algorithm should be O(n log n) or better.
*/
