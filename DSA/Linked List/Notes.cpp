/*
===========================================================================================
TOPIC: LINKED LIST DELETION & INSERTION (8 VARIETIES)
===========================================================================================

-------------------------------------------------------------------------------------------
1. DELETION OF HEAD [00:00:30]
-------------------------------------------------------------------------------------------
- Logic: Move the head pointer to head->next.
- C++ Note: Manually free the memory of the old head using 'delete' or 'free' [00:02:52].
- Java Note: Garbage collector handles memory once references are removed [00:03:08].

-------------------------------------------------------------------------------------------
2. DELETION OF TAIL [00:06:18]
-------------------------------------------------------------------------------------------
- Logic: Stop at the second-to-last node. Set its 'next' pointer to NULL.
- Edge Case: If the list is empty or has only one node, return NULL [00:08:04].

-------------------------------------------------------------------------------------------
3. DELETION OF K-TH ELEMENT [00:15:47]
-------------------------------------------------------------------------------------------
- Logic: Use a counter to reach the K-th node. Maintain a 'previous' pointer.
- Linkage: previous->next = previous->next->next.

-------------------------------------------------------------------------------------------
4. DELETION OF NODE WITH VALUE [00:30:15]
-------------------------------------------------------------------------------------------
- Logic: Similar to K-th deletion, but check if temp->data == value instead of a counter.

-------------------------------------------------------------------------------------------
5. INSERTION AT HEAD [00:32:15]
-------------------------------------------------------------------------------------------
- Logic: Create a new node. Set its 'next' to the current head. Return the new node as head.

-------------------------------------------------------------------------------------------
6. INSERTION AT TAIL [00:35:15]
-------------------------------------------------------------------------------------------
- Logic: Traverse to the last node (where temp->next == NULL). Set temp->next to the new node.

-------------------------------------------------------------------------------------------
7. INSERTION AT K-TH POSITION [00:38:40]
-------------------------------------------------------------------------------------------
- Logic: Traverse to the (K-1)th position. Point new_node->next to temp->next, then temp->next to new_node.

-------------------------------------------------------------------------------------------
8. INSERTION BEFORE VALUE X [00:51:25]
-------------------------------------------------------------------------------------------
- Logic: Traverse until temp->next->data == X. Insert the new node between temp and temp->next.
===========================================================================================
*/

#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val, Node* next_ptr = nullptr) : data(val), next(next_ptr) {}
};

// --- DELETION FUNCTIONS ---

// 1. Remove Head [00:04:05]
Node* removeHead(Node* head) {
    if (head == nullptr) return nullptr;
    Node* temp = head;
    head = head->next;
    delete temp;
    return head;
}

// 2. Remove Tail [00:12:40]
Node* removeTail(Node* head) {
    if (head == nullptr || head->next == nullptr) return nullptr;
    Node* temp = head;
    while (temp->next->next != nullptr) {
        temp = temp->next;
    }
    delete temp->next;
    temp->next = nullptr;
    return head;
}

// 3. Remove K-th Element [00:26:40]
Node* removeK(Node* head, int k) {
    if (head == nullptr) return nullptr;
    if (k == 1) return removeHead(head);

    Node* temp = head;
    Node* prev = nullptr;
    int cnt = 0;
    while (temp != nullptr) {
        cnt++;
        if (cnt == k) {
            prev->next = prev->next->next;
            delete temp;
            break;
        }
        prev = temp;
        temp = temp->next;
    }
    return head;
}

// 4. Remove Element by Value [00:30:48]
Node* removeElement(Node* head, int el) {
    if (head == nullptr) return nullptr;
    if (head->data == el) return removeHead(head);

    Node* temp = head;
    Node* prev = nullptr;
    while (temp != nullptr) {
        if (temp->data == el) {
            prev->next = prev->next->next;
            delete temp;
            break;
        }
        prev = temp;
        temp = temp->next;
    }
    return head;
}

// --- INSERTION FUNCTIONS ---

// 5. Insert at Head [00:33:50]
Node* insertHead(Node* head, int val) {
    return new Node(val, head);
}

// 6. Insert at Tail [00:37:06]
Node* insertTail(Node* head, int val) {
    if (head == nullptr) return new Node(val);
    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = new Node(val);
    return head;
}

// 7. Insert at Position K [00:48:26]
Node* insertPosition(Node* head, int val, int k) {
    if (head == nullptr) {
        if (k == 1) return new Node(val);
        else return nullptr;
    }
    if (k == 1) return new Node(val, head);

    int cnt = 0;
    Node* temp = head;
    while (temp != nullptr) {
        cnt++;
        if (cnt == k - 1) {
            Node* newNode = new Node(val, temp->next);
            temp->next = newNode;
            break;
        }
        temp = temp->next;
    }
    return head;
}

// 8. Insert Before Value [00:52:38]
Node* insertBeforeValue(Node* head, int val, int target) {
    if (head == nullptr) return nullptr;
    if (head->data == target) return new Node(val, head);

    Node* temp = head;
    while (temp->next != nullptr) {
        if (temp->next->data == target) {
            Node* newNode = new Node(val, temp->next);
            temp->next = newNode;
            break;
        }
        temp = temp->next;
    }
    return head;
}

// Utility to print LL
void printLL(Node* head) {
    while (head != nullptr) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    vector<int> arr = {12, 5, 8, 7};
    // Initialize LL...
    return 0;
}