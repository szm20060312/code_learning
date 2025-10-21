#include <stdio.h>
#include <stdlib.h>

// Define linked list node structure
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Print elements at positions specified by P in L
void print_lots(Node *L, Node *P) {
    Node *Lp = L; // Point to L
    Node *Pp = P; // Point to P
    int index = 1;

    // When both have not finished traversal
    while (Lp != NULL && Pp != NULL) {
        if (index == Pp->data) {
            printf("%d ", Lp->data);
            Pp = Pp->next; // Move to next position to print
        }
        Lp = Lp->next;
        index++;
    }
    printf("\n");
}

// Helper function: create new node
Node* create_node(int data) {
    Node *n = (Node*)malloc(sizeof(Node));
    n->data = data;
    n->next = NULL;
    return n;
}

// Helper function: append node at the end of the linked list
void append(Node **head, int data) {
    Node *new_node = create_node(data);
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    Node *temp = *head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = new_node;
}

// Example test
int main() {
    Node *L = NULL; // Main linked list
    Node *P = NULL; // Position linked list

    // L = [10, 20, 30, 40, 50, 60]
    append(&L, 10);
    append(&L, 20);
    append(&L, 30);
    append(&L, 40);
    append(&L, 50);
    append(&L, 60);

    // P = [1, 3, 4, 6]
    append(&P, 1);
    append(&P, 3);
    append(&P, 4);
    append(&P, 6);

    printf("Elements printed: ");
    print_lots(L, P);

    return 0;
}