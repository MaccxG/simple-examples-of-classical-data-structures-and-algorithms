// A static queue implemented using a circular array.

#include <iostream>

using namespace std;

template <class H>
class Queue {
private:
    int *v;
    int capacity;
    int head, tail;
	int n;

    bool isEmpty() {
        if (head == -1) {
			cout << "\n<The queue is empty>\n";
			return true;
		}
		return false;
    }

    bool isFull() {
		if (n == capacity) {
			cout << "\n<The queue is full>\n";
			return true;
		}
		return false;
    }

    void _enqueue(int key) {
        if (isFull())
			return;

        if (head == -1)
            head = 0;

        tail = (tail + 1) % capacity;
        v[tail] = key;
		n++;
    }

    H _dequeue() {
        if (isEmpty())
			return -1;

        H x = v[head];
		v[head] = -1;

        if (head == tail) {
            head = -1;
            tail = -1;
        }
        else
            head = (head + 1) % capacity;
		
		n--;

        return x;
    }

	void _print() {
		if(isEmpty())
			return;

		for (int i = head; i <= tail; i++)
			cout << "[" << v[i] << "] ";
	}

public:
    Queue(int capacity) {
        this->capacity = capacity;
        v = new int[capacity];
		for (int i = 0; i < capacity; i++)	v[i] = -1;
        head = tail = -1;
		n = 0;
    }

	void enqueue(H key) {	_enqueue(key);	}
	H dequeue() {	return _dequeue();	}
	int size() {	return n;	}
	void print() {	_print();	}
};

int main() {
    Queue<int> q(6);

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
    cout << endl;

    q.enqueue(9);
    cout << endl;

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
