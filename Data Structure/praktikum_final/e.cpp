#include <iostream>
#include <string>
using namespace std;

struct DListNode {
    int data;
    DListNode *next, *prev;
};

struct Deque {
    DListNode *_head, *_tail;
    unsigned _size;

    DListNode* __createNode(int value) {
        DListNode *newNode = (DListNode*) malloc (sizeof(DListNode));
    
        if (!newNode) return NULL;
        newNode->data = value;
        newNode->next = NULL;
        newNode->prev = NULL;

        return (DListNode*) newNode;
    }

    void init() {
        _head = _tail = NULL;
        _size = 0;
    }

    bool isEmpty() {
        return (_head == NULL && _tail == NULL);
    }

    void pushFront(int value) {
        DListNode *newNode = __createNode(value);
        if (newNode) {
            _size++;
            if (isEmpty()) {
                _head = newNode;
                _tail = newNode;
                return;
            }

            newNode->next = _head;
            _head->prev = newNode;
            _head = newNode;
        }
    }

    void pushBack(int value) {
        DListNode *newNode = __createNode(value);
        if (newNode) {
            _size++;
            if (isEmpty()) {
                _head = newNode;
                _tail = newNode;
                return;
            }

            _tail->next = newNode;
            newNode->prev = _tail;
            _tail = newNode;
        }
    }

    int front() {
        if (!isEmpty())
            return _head->data;
        exit(-1);
    }

    int back() {
        if (!isEmpty())
            return _tail->data;
        exit(-1);
    }

    void popFront() {
        if (!isEmpty()) {
            DListNode *temp = _head;
            if (_head == _tail) {
                _head = NULL;
                _tail = NULL;
                free(temp);
            }
            else {
                _head = _head->next;
                _head->prev = NULL;
                free(temp);
            }
            _size--;  
        }
    }

    void popBack() {
        if (!isEmpty()) {
            DListNode *temp;
            if (_head == _tail) {
                temp = _head;
                _head = NULL;
                _tail = NULL;
                free(temp);
            }
            else {
                temp = _tail;
                _tail = _tail->prev;
                _tail->next = NULL;
                free(temp);
            }
            _size--;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    Deque qFlip;
    qFlip.init();
    
    int n, tmp;
    string cmd;
    cin >> n;
    
    bool balik = 0;
    while (n--) {
        cin >> cmd;
        if (cmd == "depan") {
            if (qFlip.isEmpty()) {
                cout << "\n";
                continue;
            }
            if (!balik) {
                cout << qFlip.front() << "\n";
                qFlip.popFront();
            } else if (balik) {
                cout << qFlip.back() << "\n";
                qFlip.popBack();
            }
        }
        
        if (cmd == "belakang") {
            if (qFlip.isEmpty()) {
                cout << "\n";
                continue;
            }
            if (!balik) {
                cout << qFlip.back() << "\n";
                qFlip.popBack();
            } else if (balik) {
                cout << qFlip.front() << "\n";
                qFlip.popFront();
            }
        }

        if (cmd == "tambahDepan") {
            cin >> tmp;
            if (!balik)
                qFlip.pushFront(tmp);
            else if (balik)
                qFlip.pushBack(tmp);
        }

        if (cmd == "tambahBelakang") {
            cin >> tmp;
            if (!balik)
                qFlip.pushBack(tmp);
            else if (balik)
                qFlip.pushFront(tmp);
        }

        if (cmd == "balik" && !balik) balik = 1;
        else if(cmd == "balik" && balik) balik = 0;
    }
    return 0;
}