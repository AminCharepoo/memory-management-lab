#include <iostream>
#include <memory>
using namespace std;


struct SmartListNode {
    int id;
    string name;
    unique_ptr<SmartListNode> next;

    SmartListNode(int i, string n, unique_ptr<SmartListNode> nx)
        : id(i), name(n), next(move(nx)) {}
};

class SmartNodeList {
private:
    unique_ptr<SmartListNode> head;
    int count;

public:
    SmartNodeList() : head(nullptr), count(0) {}

    void addNode(int id, string name) {
        head = make_unique<SmartListNode>(id, name, move(head));
        count++;
    }
    
    void removeNode(int id) {
        if (!head) return;
        
        if (head->id == id) {
            head = move(head->next); // no manual delete needed
            count --;
            return;
        }

        SmartListNode* curr = head.get();
        while (curr->next && curr->next->id != id) {
            curr = curr->next.get();
        }

        if (curr->next) {
            curr->next = move(curr->next->next); // no manual delete needed
            count --;
        }
    }

    void display() const {
        SmartListNode* curr = head.get();
        while (curr) {
            cout << "[" << curr->id << ": "
                 << curr->name << "] -> ";
            curr = curr->next.get();
        }
        cout << "null" << endl;
    }

    // No destructor needed! No copy constructor needed!
    // No assignment operator needed
    // unique_ptr handles all cleanup automatically.
    // no risk of memory leaks or double deletes.
    // no risk of double use after free.
};

int main() {
    cout << "=== Smart Pointer Version ===" << endl;
    SmartNodeList list;
    list.addNode(1, "Alice");
    list.addNode(2, "Bob");
    list.addNode(3, "Charlie");
    cout << "Original list: ";
    list.display();
    
    list.removeNode(2);
    cout << "After removing Bob: ";
    list.display();
    

    
    return 0;
}