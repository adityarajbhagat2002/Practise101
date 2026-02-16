
/*
===========================================================================================
REVERSE A STACK - COMPLETE GUIDE
===========================================================================================
Source: GeeksForGeeks / CodeStoryWithMIK (YouTube)
Companies: Amazon, Microsoft, Goldman Sachs

-------------------------------------------------------------------------------------------
PROBLEM STATEMENT:
You are given a stack `St`. You need to reverse the stack using recursion. 
You are not allowed to use any loop in the main reverse logic (for Approach 2).

Example:
Input:  St = [3, 2, 1, 7, 6] (Top to Bottom)
Output: [6, 7, 1, 2, 3] (Top to Bottom)

-------------------------------------------------------------------------------------------
APPROACH 1: Recursive Story + Temp Stack
Logic:
1. Pop the top element and store it.
2. Recursively call `Reverse()` for the remaining stack.
3. Once the rest of the stack is reversed, we need to put the original top at the bottom.
4. To do this, we use an auxiliary `temp` stack to empty the current stack, push the top 
   element, and then push everything back from `temp`.
   
COMPLEXITY:
- Time: O(N^2) - For each element, we empty the stack once.
- Space: O(N) - Extra temp stack.

-------------------------------------------------------------------------------------------
APPROACH 2: Recursive Story + Recursive InsertAtBottom
Logic:
1. Main Function (`Reverse`):
   - Base Case: If stack is empty, return. [00:11:20]
   - Extract top, pop it, and recursively reverse the rest. [00:07:04]
   - After recursion returns, use another recursive function `insertAtBottom` to put 
     the extracted element at the base. [00:14:22]

2. Helper Function (`insertAtBottom`):
   - Base Case: If stack is empty, push the element. [00:22:44]
   - Recursive Case: Keep popping elements and store them in the function's call stack, 
     then push them back after inserting the target element at the bottom. [00:19:20]

COMPLEXITY:
- Time: O(N^2) - For each Reverse call, insertAtBottom takes O(N).
- Space: O(N) - Only the recursion call stack space (O(1) auxiliary). [00:12:28]
===========================================================================================
*/


/************************************************************ C++ ************************************************************/
//Approach-1 (Using O(n) Auxiliary Space (we took extra one temp stack))
//Simply write a story like recursion and trust it
//Time : O(n^2)
//Space : O(n) Auxiliary Space (we took extra one temp stack)
class Solution{
public:
    void Reverse(stack<int> &St){
        if(St.empty()) {
            return;
        }
        
        int top = St.top();
        St.pop();
        Reverse(St); //I am hoping my Reverse function will reverse the remaining stack

        //Now I need to push top at the bottom of the stack
        stack<int> temp;
        while(!St.empty()) {
            temp.push(St.top());
            St.pop();
        }
      
        St.push(top); //push at bottom
        //Now push remaining elements
        while(!temp.empty()) {
            St.push(temp.top());
            temp.pop();
        }
    }
};



//Approach-2 (Using O(1) Auxiliary Space)
//Simply write a story like recursion and trust it
//Time : O(n^2)
//Space : O(1) Auxiliary Space
class Solution{
public:

    void insertAtBottom(stack<int>& St, int element) {
        if(St.empty()) {
            St.push(element);
            return;
        }
        
        int cur_top_el = St.top();
        St.pop();
        insertAtBottom(St, element);
        St.push(cur_top_el);
    }

    void Reverse(stack<int> &St){
        if(St.empty()) {
            return;
        }
        int top = St.top();
        St.pop();
        
        Reverse(St);
        insertAtBottom(St, top);
    }
};

