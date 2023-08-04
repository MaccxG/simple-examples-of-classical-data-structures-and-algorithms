// A dynamic BST with several classical methods implemented.

#include <iostream>

using namespace std;

template <class H>
class Node {
private:
	H key;
	Node<H> *father, *left, *right;

public:
	Node(H key) {
		this->key = key;
		father = left = right = NULL;
	}

	void setKey(H key) { this->key = key; }
	void setFather(Node<H> *father) { this->father = father; }
	void setLeft(Node<H> *left) { this->left = left; }
	void setRight(Node<H> *right) { this->right = right; }

	H getKey() { return key; }
	Node<H> *getFather() { return father; }
	Node<H> *getLeft() { return left; }
	Node<H> *getRight() { return right; }
};

template <class H>
class BST {
private:
	Node<H> *root;

	bool isEmpty() {
		if (!root) {
			cout << "\n<The BST is empty>\n";
			return true;
		}
		return false;
	}

	void _insert(H key) {
		Node<H> *i = root, *prev = NULL;

		while (i) {
			prev = i;
			if (key <= i->getKey())
				i = i->getLeft();
			else
				i = i->getRight();
		}

		Node<H> *x = new Node<H>(key);

		if (!prev)
			root = x;
		else if (key <= prev->getKey())
			prev->setLeft(x);
		else
			prev->setRight(x);

		x->setFather(prev);
	}

	Node<H> *search(H key, Node<H> *i) {
		while (i && key != i->getKey()) {
			if (key <= i->getKey())
				i = i->getLeft();
			else
				i = i->getRight();
		}
		return i;
	}

	Node<H> *_min(Node<H> *i) {
		if (!i)
			i = new Node<H>(-1); // empty node
		else
			while (i->getLeft())
				i = i->getLeft();

		return i;
	}

	Node<H> *_max(Node<H> *i) {
		if (!i)
			i = new Node<H>(-1); // empty node
		else
			while (i->getRight())
				i = i->getRight();

		return i;
	}

	void _deleteNode(Node<H> *x) {
		if (!x)
			return;

		if (x->getLeft() && x->getRight()) {
			Node<H> *succX = _min(x->getRight());
			x->setKey(succX->getKey());
			x = succX;
		}

		// z is the parent of node x, y is the son of node x
		Node<H> *z = x->getFather(), *y = x->getLeft();
		if (!y)
			y = x->getRight();
		if (!z)
			root = y;
		else {
			if (x == z->getLeft())
				z->setLeft(y);
			else if (x == z->getRight())
				z->setRight(y);
		}
		if (y)
			y->setFather(z);
	}

	H _predecessor(Node<H> *x) {
		if (!x)
			return -1;

		if (x->getLeft())
			return _max(x->getLeft())->getKey();

		Node<H> *pred = x->getFather();
		while (pred && x->getKey() < pred->getKey())
			pred = pred->getFather();

		if (!pred)
			return -1;
		return pred->getKey();
	}

	H _successor(Node<H> *x) {
		if (!x)
			return -1;

		if (x->getRight())
			return _min(x->getRight())->getKey();

		Node<H> *succ = x->getFather();
		while (succ && x->getKey() > succ->getKey())
			succ = succ->getFather();

		if (!succ)
			return -1;
		return succ->getKey();
	}

	int _height(Node<H> *i) {
		if (!i)
			return 0;

		int leftHeight = _height(i->getLeft());
		int rightHeight = _height(i->getRight());
		if (leftHeight > rightHeight)
			return leftHeight + 1;
		else
			return rightHeight + 1;
	}

	int _nodeDepth(Node<H> *i) {
		if (!i)
			return -1;

		int depth = 0;
		while (i->getFather()) {
			depth++;
			i = i->getFather();
		}
		return depth;
	}

	int _leafsNumber(Node<H> *i) {
		if (!i)
			return 0;
		if (!i->getLeft() && !i->getRight())
			return 1;
		return _leafsNumber(i->getLeft()) + _leafsNumber(i->getRight());
	}

	void _preorder(Node<H> *i) {
		if (isEmpty())
			return;

		if (i) {
			cout << i->getKey() << " ";
			_preorder(i->getLeft());
			_preorder(i->getRight());
		}
	}

	void _postorder(Node<H> *i) {
		if (isEmpty())
			return;

		if (i) {
			_postorder(i->getLeft());
			_postorder(i->getRight());
			cout << i->getKey() << " ";
		}
	}

	void _inorder(Node<H> *i) {
		if (isEmpty())
			return;

		if (i) {
			_inorder(i->getLeft());
			cout << i->getKey() << " ";
			_inorder(i->getRight());
		}
	}

public:
	BST() {
		root = NULL;
	}

	void insert(H key) { _insert(key); }
	void deleteNode(H key) { _deleteNode(search(key, root)); }
	H min() { return _min(root)->getKey(); }
	H max() { return _max(root)->getKey(); }
	H predecessor(H key) { return _predecessor(search(key, root)); }
	H successor(H key) { return _successor(search(key, root)); }
	int height() { return _height(root); }
	int nodeDepth(H key) { return _nodeDepth(search(key, root)); }
	int leafsNumber() { return _leafsNumber(root); }
	void preorder() { _preorder(root); }
	void postorder() { _postorder(root); }
	void inorder() { _inorder(root); }
};

int main() {
	BST<int> t;

    // test for visits when the BST is empty
	t.preorder();
	t.postorder();
	t.inorder();
	cout << endl;

    // test for min and max when the BST is empty
    cout << "Min: " << t.min() << endl;
    cout << "Max: " << t.max() << endl << endl;

    // test for height when the BST is empty
    cout << "BST height = " << t.height() << endl << endl;

    // test insert
	t.insert(8);
	t.insert(5);
	t.insert(3);
	t.insert(6);
	t.insert(10);
	t.insert(13);
	t.insert(2);
	t.insert(11);

    // test for visits
	t.preorder();
	cout << endl;
	t.postorder();
	cout << endl;
	t.inorder();
    cout << endl <<endl;

    // test for min and max
    cout << "Min: " << t.min() << endl;
    cout << "Max: " << t.max() << endl << endl;

    // test for predecessor and successor
    cout << "Predecessor of 2 -> " << t.predecessor(2) << endl;
    cout << "Successor of 2 -> " << t.successor(2) << endl;
    cout << "Predecessor of 3 -> " << t.predecessor(3) << endl;
    cout << "Successor of 3 -> " << t.successor(3) << endl;
    cout << "Predecessor of 5 -> " << t.predecessor(5) << endl;
    cout << "Successor of 5 -> " << t.successor(5) << endl;
    cout << "Predecessor of 8 -> " << t.predecessor(8) << endl;
    cout << "Successor of 8 -> " << t.successor(8) << endl;
    cout << "Predecessor of 13 -> " << t.predecessor(13) << endl;
    cout << "Successor of 13 -> " << t.successor(13) << endl;
    cout << "Predecessor of 15 -> " << t.predecessor(15) << endl;
    cout << "Successor of 15 -> " << t.successor(15) << endl << endl;

    // test for height
    cout << "BST height = " << t.height() << endl << endl;

    // test for depth of a node
    cout << "Depth of 2 -> " << t.nodeDepth(2) << endl;
    cout << "Depth of 3 -> " << t.nodeDepth(3) << endl;
    cout << "Depth of 5 -> " << t.nodeDepth(5) << endl;
    cout << "Depth of 6 -> " << t.nodeDepth(6) << endl;
    cout << "Depth of 8 -> " << t.nodeDepth(8) << endl;
    cout << "Depth of 11 -> " << t.nodeDepth(11) << endl;
    cout << "Depth of 13 -> " << t.nodeDepth(13) << endl << endl;

    // test for number of leafs
    cout << "Number of leafs = " << t.leafsNumber() << endl << endl;

    // test for deleting some nodes
    t.deleteNode(2);
    t.deleteNode(10);
    t.deleteNode(5);
    t.deleteNode(8);
    t.deleteNode(15);

    t.preorder();
    cout << endl;
    t.postorder();
    cout << endl;
    t.inorder();
    cout << endl << endl;

    // test for min and max after deleted some nodes
    cout << "Min: " << t.min() << endl;
    cout << "Max: " << t.max() << endl << endl;

    // test for height after deleted some nodes
    cout << "BST height = " << t.height() << endl << endl;

    // test for depth of a node after deleted some nodes
    cout << "Depth of 2 -> " << t.nodeDepth(2) << endl;
    cout << "Depth of 3 -> " << t.nodeDepth(3) << endl;
    cout << "Depth of 5 -> " << t.nodeDepth(5) << endl;
    cout << "Depth of 6 -> " << t.nodeDepth(6) << endl;
    cout << "Depth of 8 -> " << t.nodeDepth(8) << endl;
    cout << "Depth of 11 -> " << t.nodeDepth(11) << endl;
    cout << "Depth of 13 -> " << t.nodeDepth(13) << endl << endl;

    // test for number of leafs after deleted some nodes
    cout << "Number of leafs = " << t.leafsNumber() << endl;

    // test for deleting all other nodes
    t.deleteNode(6);
    t.deleteNode(11);
    t.deleteNode(13);
    t.deleteNode(3);

    // test visits after deleted all nodes
	t.preorder();
	t.postorder();
	t.inorder();
	cout << endl;

    // test for min and max after deleted all nodes
    cout << "Min: " << t.min() << endl;
    cout << "Max: " << t.max() << endl << endl;

    // test for height after deleted all nodes
    cout << "BST height = " << t.height() << endl << endl;

    // test for number of leafs after deleted all nodes
    cout << "Number of leafs = " << t.leafsNumber() << endl << endl;

	return 0;
}