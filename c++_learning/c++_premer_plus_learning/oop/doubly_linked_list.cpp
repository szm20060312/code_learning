
#include <iostream>
using namespace std;

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int val): data(val), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;

public:
    // 默认构造函数
    DoublyLinkedList(): head(nullptr), tail(nullptr) {}

    // 析构函数
    ~DoublyLinkedList() {
        clear();
    }

    // 拷贝构造函数（深拷贝）
    DoublyLinkedList(const DoublyLinkedList& other): head(nullptr), tail(nullptr) {
        Node* current = other.head;
        while (current) {
            insert_back(current->data);
            current = current->next;
        }
    }

    // 移动构造函数
    DoublyLinkedList(DoublyLinkedList&& other) noexcept
        : head(other.head), tail(other.tail) {
        other.head = nullptr;
        other.tail = nullptr;
    }

    // 插入值：在前端
    void insert_front(int val) {
        Node* node = new Node(val);
        node->next = head;
        if (head) head->prev = node;
        else tail = node; // 如果为空，则新节点也是尾
        head = node;
    }

    // 插入值：在尾端
    void insert_back(int val) {
        Node* node = new Node(val);
        node->prev = tail;
        if (tail) tail->next = node;
        else head = node; // 如果为空，则新节点也是头
        tail = node;
    }

    // 插入值：在某个值之前
    void insert_before(int target, int val) {
        Node* current = head;
        while (current && current->data != target) {
            current = current->next;
        }
        if (!current) return; // 没找到

        Node* node = new Node(val);
        node->next = current;
        node->prev = current->prev;
        if (current->prev) current->prev->next = node;
        else head = node;
        current->prev = node;
    }

    // 删除一个节点（第一个匹配值）
    void delete_value(int val) {
        Node* current = head;
        while (current && current->data != val) {
            current = current->next;
        }
        if (!current) return;

        if (current->prev) current->prev->next = current->next;
        else head = current->next;

        if (current->next) current->next->prev = current->prev;
        else tail = current->prev;

        delete current;
    }

    // 查找值
    bool find(int val) const {
        Node* current = head;
        while (current) {
            if (current->data == val) return true;
            current = current->next;
        }
        return false;
    }

    // 打印链表
    void print() const {
        Node* current = head;
        while (current) {
            cout << current->data << " <-> ";
            current = current->next;
        }
        cout << "null\n";
    }

    // 清空链表
    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }
};

// 测试主函数
int main() {
    DoublyLinkedList dll;
    dll.insert_back(1);
    dll.insert_back(3);
    dll.insert_front(0);
    dll.insert_before(3, 2);
    dll.print();  // 0 <-> 1 <-> 2 <-> 3 <-> null

    cout << "Find 2: " << (dll.find(2) ? "Yes" : "No") << endl;
    dll.delete_value(2);
    dll.print();  // 0 <-> 1 <-> 3 <-> null

    // 拷贝构造
    DoublyLinkedList copy = dll;
    copy.insert_back(4);
    cout << "Original list: ";
    dll.print();
    cout << "Copied list: ";
    copy.print();

    // 移动构造
    DoublyLinkedList moved = std::move(copy);
    cout << "Moved list: ";
    moved.print();
    cout << "Copied list after move: ";
    copy.print();

    return 0;
}
