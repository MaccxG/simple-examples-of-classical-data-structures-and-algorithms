// A dinamic queue.

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
class Queue {
private:
	Node<H> *head, *tail;
	int n;

	bool isEmpty() {
		if (!head) {
			cout << "\n<The queue is empty>\n";
			return true;
		}
		return false;
	}

	void _enqueue(H key) {
		Node<H> *x = new Node<H>(key);
		if (!head)
			head = tail = x;
		else {
			tail->setNext(x);
			tail = x;
		}
		n++;
	}

	H _dequeue() {
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
				cout << " <- ";
			i = i->getNext();
		}
	}

public:
	Queue() {
		head = tail = NULL;
		n = 0;
	}

	void enqueue(H key) {	_enqueue(key);	}
	H dequeue() {	return _dequeue();	}
	int size() {	return n;	}
	void print() { _print(); }
};

int main() {
    Queue<int> q;

    q.print();
    cout << endl;

    cout << "enqueue tests:" << endl << endl;
    q.enqueue(5);
    q.print();
    cout << endl;
    
    q.enqueue(8);
    q.print();
    cout << endl;
    
    q.enqueue(3);
    q.print();
    cout << endl;
    
    q.enqueue(6);
    q.print();
    cout << endl;

    q.enqueue(2);
    q.print();
    cout << endl;

    q.enqueue(7);
    q.print();
    cout << endl << endl;
    
    cout << "dequeue tests:" << endl << endl;
    int n = q.size(), value;
    for (int i = 0; i < n; i++) {
		value = q.dequeue();
		if (value > 0)
			cout << "dequeue: [" << value << "]" << endl;
		q.print();
		cout << endl;
    }

    return 0;
}