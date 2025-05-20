
#include <iostream>
#include <stdexcept>
using namespace std;

// ---------------------- LinkedList ----------------------
class LinkedList {
private:
    struct Node {
        int data;
        Node* next;
        Node(int val): data(val), next(nullptr) {}
    };
    Node* head;

public:
    LinkedList(): head(nullptr) {}

    ~LinkedList() {
        while (head) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
    }

    void insert_front(int val) {
        Node* node = new Node(val);
        node->next = head;
        head = node;
    }

    void print() const {
        Node* current = head;
        while (current) {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "null\n";
    }
};

// ---------------------- Stack ----------------------
class Stack {
private:
    struct Node {
        int data;
        Node* next;
        Node(int val): data(val), next(nullptr) {}
    };
    Node* top;

public:
    Stack(): top(nullptr) {}

    ~Stack() {
        while (top) {
            Node* tmp = top;
            top = top->next;
            delete tmp;
        }
    }

    void push(int val) {
        Node* node = new Node(val);
        node->next = top;
        top = node;
    }

    void pop() {
        if (top) {
            Node* tmp = top;
            top = top->next;
            delete tmp;
        }
    }

    int peek() const {
        if (top) return top->data;
        throw runtime_error("Stack is empty");
    }

    bool empty() const {
        return top == nullptr;
    }
};

// ---------------------- Queue ----------------------
class Queue {
private:
    struct Node {
        int data;
        Node* next;
        Node(int val): data(val), next(nullptr) {}
    };
    Node* front;
    Node* rear;

public:
    Queue(): front(nullptr), rear(nullptr) {}

    ~Queue() {
        while (front) {
            Node* tmp = front;
            front = front->next;
            delete tmp;
        }
    }

    void enqueue(int val) {
        Node* node = new Node(val);
        if (rear) {
            rear->next = node;
            rear = node;
        } else {
            front = rear = node;
        }
    }

    void dequeue() {
        if (front) {
            Node* tmp = front;
            front = front->next;
            if (!front) rear = nullptr;
            delete tmp;
        }
    }

    int peek() const {
        if (front) return front->data;
        throw runtime_error("Queue is empty");
    }

    bool empty() const {
        return front == nullptr;
    }
};

// ---------------------- Main ----------------------
int main() {
    // LinkedList
    LinkedList list;
    list.insert_front(3);
    list.insert_front(2);
    list.insert_front(1);
    cout << "LinkedList: ";
    list.print();

    // Stack
    Stack stack;
    stack.push(10);
    stack.push(20);
    cout << "Stack top: " << stack.peek() << "\n";
    stack.pop();
    cout << "Stack top after pop: " << stack.peek() << "\n";

    // Queue
    Queue q;
    q.enqueue(100);
    q.enqueue(200);
    cout << "Queue front: " << q.peek() << "\n";
    q.dequeue();
    cout << "Queue front after dequeue: " << q.peek() << "\n";

    return 0;
}
