#include <iostream>

// 定义链表节点结构体
class Node {
public:
    int data;
    Node* next;
    Node(int value) : data(value), next(nullptr) {}
};

// 定义链表类
class LinkedList {
private:
    Node* head;
public:
    // 构造函数，初始化头指针为 nullptr
    LinkedList() : head(nullptr) {}

    // 在链表头部插入节点
    void insertAtHead(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }

    // 在链表尾部插入节点
    void insertAtTail(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
            return;
        }
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }

    // 打印链表
    void printList() {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    // 查找节点
    Node* find(int value) {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    // 删除节点
    void remove(int value) {
        if (head == nullptr) {
            return;
        }
        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        Node* current = head;
        while (current->next != nullptr && current->next->data != value) {
            current = current->next;
        }
        if (current->next != nullptr) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
    }

    // 析构函数，释放链表内存
    ~LinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    LinkedList list;

    // 在链表头部插入节点
    list.insertAtHead(3);
    list.insertAtHead(2);
    list.insertAtHead(1);

    // 打印链表
    std::cout << "插入头部后的链表: ";
    list.printList();

    // 在链表尾部插入节点
    list.insertAtTail(4);
    list.insertAtTail(5);

    // 打印链表
    std::cout << "插入尾部后的链表: ";
    list.printList();

    // 查找节点
    Node* found = list.find(3);
    if (found != nullptr) {
        std::cout << "找到节点: " << found->data << std::endl;
    } else {
        std::cout << "未找到节点" << std::endl;
    }

    // 删除节点
    list.remove(3);
    std::cout << "删除节点 3 后的链表: ";
    list.printList();

    return 0;
}    