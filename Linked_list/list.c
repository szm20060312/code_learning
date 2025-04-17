#include <stdio.h>
#include <stdlib.h>
#include "list.h"

Node * find_tail(Node * someNode){
    Node * current = someNode;
    while(current != NULL && current -> next != NULL)
        current = current->next;
    return current;
}

DNode * find_head_DLL(DNode * someNode){
    DNode * current = someNode;
    while(current != NULL && current -> prev != NULL)
        current = current->prev;
    return current;
}

Node * new_node_with_data(int data){
    Node * newNode = (Node * ) malloc( sizeof(Node)); 
    if (newNode != NULL) {/* Maybe malloc() is unsuccesful */
        newNode->data = data; 
        newNode->next = NULL;
        // for a DNode, add:  newNode->prev = NULL;
    }
    return newNode; 
}

Node * append_data(Node * head, int data){
    Node * tail = find_tail(head);
    Node * newNode = new_node_with_data(data);
    if(head == NULL)
        return newNode; // newNode is the head
    else {
        tail->next = newNode; 
        // for DLL, add:   newNode->prev = tail;
        return head;
    }
}

Node * prepend_data(Node * head, int data){
    Node * newNode = new_node_with_data(data);
    if(head == NULL)
        return newNode; // newNode is the head
    else {
        newNode -> next = head; 
        // for DLL, add:   newNode->prev = head;
        return newNode; // the head of the list is not changed
    }
}

Node * insert_data_after(Node * someNode, int data){
    if (someNode == NULL) 
        return NULL; // do nothing if someNode is not found
    Node * newNode = new_node_with_data(data);
    newNode->next = someNode->next;
    someNode -> next = newNode;  
    return newNode; 
}

Node * find_data(Node * head, int data){
    Node * current = head; 
    while(current != NULL){ 
        if(current -> data == data)
            return current;
        current = current->next;
    } 
    return NULL; 
}

Node * delete_node(Node * head, Node * someNode){
    Node * nd = head;
    if (head == NULL || someNode == NULL) // meaningless case
        return NULL;
    // deleting the first node in the list
    if(head == someNode){
        nd = someNode->next;
        // for DLL, add: nd->prev = NULL;
        free(someNode);
        return nd;
    }
    // find the previous node of someNode
    while(nd!=NULL && nd->next != someNode)
        nd = nd->next;
    if(nd!=NULL){ // someNode is found in the list
        nd->next = someNode->next; 
        // for DLL, add: someNode->next->prev = nd;
        free(someNode);
    }
    // if someNode is not found in the list, do nothing. 
    return head; // the list still has the same head.  
}

int count(Node * head){
    Node * current = head;
    int count = 0;
    while (current != NULL){
        count++;
        current = current -> next;   
    }
    return count;
}

void print_list(Node * head){
    Node * current = head;
    while (current != NULL){
        printf("%d ", current -> data);
        current = current -> next;   
    }
    puts("");
}

int free_list(Node * head){
    int count = 0;
    Node * current = head;
    Node * nextNd = NULL;
    while(current != NULL){
        nextNd = current -> next;
        free(current);
        current = nextNd;
        count++;
    }
    return count; 
}

Node * clone_list(Node * head){
    Node * current = head;
    Node * newListHead = NULL;
    Node * newListTail = NULL; 
    Node * newNd;
    if(head == NULL)
        return NULL; 
    if( (newNd = new_node_with_data(head->data)) == NULL){
        printf("Creating new node fails\n");
        return NULL;
    }
    newListHead = newListTail = newNd;
    current = head->next;
    while(current != NULL){
        if( (newNd = new_node_with_data(current->data)) == NULL){
            printf("Creating new node fails\n");
            free_list(newListHead);
            return NULL;
        }
        newListTail->next = newNd;
        current = current->next;
        newListTail = newListTail->next;
    }
    return newListHead;
}


void map_on_list(Node * head,  void(*f)(Node *)){
    Node * current = head;
    while(current != NULL) {
        f(current);
        current = current->next;
    }
}

void print_node(Node * nd){
    printf("%d ", nd->data);
}

void print_list_v2(Node * head){
    map_on_list(head, print_node);
    puts("");
}
