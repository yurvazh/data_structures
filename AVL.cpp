#include<bits/stdc++.h>

using namespace std;

class Node {
public:

    int k, h;
    Node* left = nullptr;
    Node* right = nullptr;
    Node (int a, Node* a123, Node* a246) {
        k = a; h = 1;
        left = a123;
        right = a246;
    }
    void update_height();
    Node* turn_left();
    Node* turn_right();
    Node* balance();
    Node* insert(int key);
    Node* find_key(int key);
    Node* find_min();
    Node* delete_min();
    Node* delete_key(int key);
    void print();
};

void Node::update_height() {
    h = max(left ? left->h : 0, right ? right->h : 0) + 1;
}
Node* Node::turn_left() {
    Node* x = this;
    Node* y = this->right;
    x->right = y->left;
    y->left = x;
    x->update_height();
    y->update_height();
    return y;
}

Node* Node::turn_right() {
    Node* x = this;
    Node* y = this->left;
    x->left = y->right;
    y->right = x;
    x->update_height();
    y->update_height();
    return y;
}

Node* Node::balance() {
    int h_left, h_right;
    if (!left)
        h_left = 0;
    else
        h_left = left->h;
    if (!right)
        h_right = 0;
    else
        h_right = right->h;
    if (abs(h_left - h_right) < 2) {
        this->update_height();
        return this;
    }
    if (h_left + 1 < h_right) {
        Node* y = this->right;
        if ((y->left ? y->left->h : 0) > (y->right ? y->right->h : 0)) {
            this->right = y->turn_right();
        }
        return this->turn_left();
    }
    if (h_left > h_right + 1) {
        Node* y = this->left;
        if ((y->left ? y->left->h : 0) < (y->right ? y->right->h : 0)) {
            this->left = y->turn_left();
        }
        return this->turn_right();
    }
}
Node* Node::insert(int key) {
    if (k == key) {
        return this;
    }
    if (k > key) {
        if (left != nullptr) {
            left = (left->insert(key))->balance();
        } else {
            left = new Node(key, nullptr, nullptr);
        }
    } else {
        if (right != nullptr) {
            right = (right->insert(key))->balance();
        } else {
            right = new Node(key, nullptr, nullptr);
        }
    }
    return this->balance();
}

Node* Node::find_key (int key) {
    if (k == key) {
        return this;
    } else if (k > key) {
        return left->find_key(key);
    } else {
        return right->find_key(key);
    }
}

Node* Node::find_min() {
    if (left == nullptr) {
        return this;
    } else {
        return left->find_min();
    }
}

Node* Node::delete_min() {
    if (left != nullptr) {
        left = left->delete_min();
        return this->balance();
    } else {
        return right;
    }
}

Node* Node::delete_key(int key) {
    if (k == key) {
        Node* now = this;
        if (!right) {
            return left;
        }
        now = now->right;
        while (now->left != nullptr) {
            now = now->left;
        }
        int key1 = now->k;
        right = right->delete_min();
        k = key1;
        return this->balance();
    } else if (k > key) {
        left = left->delete_key(key);
        return this->balance();
    } else {
        right = right->delete_key(key);
        return this->balance();
    }
}

void Node::print() {
    if (left != nullptr)
        cout << k << " " << left->k << " l\n";
    if (right != nullptr)
        cout << k << " " << right->k << " r\n";
    if (left != nullptr)
        left->print();
    if (right != nullptr)
        right->print();
}

int main() {
    cout << "insert - insert a number\n";
    cout << "find_min - find min. element\n";
    cout << "find_key - find element with given key\n";
    cout << "delete_min - delete element with min key\n";
    cout << "delete_key - delete element with given key\n";
    cout << "print - print all tree\n";
    cout << "exit - exit\n";
    string s;
    Node* start = nullptr;
    while (true) {
        cin >> s;
        if (s == "exit") {
            cout << "exit.........\n";
            return 0;
        }
        if (s == "insert") {
            cout << "number, please: ";
            int num; cin >> num;
            if (!start) {
                start = new Node(num, nullptr, nullptr);
            } else {
                start = start->insert(num);
            }
            cout << "done" << endl;
        } else if (s == "find_min") {
            Node* x = start->find_min();
            cout << x << " " << x->k << endl;
        } else if (s == "find_key") {
            cout << "number, please: ";
            int num; cin >> num;
            cout << start->find_key(num) << endl;
        } else if (s == "delete_min") {
            start->delete_min();
            cout << "done\n";
        } else if (s == "delete_key") {
            cout << "number, please: ";
            int num; cin >> num;
            start->delete_key(num);
            cout << "done\n";
        } else if (s == "print"){
            start->print();
            cout << "done\n";
        }
    }
}