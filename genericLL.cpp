#include <iostream>
using namespace std;

// Node structure
template <typename T>
class Node {
public:
    T data;         // Data of the node
    Node* next;     // Pointer to the next node

    // Constructor
    Node(T value) {
        data = value;
        next = nullptr;
    }
};

// Generic Linked List class
template <typename T>
class LinkedList {
private:
    Node<T>* head; // Pointer to the head of the list

public:
    // Constructor
    LinkedList() {
        head = nullptr;
    }

    // Destructor to free memory
    ~LinkedList() {
        Node<T>* current = head;
        while (current) {
            Node<T>* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    // Insert a new node at the end
    void insert(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (!head) {
            head = newNode;
        } else {
            Node<T>* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Delete a node with the given value
    void remove(T value) {
        if (!head) {
            cout << "List is empty!" << endl;
            return;
        }

        // If the head node is to be deleted
        if (head->data == value) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        // Traverse the list to find the node
        Node<T>* temp = head;
        while (temp->next && temp->next->data != value) {
            temp = temp->next;
        }

        // If the node is found
        if (temp->next) {
            Node<T>* nodeToDelete = temp->next;
            temp->next = temp->next->next;
            delete nodeToDelete;
        } else {
            cout << "Value not found in the list!" << endl;
        }
    }

    // Print the linked list
    void display() const {
        Node<T>* temp = head;
        while (temp) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
};

// Main function to demonstrate the generic linked list
int main() {
    LinkedList<int> intList; // Linked list for integers
    intList.insert(10);
    intList.insert(20);
    intList.insert(30);
    cout << "Integer Linked List: ";
    intList.display();

    intList.remove(20);
    cout << "After deleting 20: ";
    intList.display();

    LinkedList<string> stringList; // Linked list for strings
    stringList.insert("Hello");
    stringList.insert("World");
    cout << "String Linked List: ";
    stringList.display();

    return 0;
}