#include<iostream>
#include<queue>
#define ft first
#define sd second
#define mp make_pair
#define pb push_back

using namespace std;

class Node {
public:
    int value;
    Node* next;
    Node (int t, Node* v);
    Node (int t);
};

class list {
public:
    Node* head;
    Node* tail;
    bool empty();
    void push_front(int p);
    void push_back(int p);
    void push_middle(int in, int p);
    void pop_front();
    list();
    void pop_back();
    void pop_middle(int in);
    void pop_value(int v);
    int search_value(int v);
    int operator[](int i);
    void sort();
    friend ostream& operator<<(ostream&, const list&);
};


Node::Node (int t) {
    value = t;
    next = nullptr;
}

Node::Node (int t, Node* v) {
    value = t;
    next = v;
}

bool list::empty() {
    return (head == nullptr);
}

void list::push_front(int p) {
    head = new Node(p, head);
    if (tail == nullptr) {
        tail = head;
    }
}

void list::push_back(int p) {
    Node* newtall = new Node(p);
    tail -> next = newtall;
    tail = newtall;
    if (head == nullptr) {
        head = tail;
    }
}

list::list(){
    head = tail = nullptr;
}
void list::push_middle(int in, int p) {
    if (in == 0) {
        head = new Node(p, head);
        if (tail == nullptr) {
            tail = head;
        }
        return;
    }
    Node* after = head;
    for (int i = 1; i < in; i++) {
        after = after->next;
    }
    after->next = new Node(p, after->next);
}

void list::pop_front(){
    if (head == tail) {
        head = tail = nullptr;
        return;
    }
    Node* m = head -> next;
    swap(head, m);
    delete(m);
};

void list::pop_back() {
    if (head == tail) {
        head = tail = nullptr;
        return;
    }
    Node* after = head;
    while(after->next != tail) {
        after = after->next;
    }
    swap(tail, after);
    tail -> next = nullptr;
    if (after != head) {
        delete (after);
    }
}

void list::pop_middle(int in) {
    if (head == tail) {
        head = tail = nullptr;
        return;
    }
    if (in == 0) {
        head = head -> next;
        return;
    }
    Node* after = head;
    for (int i = 1; i < in; i++) {
        if (after == nullptr) {
            cout << "incorrect index" << endl;
            return;
        }
        after = after->next;
    }
    if (((after == nullptr) || (after->next == nullptr)) || (in < 0)) {
        cout << "incorrect index" << endl;
        return;
    }
    if (after->next == tail) {
        after->next = after->next->next;
        tail = after;
        return;
    }
    after->next = after->next->next;
    return;
}
void list::pop_value(int t) {
    if (head == tail) {
        head = tail = nullptr;
        return;
    }
    if (head->value == t) {
        head = head->next;
        return;
    }
    Node* after = head;
    while ((after->next != nullptr) && (after->next->value != t)){
        after = after->next;
    }
    if ((after->next == tail) && (after->next->value == t)) {
        after->next = after->next->next;
        tail = after;
        return;
    }
    if ((after->next != nullptr) && (after->next->value == t)) {
        after->next = after->next->next;
        return;
    }
    cout << "incorrect value" << endl;
    return;
}

int list::search_value(int t) {
    if (head->value == t) {
        return 0;
    }
    Node* after = head;
    int sc = 1;
    while ((after->next != nullptr) && (after->next->value != t)){
        after = after->next;
        sc++;
    }
    if (after->next->value == t) {
        return sc;
    } else {
        return -1;
    }
}

int list::operator[](int in) {
    Node* after = head;
    for (int i = 0; i < in; i++) {
        if (after == nullptr) {
            cout << "incorrect index" << endl;
            return -2000000000;
        }
        after = after->next;
    }
    if ((in < 0) || (after == nullptr)) {
       cout << "incorrect index" << endl;
       return -2000000000;
    }
    return after->value;
}

void list::sort() {
    deque<Node*> d;
    Node* after = head;
    while (after != nullptr) {
        Node* m = after->next;
        after->next = nullptr;
        d.push_back(after);
        after = m;
    }
    while (d.size() != 1) {
        Node* head1 = d.front();
        Node* now = d.front();
        d.pop_front();
        Node* head2 = d.front();
        d.pop_front();
        if (head1->value > head2->value) {
            swap(head2, head1);
            now = head1;
        }
        while (head2 != nullptr) {
            if ((now->next == nullptr) || (head2->value < now->next->value)) {
                Node* m = head2->next;
                head2->next = now->next;
                now->next = head2;
                now = now->next;
                head2 = m;
            } else {
                now = now->next;
            }
        }
        d.push_back(head1);
    }
    head = d.front();
    tail = d.front();
    while(tail->next != nullptr) {
        tail = tail->next;
    }
}

ostream& operator<<(ostream& out, const list& a) {
    Node* after = a.head;
    while (after != nullptr) {
        out << after->value << " ";
        after = after->next;
    }
    out << endl;
    return out;
}

int main() {
    list a = list();
    cout << "now list is empty\n";
    cout << "1 - empty or not\n";
    cout << "2 - push front\n";
    cout << "3 - push back\n";
    cout << "4 - push middle\n";
    cout << "5 - pop front\n";
    cout << "6 - pop back\n";
    cout << "7 - pop middle\n";
    cout << "8 - pop value\n";
    cout << "9 - get position by value\n";
    cout << "10 - get value by position\n";
    cout << "11 - sort\n";
    cout << "12 - finish\n";
    int num;
    while (cin >> num) {
        if (num == 12) {
            return 0;
        }
        if (num == 1) {
            cout << a.empty() << endl;
        }
        if (num == 2) {
            int y;
            cout << "value: ";
            cin >> y;
            a.push_front(y);
            cout << a;
        }
        if (num == 3) {
            int y;
            cout << "value: ";
            cin >> y;
            if (a.empty())
                a.push_front(y);
            else
                a.push_back(y);
            cout << a;
        }
        if (num == 4) {
            int in, y;
            cout << "index and value: ";
            cin >> in >> y;
            a.push_middle(in, y);
            cout << a;
        }
        if (num == 5) {
            a.pop_front();
            cout << a;
        }
        if (num == 6) {
            a.pop_back();
            cout << a;
        }
        if (num == 7) {
            int in;
            cout << "index: ";
            cin >> in;
            a.pop_middle(in);
            cout << a;
        }
        if (num == 8) {
            int va;
            cout << "value: ";
            cin >> va;
            a.pop_value(va);
            cout << a;
        }
        if (num == 9) {
            int va;
            cout << "value: ";
            cin >> va;
            cout << a.search_value(va) << endl;
        }
        if (num == 10) {
            int pos;
            cout << "index: ";
            cin >> pos;
            if (a[pos] != -2000000000) {
                cout << a[pos] << endl;
            }
        }
        if (num == 11) {
            a.sort();
            cout << a;
        }
    }

}