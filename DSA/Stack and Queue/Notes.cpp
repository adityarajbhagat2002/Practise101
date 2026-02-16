/*
===========================================================================================
TOPIC: STACKS AND QUEUES (COMPLETE GUIDE)
===========================================================================================

-------------------------------------------------------------------------------------------
1. THEORETICAL NOTES [00:00:55 - 00:06:12]
-------------------------------------------------------------------------------------------
* STACK:
  - Principle: LIFO (Last In First Out). The element added most recently is removed first.
  - Analogy: A stack of plates. You add to the top and take from the top.
  - Time Complexity: All basic operations (push, pop, top) are O(1).

* QUEUE:
  - Principle: FIFO (First In First Out). The element added first is removed first.
  - Analogy: A line at a ticket counter. The person who arrives first leaves first.
  - Time Complexity: Basic operations (enqueue, dequeue) are O(1).

-------------------------------------------------------------------------------------------
2. STACK IMPLEMENTATION (USING ARRAY) [00:11:25]
-------------------------------------------------------------------------------------------
*/

#include <iostream>
#include <queue>
#include <stack>

using namespace std;

class MyStack {
    int* arr;
    int topIndex;
    int capacity;

public:
    MyStack(int size) {
        capacity = size;
        arr = new int[capacity];
        topIndex = -1; // -1 indicates the stack is empty [00:12:10]
    }

    // Push: O(1)
    void push(int x) {
        if (topIndex == capacity - 1) {
            cout << "Stack Overflow" << endl;
            return;
        }
        topIndex++;
        arr[topIndex] = x; // Add element and move pointer [00:16:17]
    }

    // Pop: O(1)
    void pop() {
        if (topIndex == -1) {
            cout << "Stack Underflow" << endl;
            return;
        }
        topIndex--; // Simply move the pointer back [00:17:44]
    }

    // Top: O(1)
    int top() {
        if (topIndex == -1) return -1;
        return arr[topIndex]; [00:17:05]
    }

    int size() {
        return topIndex + 1;
    }
};

/*
-------------------------------------------------------------------------------------------
3. QUEUE IMPLEMENTATION (USING ARRAY) [00:20:45]
-------------------------------------------------------------------------------------------
* Note: A circular array is used to prevent wasting space after pops.
*/

class MyQueue {
    int *arr;
    int start, end, currSize, maxSize;

public:
    MyQueue(int n) {
        arr = new int[n];
        start = -1;
        end = -1;
        currSize = 0;
        maxSize = n;
    }

    void push(int x) {
        if (currSize == maxSize) {
            cout << "Queue Full" << endl;
            return;
        }
        if (end == -1) {
            start = 0;
            end = 0;
        } else {
            end = (end + 1) % maxSize; // Circular increment [00:25:30]
        }
        arr[end] = x;
        currSize++;
    }

    void pop() {
        if (currSize == 0) {
            cout << "Queue Empty" << endl;
            return;
        }
        if (currSize == 1) {
            start = -1;
            end = -1;
        } else {
            start = (start + 1) % maxSize; // Circular increment
        }
        currSize--;
    }

    int front() {
        if (currSize == 0) return -1;
        return arr[start];
    }
};

/*
-------------------------------------------------------------------------------------------
4. STACK USING SINGLE QUEUE (LOGIC) [00:45:03]
-------------------------------------------------------------------------------------------
* Algorithm: 
  1. Push x into the queue.
  2. For (size - 1) times:
     - Take the front element and push it back into the queue.
     - Pop the front.
  3. This reverses the order so the last element is at the front (LIFO). [00:49:40]
*/

class StackUsingQueue {
    queue<int> q;

public:
    void push(int x) {
        int s = q.size();
        q.push(x);
        for (int i = 0; i < s; i++) {
            q.push(q.front());
            q.pop();
        }
    }

    void pop() { q.pop(); }
    int top() { return q.front(); }
};

/*
-------------------------------------------------------------------------------------------
5. QUEUE USING TWO STACKS (OPTIMIZED POP) [01:04:12]
-------------------------------------------------------------------------------------------
* Strategy: Use an input stack and an output stack.
  - Push: Always push to 'input'.
  - Pop/Top: If 'output' is empty, move EVERYTHING from 'input' to 'output'.
    This reverses the order and makes it FIFO.
*/

class QueueUsingStacks {
    stack<int> input, output;

public:
    void push(int x) {
        input.push(x); // O(1)
    }

    int pop() {
        if (output.empty()) {
            while (!input.empty()) {
                output.push(input.top());
                input.pop();
            }
        }
        int val = output.top();
        output.pop();
        return val; // Amortized O(1)
    }
};

/*
-------------------------------------------------------------------------------------------
SUMMARY OF COMPLEXITIES [01:06:50]
-------------------------------------------------------------------------------------------
| Operation | Stack (Array) | Queue (Array) | Stack (via Q) | Queue (via 2 Stacks) |
|-----------|---------------|---------------|---------------|----------------------|
| Push      | O(1)          | O(1)          | O(N)          | O(1)                 |
| Pop       | O(1)          | O(1)          | O(1)          | Amortized O(1)       |
| Top/Front | O(1)          | O(1)          | O(1)          | Amortized O(1)       |
===========================================================================================
*/