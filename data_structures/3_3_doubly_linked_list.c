#include <stdio.h>
#include <stdlib.h>

typedef struct DNode {
    int data;
    struct DNode* prev;
    struct DNode* next;
} DNode;

DNode* createDNode(int data) {
    DNode* node = (DNode*)malloc(sizeof(DNode));
    node->data = data;
    node->prev = node->next = NULL;
    return node;
}

void printDList(DNode* head) {
    while (head) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

DNode* swapAdjacentD(DNode* head, int pos) {
    if (!head || !head->next) return head;

    DNode* p = head;
    for (int i = 0; i < pos && p->next; i++)
        p = p->next;

    DNode* q = p->next;
    if (!q) return head;

    DNode* before = p->prev;
    DNode* after = q->next;

    if (before) before->next = q;
    q->prev = before;

    q->next = p;
    p->prev = q;

    p->next = after;
    if (after) after->prev = p;

    if (pos == 0) head = q;
    return head;
}

int main() {
    DNode* head = createDNode(1);
    DNode* n2 = createDNode(2);
    DNode* n3 = createDNode(3);
    DNode* n4 = createDNode(4);

    head->next = n2; n2->prev = head;
    n2->next = n3; n3->prev = n2;
    n3->next = n4; n4->prev = n3;

    printf("Before swapping:\n");
    printDList(head);

    head = swapAdjacentD(head, 1);
    printf("After swapping position 1 and 2:\n");
    printDList(head);

    return 0;
}
