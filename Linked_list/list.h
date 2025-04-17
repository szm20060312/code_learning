#ifndef _LIST_H_
#define _LIST_H_

struct node { // type of a node in a single linked list
    int data;
    struct node * next; 
};

struct dNode{ // type of a node in a single linked list
    int data;
    struct dNode * prev; // address of the previous node
    struct dNode * next; // address of the next node
};

typedef struct node Node;
typedef struct dNode DNode;

Node * find_tail(Node * someNode);
DNode * find_head_DLL(DNode * someNode);
Node * new_node_with_data(int data);
Node * append_data(Node * head, int data);
Node * prepend_data(Node * head, int data);
Node * insert_data_after(Node * someNode, int data);
Node * find_data(Node * head, int data);
Node * delete_node(Node * head, Node * someNode);
int count(Node * head);
void print_list(Node * head);
int free_list(Node * head);
Node * clone_list(Node * head);
void map_on_list(Node * head,  void(*f)(Node *));
void print_node(Node * nd);
void print_list_v2(Node * head);

#endif