#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Print the linked list
void printList(Node* head) {
    while (head) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

// Swap adjacent nodes (singly linked list version)
Node* swapAdjacent(Node* head, int pos) {
    // pos indicates the position to be swapped. For example, pos=1 means swapping the 1st and 2nd nodes.
    if (!head || !head->next) return head;
    if (pos == 0) {
        Node* first = head;
        Node* second = head->next;
        first->next = second->next;
        second->next = first;
        head = second;
        return head;
    }

    Node* prev = head;
    for (int i = 0; i < pos - 1 && prev->next && prev->next->next; i++)
        prev = prev->next;

    Node* p = prev->next;
    Node* q = p->next;
    if (!q) return head;

    p->next = q->next;
    q->next = p;
    prev->next = q;

    return head;
}

int main() {
    Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);

    printf("Before swapping:\n");
    printList(head);

    head = swapAdjacent(head, 1);
    printf("After swapping position 1 and 2:\n");
    printList(head);

    return 0;
}
