// A static stack implemented using a circular array.

#include <iostream>

using namespace std;

template <class H>
class Stack {
private:
    int *v;
    int capacity;
    int head;
	int n;

    bool isEmpty() {
        if (n == 0) {
			cout << "\n<The Stack is empty>\n";
			return true;
		}
		return false;
    }

    bool isFull() {
		if (n == capacity) {
			cout << "\n<The Stack is full>\n";
			return true;
		}
		return false;
    }

    void _push(int key) {
        if (isFull())
            return;

        head = (head + 1) % capacity;
        v[head] = key;
        n++;
    }

    H _pop() {
        if (isEmpty())
            return -1;

        H x = v[head];
        v[head] = -1;

        if (head == 0)
            head = -1;
        else
            head = (head - 1 + capacity) % capacity;
		
		n--;

        return x;
    }

	void _print() {
		if (isEmpty())
			return;

		for (int i = head; i >= 0; i--) {
			cout << "[" << v[i] << "]";
			if (v[i - 1] != -1 && i - 1 >= 0)
				cout << " -> ";
		}
	}

public:
    Stack(int capacity) {
        this->capacity = capacity;
        v = new int[capacity];
		for (int i = 0; i < capacity; i++)	v[i] = -1;
        head = -1;
		n = 0;
    }

	void push(H key) {	_push(key);	}
	H pop() {	return _pop();	}
	int size() {	return n;	}
	void print() {	_print();	}
};

int main() {
    Stack<int> s(6);

    s.print();
    cout << endl;

    cout << "push tests:" << endl << endl;
    s.push(5);
    s.print();
    cout << endl;
    
    s.push(28);
    s.print();
    cout << endl;
    
    s.push(2);
    s.print();
    cout << endl;
    
    s.push(11);
    s.print();
    cout << endl;

    s.push(36);
    s.print();
    cout << endl;

    s.push(13);
    s.print();
    cout << endl;

    s.push(24);
    cout << endl;

    cout << "pop tests:" << endl << endl;
    int value;
	value = s.pop();
	if (value > 0)
		cout << "pop: [" << value << "]" << endl;
    s.print();
    cout << endl;

	value = s.pop();
	if (value > 0)
		cout << "pop: [" << value << "]" << endl;
    s.print();
    cout << endl << endl;

    cout << "push tests:" << endl << endl;
    s.push(24);
    s.print();
    cout << endl;

    s.push(7);
    s.print();
    cout << endl;

    s.push(10);
    cout << endl;

    cout << "pop tests:" << endl << endl;
    int n = s.size();
    for (int i = 0; i < n; i++) {
		value = s.pop();
		if (value > 0)
			cout << "pop: [" << value << "]" << endl;
		s.print();
		cout << endl;
    }

    return 0;
}