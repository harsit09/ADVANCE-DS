#include <iostream>
using namespace std;

// Node structure for XOR Linked List
struct Node {
    int data;
    Node* npx; // XOR of next and previous node addresses

    Node(int value) : data(value), npx(nullptr) {}
};

// XOR Linked List class
class XORLinkedList {
private:
    Node* head; // Head of the list
    Node* tail; // Tail of the list

    // Utility function to XOR two node pointers
    Node* XOR(Node* a, Node* b) {
        return reinterpret_cast<Node*>(reinterpret_cast<uintptr_t>(a) ^ reinterpret_cast<uintptr_t>(b));
    }

public:
    // Constructor
    XORLinkedList() : head(nullptr), tail(nullptr) {}

    // Insert at the end
    void insert(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            // If the list is empty
            head = tail = newNode;
        } else {
            // Update the tail's npx and the new node's npx
            newNode->npx = XOR(tail, nullptr);
            tail->npx = XOR(tail->npx, newNode);
            tail = newNode;
        }
    }

    // Display the list in forward direction
    void displayForward() {
        Node* current = head;
        Node* prev = nullptr;
        Node* next;

        cout << "Forward: ";
        while (current) {
            cout << current->data << " ";
            // Compute the next node using XOR
            next = XOR(prev, current->npx);
            prev = current;
            current = next;
        }
        cout << endl;
    }

    // Display the list in reverse direction
    void displayReverse() {
        Node* current = tail;
        Node* next = nullptr;
        Node* prev;

        cout << "Reverse: ";
        while (current) {
            cout << current->data << " ";
            // Compute the previous node using XOR
            prev = XOR(next, current->npx);
            next = current;
            current = prev;
        }
        cout << endl;
    }

    // Destructor to clean up memory
    ~XORLinkedList() {
        Node* current = head;
        Node* prev = nullptr;
        Node* next;

        while (current) {
            next = XOR(prev, current->npx);
            delete current;
            prev = current;
            current = next;
        }
    }
};

// Main function to demonstrate the XOR Linked List
int main() {
    XORLinkedList list;

    // Insert elements
    list.insert(10);
    list.insert(20);
    list.insert(30);
    list.insert(40);

    // Display the list
    list.displayForward();  // Output: Forward: 10 20 30 40
    list.displayReverse();  // Output: Reverse: 40 30 20 10

    return 0;
}