/*Write a program to implement the following list:
An ordinary Doubly Linked List requires space for two address fields to store the
addresses of previous and next nodes. A memory efficient version of Doubly Linked List
can be created using only one space for address field with every node. This memory
efficient Doubly Linked List is called XOR Linked List or Memory Efficient as the list
uses bitwise XOR operation to save space for one address. In the XOR linked list, instead
of storing actual memory addresses, every node stores the XOR of addresses of previous
and next nodes. */

#include<bits/stdc++.h>
#include <iostream>
#include <vector>
#include <cstdint>
using namespace std;
 
struct Node {
    int data;
    struct Node* nxorp;
};
 
struct Node* XOR(struct Node* a,
                 struct Node* b)
{
    return (struct Node*)((uintptr_t)(a)^ (uintptr_t)(b));
}
 
struct Node* insert(struct Node** head,
                    int value, int position)
{
    if (*head == NULL) {
 
        if (position == 1) {
            struct Node* node= new Node();
            node->data = value;
            node->nxorp = XOR(NULL, NULL);
            *head = node;
        }
 
        else {
            cout << "Invalid Position\n";
        }
    }
 
    else {
 
        int Pos = 1;
        struct Node* curr = *head;
        struct Node* prev = NULL;
        struct Node* next
            = XOR(prev, curr->nxorp);
 
        while (next != NULL && Pos < position - 1) {
 
            prev = curr;
            curr = next;
            next = XOR(prev, curr->nxorp);
            Pos++;
        }
        if (Pos == position - 1) {
 
            struct Node* node = new Node();
                
            struct Node* temp = XOR(curr->nxorp, next);

            curr->nxorp = XOR(temp, node);
 
            if (next != NULL) {
                next->nxorp = XOR(node,
                                XOR(next->nxorp, curr));
            }
 
            node->nxorp = XOR(curr, next);
            node->data = value;
        }
        else if (position == 1) {
            struct Node* node = new Node();
 
            curr->nxorp = XOR(node,XOR(NULL, curr->nxorp));
            node->nxorp = XOR(NULL, curr);
            *head = node;
            node->data = value;
        }
        else {
            cout << "Invalid Position\n";
        }
    }
    return *head;
}
void printList(struct Node** head)
{
    struct Node* curr = *head;
    struct Node* prev = NULL;
    struct Node* next;
    
    while (curr != NULL) {
        
       cout << curr->data << " ";
       
        next = XOR(prev, curr->nxorp);
        prev = curr;
        curr = next;
    }
}

Node *deleteend(Node** head)
{
  struct Node *curr = *head;
  struct Node *prev = NULL;
  struct Node *next = XOR(curr->nxorp,prev);
  if(head == NULL)
   return NULL;
   
   while(next!=NULL)
   {
    prev=curr;
    curr=next;
    next=XOR(curr->nxorp,prev);
   }
   if(prev!=NULL)
   prev->nxorp=XOR(prev->nxorp,curr);
    
    free(curr);
    return *head;
}
 
int main()
{
    struct Node* head = NULL;
    insert(&head, 5, 1);
    printList(&head);
    cout<<" \n";
    insert(&head, 6, 1);
    printList(&head);
    cout<<" \n";
    insert(&head, 35, 3);
    printList(&head);
    cout<<" \n";
    insert(&head, 20, 2);
    printList(&head);
    cout<<" \n";
    deleteend(&head);
    printList(&head);
    cout<<" \n";
 
    return 0;
}
