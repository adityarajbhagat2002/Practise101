/*
===========================================================================================
PROBLEM: Sort a Stack (Recursive Approach)
===========================================================================================

-------------------------------------------------------------------------------------------
1. LOGIC AND INTUITION: [00:03:18]
-------------------------------------------------------------------------------------------
- To sort a stack without extra space (auxiliary structures), we use the Recursion Stack.
- The process has two main phases:
    Phase A (Sort function): [00:09:44]
    1. Pop the top element and store it.
    2. Recursively call sort() on the remaining stack.
    3. Once the stack is empty (base case), start Phase B.

    Phase B (SortedInsert function): [00:05:26]
    1. For each popped element, check if the stack is empty OR the top element is 
       smaller than the current element. [00:11:02]
    2. If yes, push the element (since it's in the correct sorted order).
    3. If no (top is greater), pop the top, recursively call SortedInsert, 
       and then push the popped element back. [00:11:14]

-------------------------------------------------------------------------------------------
2. TIME AND SPACE COMPLEXITY: [00:12:43]
-------------------------------------------------------------------------------------------
- Time Complexity: O(N^2)
    - For every element (N), we might traverse the rest of the stack (N) to find 
      its correct position during SortedInsert. [00:14:46]
- Space Complexity: O(N)
    - Due to the recursive call stack (at most N frames). [00:15:01]

-------------------------------------------------------------------------------------------
3. OPTIMIZED CODE IMPLEMENTATION (C++):
-------------------------------------------------------------------------------------------
*/

#include <iostream>
#include <stack>

using namespace std;

// Helper function to insert an element in its correct sorted position [00:05:26]
void sortedInsert(stack<int>& s, int element) {
    // Base case: Stack is empty OR current element is greater than the top [00:11:02]
    // Note: To sort in descending order (top is smallest), change '>' to '<'.
    if (s.empty() || element > s.top()) {
        s.push(element); [00:11:02]
        return;
    }

    // If the top is greater, remove it and find the correct spot for 'element' [00:11:14]
    int n = s.top();
    s.pop();

    // Recursive call to go deeper into the stack
    sortedInsert(s, element); [00:11:29]

    // Push the removed top back once the element is inserted [00:12:05]
    s.push(n);
}

// Main function to sort the stack [00:09:44]
void sortStack(stack<int>& s) {
    // Base case: Stack is empty
    if (s.empty()) {
        return; [00:04:39]
    }

    // Phase A: Remove the top element [00:03:38]
    int num = s.top();
    s.pop();

    // Recursive call to sort the remaining stack [00:03:49]
    sortStack(s);

    // Phase B: Insert the popped element back in sorted order [00:11:38]
    sortedInsert(s, num);
}


/*
-------------------------------------------------------------------------------------------
4. DRY RUN: [00:04:12]
-------------------------------------------------------------------------------------------
Stack: [11, 2, 32, 3] (top is 3)
1. sortStack pops 3, then 32, then 2, then 11.
2. Stack is empty.
3. sortedInsert(11) -> Stack: [11]
4. sortedInsert(2)  -> 11 > 2, pop 11, push 2, push 11 -> Stack: [2, 11]
5. sortedInsert(32) -> 32 > 11, push 32 -> Stack: [2, 11, 32]
6. sortedInsert(3)  -> 32 > 3, pop 32, call insert(3)... eventually Stack: [2, 3, 11, 32]
===========================================================================================
*/