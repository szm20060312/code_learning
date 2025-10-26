#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

typedef Node* List;

void InsertMiddle(List &L, int num) {
    if (L == nullptr) return;
    Node* slow = L;
    Node* fast = L;
    
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    Node* newNode = new Node;
    newNode->data = num;
    newNode->next = slow->next;
    slow->next = newNode;
}

void printList(List L) {
    Node* temp = L;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main() {
    List L = nullptr;

    for (int i = 9; i >= 0; --i) {
        Node* newNode = new Node;
        newNode->data = i;
        newNode->next = L;
        L = newNode;
    }

    cout << "Original List: ";
    printList(L);
    InsertMiddle(L, 10);
    cout << "List after inserting 10: ";
    printList(L);

    return 0;
}
