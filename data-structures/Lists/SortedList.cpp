// A dynamic sorted list.

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
class SortedList {
private:
    Node<H> *head, *tail;
    int n;

	bool isEmpty() {
		if (!head) {
			cout << "\n<The sorted list is empty>\n";
			return true;
		}
		return false;
	}

    void _insert(H key) {
        Node<H> *prev = NULL, *i = head;
        while(i && key >= i->getKey()) {
            prev = i;
            i = i->getNext();
        }

        Node<H> *x = new Node<H>(key);
        if (!prev)  // case of the minimum
            head = tail = x;
        else    // intermediate case
            prev->setNext(x);
        if (!i) // case of the maximum
            tail = x;
        x->setNext(i);
        n++;
    }

    void _deleteNode(H key) {
		if (isEmpty())
			return;

        Node<H> *prev = NULL, *i = head;
        while(i && key != i->getKey()) {
            prev = i;
            i = i->getNext();
        }

        if (!i) {
            cout << "\n<The node doesn't exist>\n";
            return;
        }

        if (!prev)  // case of the minimum
            head = head->getNext();
        else {
            if (i == tail)  // case of the maximum
                tail = prev;
            prev->setNext(i->getNext());    // intermediate case
        }
        delete i;
        n--;      
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
    SortedList() {
        head = tail = NULL;
        n = 0;
    }

    void insert(H key) {    _insert(key);   }
    void deleteNode(H key) {    _deleteNode(key);   }
    int size() {	return n;	}
    void print() {  _print();   }
};

int main() {
    SortedList<int> l;

    l.print();
    l.deleteNode(5);
    cout << endl;

    cout << "insert tests:" << endl << endl;
    l.insert(5);
    l.print();
    cout << endl;
    
    l.insert(28);
    l.print();
    cout << endl;
    
    l.insert(2);
    l.print();
    cout << endl;
    
    l.insert(11);
    l.print();
    cout << endl;

    l.insert(36);
    l.print();
    cout << endl;

    l.insert(13);
    l.print();
    cout << endl << endl;

    cout << "delete tests:" << endl << endl;
    l.deleteNode(11);
    l.print();
    cout << endl;

    l.deleteNode(2);
    l.print();
    cout << endl;

    l.deleteNode(36);
    l.print();
    cout << endl;

    l.deleteNode(8);
    cout << endl;

    cout << "insert tests:" << endl << endl;
    l.insert(31);
    l.print();
    cout << endl;
    
    l.insert(3);
    l.print();
    cout << endl;
    
    l.insert(24);
    l.print();
    cout << endl << endl;

    return 0;
}