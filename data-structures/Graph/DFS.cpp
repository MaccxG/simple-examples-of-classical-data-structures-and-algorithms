// A Graph class that has a method that implements the DFS visit.

#include <iostream>
#include <algorithm>

using namespace std;

template <class H>
class Graph {
private:
    int length, n;
    H *v;
    bool **adjMatrix;
    int visitingTimes, *startTimes, *endTimes, *colors;
    const int white = 0, grey = 1, black = 2;

    bool isEmpty() {
        if (n == 0) {
            cout << "\n<The graph is empty>\n";
            return true;
        }
        return false;
    }

    int findIndex(H key) {   // find index using binary search
        int left = 0, right = n - 1, mid;
        while (left <= right) {
            mid = (left + right) / 2;
            if (key == v[mid])
                return mid;
            if (key < v[mid])
                right = mid - 1;
            else
                left = mid + 1;
        }
        return -1;
    }

    void _addNode(H key) {
        if (n == length) {
            cout << "\n<Maximum number of nodes reached>\n";
            return;
        }
        v[n++] = key;
        sort(v, v + n);
    }

    void _addEdge(H x, H y) {
        if (isEmpty())
            return;
        
        int i = findIndex(x), j = findIndex(y);

        if (i == -1 || j == -1) {
            cout << "\n<Impossible to add edge (" << x << " " << y << ")>\n";
            return;
        }

        if (adjMatrix[i][j])
            cout << "\n<The edge (" << x << " " << y << ") already exists>\n";
        else
            adjMatrix[i][j] = true;
    }

    void _removeNode(H key) {
        if (isEmpty())
            return;

        int i = findIndex(key);

        if (i == -1) {
            cout << "\n<The node "<< key << " does not exist>\n";
            return;
        }
        
        // nodes array recompaction
        for (int j = i; j < n; j++)
            v[j] = v[j + 1];

        // edges matrix recompaction
        for (int k = i + 1; k < n; k++) {
            for (int j = 0; j < n; j++) {
                adjMatrix[i][j] = adjMatrix[i + 1][j];
                adjMatrix[j][i] = adjMatrix[j][i + 1];
            }
            adjMatrix[i][i] = false;
            i++;
        }

        v[n--] = -1;
    }

    void _removeEdge(H x, H y) {
        if (isEmpty())
            return;
        
        int i = findIndex(x), j = findIndex(y);

        if (i == -1 || j == -1) {
            cout << "\n<Impossible to remove edge (" << x << " " << y << ")>\n";
            return;
        }

        if (!adjMatrix[i][j])
            cout << "\n<The edge (" << x << " " << y << ") does not exist>\n";
        else
            adjMatrix[i][j] = false;        
    }

	void DFSvisit(int i) {
		startTimes[i] = visitingTimes++;
		colors[i] = grey;

		for (int j = 0; j < n; j++)
			if (adjMatrix[i][j] && colors[j] == white)
                DFSvisit(j);
			
		endTimes[i] = visitingTimes++;
		colors[i] = black;
	}

	void _DFS() {
        if (isEmpty())
            return;
                
		for (int i = 0; i < n; i++)
            colors[i] = white;

		for (int i = 0; i < n; i++)
            if (colors[i] == white)
                DFSvisit(i);
        
        // output DFS
		for (int i = 0; i < n; i++)
            cout << "(" << v[i] << " " << startTimes[i] << " " << endTimes[i] << ") ";
	}

    void _print() {
        if (isEmpty())
            return;
        
        for (int i = 0; i < n; i++) {
            cout << "(" << v[i];
            for (int j = 0; j < n; j++)
                if (adjMatrix[i][j])
                    cout << " " << v[j];
            cout << ") ";
        }
    }

public:
    Graph(int length) {
        this->length = length;
        n = 0;

        v = new H[length];
        for (int i = 0; i < length; i++)
            v[i] = -1;

        adjMatrix = new bool *[length];
        for (int i = 0; i < length; i++)
            adjMatrix[i] = new bool[length];
        for (int i = 0; i < length; i++)
            for (int j = 0; j < length; j++)
                adjMatrix[i][j] = false;

		visitingTimes = 0;
		startTimes = new int[length];
		endTimes = new int[length];
		colors = new int[length];
    }

    void addNode(H key) {   _addNode(key);  }
    void addEdge(H x, H y) {    _addEdge(x, y); }
    void removeNode(H key) {  _removeNode(key); }
    void removeEdge(H x, H y) { _removeEdge(x, y);  }
    void DFS() {    _DFS(); }
    void print() {  _print(); }
};

int main() {
    Graph<int> g(5);

    cout << "Adding nodes test:" << endl;
    g.addNode(18);
    g.addNode(7);
    g.addNode(5);
    g.addNode(30);
    g.addNode(24);

    g.print();
    cout << endl << endl;

    cout << "Adding edges test:" << endl;
    g.addEdge(5, 7);
    g.addEdge(5, 18);
    g.addEdge(5, 30);
    g.addEdge(7, 18);
    g.addEdge(7, 24);
    g.addEdge(18, 24);
    g.addEdge(18, 30);
    g.addEdge(24, 5);
    g.addEdge(24, 7);
    g.addEdge(24, 30);
    g.addEdge(30, 18);

    g.print();
    cout << endl << endl;

    cout << "DFS test:" << endl;
    g.DFS();
    cout << endl;

    return 0;
}