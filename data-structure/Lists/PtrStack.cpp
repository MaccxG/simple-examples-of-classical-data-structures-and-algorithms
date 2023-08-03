// A dinamic stack.

#include <iostream>

using namespace std;

template <class H>
class Node {
private:
    H key;
    Node<H> *next;

public:
    Node(H key) {
        this->key = key;
        next = NULL;
    }

    void setNext(Node<H> *next) { this->next = next; }

    H getKey() { return key; }
    Node<H> *getNext() { return next; }
};

template <class H>
class Stack {
private:
    Node<H> *head;
	int n;

    bool isEmpty() {
        if (!head) {
            cout << "\n<The stack is empty>\n";
            return true;
        }
        return false;
    }

    void _push(H key) {
        Node<H> *x = new Node<H>(key);
        x->setNext(head);
        head = x;
		n++;
    }

    H _pop() {
        if (isEmpty())
			return -1;

		H x = head->getKey();
        head = head->getNext();
		n--;
		return x;
    }

    void _print() {
        if (isEmpty())
			return;

        Node<H> *i = head;
        while (i) {
            cout << "[" << i->getKey() << "]";
            if(i->getNext())
				cout << " -> ";
            i = i->getNext();
        }
    }

public:
    Stack() {
		head = NULL;
		n = 0;
	}

    void push(H key) { _push(key); }
    H pop() {	return _pop();	}
	int size() {	return n;	}
    void print() { _print(); }
};

int main() {
    Stack<int> s;

    s.print();
    cout << endl;

    cout << "Push tests:" <<endl;
    s.push(5);
    s.print();
    cout << endl;
    
    s.push(8);
    s.print();
    cout << endl;
    
    s.push(3);
    s.print();
    cout << endl;
    
    s.push(6);
    s.print();
    cout << endl;

    s.push(2);
    s.print();
    cout << endl;

    s.push(7);
    s.print();
    cout << endl << endl;

    cout << "Pop tests:" << endl;
    int n = s.size(), value;
    for (int i = 0; i < n; i++) {
		value = s.pop();
		if (value > 0)
			cout << "pop: [" << value << "]" << endl;
		s.print();
		cout << endl;
    }

    return 0;
}