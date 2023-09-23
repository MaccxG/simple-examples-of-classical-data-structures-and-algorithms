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

	Node<H> *_search(H key, Node<H> *i) {
		while (i && key != i->getKey()) {
			if (key <= i->getKey())
				i = i->getLeft();
			else
				i = i->getRight();
		}
		return i;
	}
    
    bool _search(H key) {
        if (_search(key, root))
            return true;
        return false;
    }

	Node<H> *_min(Node<H> *i) {
		if (!i)
            return new Node<H>(-1); // empty node
		
        while (i->getLeft())
			i = i->getLeft();

		return i;
	}

	Node<H> *_max(Node<H> *i) {
		if (!i)
            return new Node<H>(-1); // empty node
		
        while (i->getRight())
            i = i->getRight();

		return i;
	}

	void _deleteNode(H key) {
        Node<H> *x = _search(key, root);
		
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

        delete x;
	}

	H _predecessor(H key) {
        Node<H> *x = _search(key, root);

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

	H _successor(H key) {
        Node<H> *x = _search(key, root);

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

	int _nodeDepth(H key) {
        Node<H> *i = _search(key, root);

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
    bool search(H key) {    return _search(key);    }
	void deleteNode(H key) { _deleteNode(key); }
	H min() { return _min(root)->getKey(); }
	H max() { return _max(root)->getKey(); }
	H predecessor(H key) { return _predecessor(key); }
	H successor(H key) { return _successor(key); }
	int height() { return _height(root); }
	int nodeDepth(H key) { return _nodeDepth(key); }
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
	t.insert(45);
	t.insert(28);
	t.insert(13);
	t.insert(36);
	t.insert(76);
	t.insert(90);
	t.insert(4);
	t.insert(81);
    t.insert(55);
    t.insert(63);

    // test for visits
	t.preorder();
	cout << endl;
	t.postorder();
	cout << endl;
	t.inorder();
    cout << endl <<endl;

    // test search
    cout << "13: " << t.search(13) << endl;
    cout << "81: " << t.search(81) << endl;
    cout << "28: " << t.search(28) << endl;
    cout << "76: " << t.search(76) << endl;
    cout << "5: " << t.search(5) << endl << endl;
    cout << "31: " << t.search(31) << endl << endl;

    // test for min and max
    cout << "Min: " << t.min() << endl;
    cout << "Max: " << t.max() << endl << endl;

    // test for predecessor and successor
    cout << "Predecessor of 4 -> " << t.predecessor(4) << endl;
    cout << "Successor of 4 -> " << t.successor(4) << endl;
    cout << "Predecessor of 13 -> " << t.predecessor(13) << endl;
    cout << "Successor of 13 -> " << t.successor(13) << endl;
    cout << "Predecessor of 28 -> " << t.predecessor(28) << endl;
    cout << "Successor of 28 -> " << t.successor(28) << endl;
    cout << "Predecessor of 45 -> " << t.predecessor(45) << endl;
    cout << "Successor of 45 -> " << t.successor(45) << endl;
    cout << "Predecessor of 63 -> " << t.predecessor(63) << endl;
    cout << "Successor of 63 -> " << t.successor(63) << endl;
    cout << "Predecessor of 90 -> " << t.predecessor(90) << endl;
    cout << "Successor of 90 -> " << t.successor(90) << endl;
    cout << "Predecessor of 5 -> " << t.predecessor(5) << endl;
    cout << "Successor of 5 -> " << t.successor(5) << endl;
    cout << "Predecessor of 31 -> " << t.predecessor(31) << endl;
    cout << "Successor of 31 -> " << t.successor(31) << endl << endl;

    // test for height
    cout << "BST height = " << t.height() << endl << endl;

    // test for depth of a node
    cout << "Depth of 4 = " << t.nodeDepth(4) << endl;
    cout << "Depth of 13 = " << t.nodeDepth(13) << endl;
    cout << "Depth of 28 = " << t.nodeDepth(28) << endl;
    cout << "Depth of 45 = " << t.nodeDepth(45) << endl;
    cout << "Depth of 55 = " << t.nodeDepth(55) << endl;
    cout << "Depth of 90 = " << t.nodeDepth(90) << endl;
    cout << "Depth of 81 = " << t.nodeDepth(81) << endl << endl;

    // test for number of leafs
    cout << "Number of leafs = " << t.leafsNumber() << endl << endl;

    // test for deleting some nodes
    t.deleteNode(4);
    t.deleteNode(90);
    t.deleteNode(28);
    t.deleteNode(45);
    t.deleteNode(76);
    t.deleteNode(63);

    t.preorder();
    cout << endl;
    t.postorder();
    cout << endl;
    t.inorder();
    cout << endl << endl;

    // test search after deleted some nodes
    cout << "4: " << t.search(4) << endl;
    cout << "90: " << t.search(90) << endl;
    cout << "28: " << t.search(28) << endl;
    cout << "45: " << t.search(45) << endl;
    cout << "76: " << t.search(76) << endl;
    cout << "63: " << t.search(63) << endl << endl;

    // test for min and max after deleted some nodes
    cout << "Min: " << t.min() << endl;
    cout << "Max: " << t.max() << endl << endl;

    // test for height after deleted some nodes
    cout << "BST height = " << t.height() << endl << endl;

    // test for depth of a node after deleted some nodes
    cout << "Depth of 4 = " << t.nodeDepth(4) << endl;
    cout << "Depth of 13 = " << t.nodeDepth(13) << endl;
    cout << "Depth of 28 = " << t.nodeDepth(28) << endl;
    cout << "Depth of 45 = " << t.nodeDepth(45) << endl;
    cout << "Depth of 55 = " << t.nodeDepth(55) << endl;
    cout << "Depth of 90 = " << t.nodeDepth(90) << endl;
    cout << "Depth of 81 = " << t.nodeDepth(81) << endl << endl;

    // test for number of leafs after deleted some nodes
    cout << "Number of leafs = " << t.leafsNumber() << endl;

    // test for deleting all other nodes
    t.deleteNode(13);
    t.deleteNode(36);
    t.deleteNode(81);
    t.deleteNode(55);

    // test visits after deleted all nodes
    t.preorder();
    t.postorder();
    t.inorder();
    cout << endl;

    // test search after deleted all nodes
    cout << "13: " << t.search(13) << endl;
    cout << "36: " << t.search(36) << endl;
    cout << "81: " << t.search(81) << endl;
    cout << "55: " << t.search(55) << endl << endl;

    // test for min and max after deleted all nodes
    cout << "Min: " << t.min() << endl;
    cout << "Max: " << t.max() << endl << endl;

    // test for height after deleted all nodes
    cout << "BST height = " << t.height() << endl << endl;

    // test for number of leafs after deleted all nodes
    cout << "Number of leafs = " << t.leafsNumber() << endl << endl;

	return 0;
}