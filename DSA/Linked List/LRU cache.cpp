https://leetcode.com/problems/lru-cache/description/

/*(Haven;t done it along with least frequently use[LFU])
===========================================================================================
PROBLEM: LRU Cache (Least Recently Used)
===========================================================================================


-------------------------------------------------------------------------------------------
1. QUESTION EXPLANATION:
-------------------------------------------------------------------------------------------
The goal is to design a "Cache" (temporary fast storage) with a fixed capacity.
- get(key): Return the value of the key if it exists, otherwise return -1.
- put(key, value): 
    - If the key exists, update its value.
    - If the key is new, add it.
    - If the cache is FULL, you must remove the LEAST RECENTLY USED (LRU) item
      before adding the new one.

Definition of "Used": An item is considered "used" if it is either fetched (get) 
or updated/added (put).

-------------------------------------------------------------------------------------------
2. INTUITION & STRATEGY:
-------------------------------------------------------------------------------------------
- We need O(1) Access: A Hash Map (map/unordered_map) is perfect for this.
- We need O(1) Re-ordering: If we use an Array, moving an element to the front 
  takes O(N). If we use a Singly Linked List, deleting a node takes O(N) because 
  we need the previous node's pointer.
- SOLUTION: A Doubly Linked List (DLL). 
  - It allows us to delete a node in O(1) if we have its address.
  - It allows us to add a node to the head in O(1).
-------------------------------------------------------------------------------------------
1. ARCHITECTURAL OVERVIEW:
-------------------------------------------------------------------------------------------
To achieve O(1) for both get() and put(), we use two data structures:
- Doubly Linked List (DLL): Maintains the "order of use."
    - Head (Dummy): Recently used items are moved/inserted here.
    - Tail (Dummy): Least recently used items reside here, ready for eviction.
- Map (std::map): Provides O(log N) lookup to the Node pointers. 
  Note: Using 'unordered_map' would make it O(1) average.

-------------------------------------------------------------------------------------------
2. LINE-BY-LINE EXPLANATION:
-------------------------------------------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

// Node: The building block of our DLL.
// Each node stores key AND val so that when we evict from DLL (using tail->prev),
// we know which key to erase from the Map.
class Node {
public:
    int key, val;
    Node *next, *prev;

    Node() { key = val = -1; next = prev = NULL; } // Dummy node constructor
    Node(int k, int value) { key = k; val = value; next = prev = NULL; } // Data node
};



class LRUCache {
private:
    map<int, Node*> mpp; // Stores {Key -> Address of Node in DLL}
    int cap;             // Maximum items the cache can hold
    Node *head, *tail;   // Sentinel (dummy) nodes to avoid null-pointer checks

    // Method to remove a node's existing links.
    // Logic: Tell the neighbors to point to each other, bypassing this node.
    void deleteNode(Node* node) {
        Node* prevNode = node->prev;
        Node* nextNode = node->next;
        prevNode->next = nextNode;
        nextNode->prev = prevNode;
    }

    // Method to place a node at the "Newest" position (right after dummy head).
    void insertAfterHead(Node* node) {
        Node* nextNode = head->next;
        head->next = node;
        nextNode->prev = node;
        node->prev = head;
        node->next = nextNode;
    }



public:
    LRUCache(int capacity) {
        cap = capacity;
        mpp.clear();
        head = new Node(); // Dummy head
        tail = new Node(); // Dummy tail
        head->next = tail; // Initially, head points to tail
        tail->prev = head; // and tail points back to head
    }

    int get(int key_) {
        // Step 1: Check if key exists in the map
        if (mpp.find(key_) == mpp.end()) return -1;

        Node* node = mpp[key_];
        int val = node->val;

        // Step 2: Since it's accessed, it's now "Recently Used."
        // We move it from its current position to the front.
        deleteNode(node);
        insertAfterHead(node);

        return val;
    }

    void put(int key_, int value) {
        // Case 1: Key exists. Update value and move to front.
        if (mpp.find(key_) != mpp.end()) {
            Node* node = mpp[key_];
            node->val = value;
            deleteNode(node);
            insertAfterHead(node);
            return;
        }

        // Case 2: Cache is full. Evict the LRU node.
        if (mpp.size() == cap) {
            Node* lruNode = tail->prev; // Node right before dummy tail is oldest
            mpp.erase(lruNode->key);    // Remove from map using the key stored in node
            deleteNode(lruNode);        // Remove from DLL
            // Note: In a real system, you'd 'delete lruNode' here to free memory.
        }

        // Case 3: New Key. Create node, add to map, and insert at front.
        Node* newNode = new Node(key_, value);
        mpp[key_] = newNode;
        insertAfterHead(newNode);
    }
};

/*
-------------------------------------------------------------------------------------------
3. CRITICAL NOTES:
-------------------------------------------------------------------------------------------
- Why Dummy Nodes? [00:05:22] They remove the need to check 'if (head == NULL)' 
  during every insertion or deletion, making the code cleaner and faster.
- Map vs Unordered_Map: Your code uses 'std::map' (Red-Black Tree, O(log N)). 
  For true O(1), 'std::unordered_map' (Hash Table) is preferred.
- Memory Leak: Every 'new Node' in put() adds to the heap. When a node is evicted 
  (deleteNode), it should be 'deleted' from memory to prevent leaks.
===========================================================================================
*/