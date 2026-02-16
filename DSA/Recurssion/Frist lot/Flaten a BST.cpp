/*
===========================================================================================
FLATTEN BST TO SORTED LIST (LINKED LIST STYLE)
===========================================================================================
Source: CodeStoryWithMIK (YouTube Video 12)
Concept: Magic of Recursion / Flattening Category
Complexity: Time O(N) | Space O(N) [Recursion Stack Depth]

-------------------------------------------------------------------------------------------
PROBLEM DESCRIPTION:
- Convert a Binary Search Tree (BST) into a sorted "linked list" in-place.
- Requirements: 
  1. The left child of every node must be NULL. [00:02:43]
  2. The right child must point to the next element in sorted order (In-order).
  3. No extra space (Auxiliary) allowed, only recursion stack. [00:03:05]

-------------------------------------------------------------------------------------------
THE RECURSION STORY (TRUST THE PROCESS):
1. Left Subtree: Ask recursion to flatten the left subtree. It returns the 'head' 
   of that flattened list. [00:05:35]
2. Break Bond: Set root->left = NULL (required by problem). [00:07:51]
3. Bridge Connection: If the left flattened list exists, find its 'tail' (last node)
   and connect its right pointer to our current 'root'. [00:08:29]
4. Right Subtree: Ask recursion to flatten the right subtree and attach it to 
   root->right. [00:11:11]
5. Return Head: If left existed, return the head of the left list. Otherwise, 
   the root itself is the head. [00:12:13]

-------------------------------------------------------------------------------------------
CORNER CASE: [00:17:22]
- If root->left is NULL, our 'head' from recursion will be NULL. 
- In this case, the current 'root' becomes the head of the sorted list for that branch.
===========================================================================================
*/

#include <iostream>

using namespace std;

/* Definition for Node */
struct Node {
    int data;
    Node *left;
    Node *right;
    Node(int val) {
        data = val;
        left = NULL;
        right = NULL;
    }
};

class Solution {
public:
    Node* flattenBST(Node* root) {
        // Base Case: An empty tree is already "flat" [00:15:33]
        if (!root) {
            return NULL;
        }

        // 1. Flatten the left subtree and get the head [00:05:35]
        Node* head = flattenBST(root->left);

        // 2. Break the left pointer bond (Requirement) [00:07:51]
        root->left = NULL;

        // 3. Connect the flattened left part to the current root [00:17:51]
        if (head != NULL) {
            Node* temp = head;
            // Traverse to the end of the left-flattened list [00:08:42]
            while (temp->right != NULL) {
                temp = temp->right;
            }
            temp->right = root; // Last node of left list points to root
        } else {
            // If there's no left part, current root is the head of this sorted segment
            head = root;
        }

        // 4. Flatten the right subtree and attach to root->right [00:11:11]
        root->right = flattenBST(root->right);

        // 5. Return the start of our sorted list [00:13:15]
        return head;
    }
};
/*
flattenBST(5)
│
├── flattenBST(3)
│   │
│   ├── flattenBST(2)
│   │   │
│   │   ├── flattenBST(NULL) → returns NULL
│   │   │
│   │   ├── head = NULL → so head = 2
│   │   │
│   │   ├── flattenBST(NULL) → returns NULL
│   │   │
│   │   └── return head = 2
│   │
│   ├── attach 3 to tail of [2] → 2 → 3
│   │
│   ├── flattenBST(4)
│   │   │
│   │   ├── flattenBST(NULL) → NULL
│   │   ├── head = 4
│   │   ├── flattenBST(NULL) → NULL
│   │   └── return 4
│   │
│   ├── attach 4 to right of 3 → 2 → 3 → 4
│   │
│   └── return head = 2
│
├── attach 5 to tail of [2 → 3 → 4]
│     → 2 → 3 → 4 → 5
│
├── flattenBST(7)
│   │
│   ├── flattenBST(6)
│   │   │
│   │   ├── flattenBST(NULL) → NULL
│   │   ├── head = 6
│   │   ├── flattenBST(NULL) → NULL
│   │   └── return 6
│   │
│   ├── attach 7 to tail of [6] → 6 → 7
│   │
│   ├── flattenBST(8)
│   │   │
│   │   ├── flattenBST(NULL) → NULL
│   │   ├── head = 8
│   │   ├── flattenBST(NULL) → NULL
│   │   └── return 8
│   │
│   ├── attach 8 to right of 7 → 6 → 7 → 8
│   │
│   └── return head = 6
│
├── attach right list to 5 → 2 → 3 → 4 → 5 → 6 → 7 → 8
│
└── return head = 2

*/