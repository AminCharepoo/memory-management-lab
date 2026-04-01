#include <iostream>
using namespace std;


struct ListNode {
    int id;
    string name;
    ListNode* next;
};

class NodeList {
private:
    ListNode* head;
    int count;

public:
    NodeList() : head(nullptr), count(0) {}

    void addNode(int id, string name) {
        ListNode* n = new ListNode{id, name, head};
        head = n;
        count++;
    }

    void removeNode(int id) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        while (curr && curr->id != id) {
            prev = curr;
            curr = curr->next;
        }
        if (!curr) return;
        if (prev) prev->next = curr->next;
        else head = curr->next;
        delete curr;
        delete curr;
        count--;
    }

    void display() const {
        ListNode* curr = head;
        while (curr) {
            cout << "[" << curr->id << ": "
                 << curr->name << "] -> ";
            curr = curr->next;
        }
        cout << "null" << endl;
    }

    // TODO: Implement destructor, copy constructor, operator=
    // (Part A deliverable)

    ~NodeList() {
        ListNode* curr = head;
        while (curr) {
            ListNode* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }

    NodeList(const NodeList& other) : count(other.count), head(nullptr) {

        ListNode* src = other.head;
        ListNode** dst = &head;
        while (src) {
            *dst = new ListNode{src->id, src->name, nullptr};
            src = src->next;
            dst = &((*dst)->next);
        }
    }

    NodeList& operator=(const NodeList& other) {
        if (this != &other) {
            NodeList temp(other);
            swap(head, temp.head);
            swap(count, temp.count);
        }
        return *this;

    }

};

int main() {
    NodeList list;
    list.addNode(1, "Alice");
    list.addNode(2, "Bob");
    list.addNode(3, "Charlie");
    list.display();

    list.removeNode(2);
    list.display();

    NodeList copy(list); // Copy constructor
    copy.display();

    NodeList assigned;
    assigned = list; // Copy assignment operator
    assigned.display();

    return 0;
}