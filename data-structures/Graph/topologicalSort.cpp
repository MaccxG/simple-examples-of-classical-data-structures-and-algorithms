// A Graph class that has a method to implement topological sort, a method to count the
// the number of cycles within the graph and a method a method that allows transform
// the graph to a DAG.   

#include <iostream>
#include <algorithm>

using namespace std;

template <class H>
class Graph {
private:
    int length, n;
    H *v;
    bool **adjMatrix;
    const int white = 0, grey = 1, black = 2;
    int *colors;
    H *topSort;
    int topSortIndex;

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

    void resetColors() {
        for (int i = 0; i < n; i++)
            colors[i] = white;
    }

	int countCycles(int i) {
		colors[i] = grey;
        
		int cycles = 0;
		for (int j = 0; j < n; j++) {
			if (adjMatrix[i][j]) {
				if (colors[j] == grey)
                    cycles++;
				else if (colors[j] == white)
                    cycles += countCycles(j);
			}
		}
		colors[i] = black;
			
		return cycles;
	}

	int _getCycles() {
        resetColors();

		int cycles = 0;
		for (int i = 0; i < n; i++)
			if (colors[i] == white)
                cycles += countCycles(i);

		return cycles;
	}

    void deleteCycles(int i) {
		colors[i] = grey;

		for (int j = 0; j < n; j++) {
			if (adjMatrix[i][j]) {
				if (colors[j] == grey)
                    _removeEdge(v[i], v[j]);
				else if (colors[j] == white)
                    deleteCycles(j);
			}
		}

		colors[i] = black;
    }

    void _transformIntoDAG() {
        if (isEmpty())
            return;

        resetColors();

		for (int i = 0; i < n; i++)
			if (colors[i] == white)
                deleteCycles(i);    
    }

	void topSortDFSvisit(int i) {
		colors[i] = grey;

		for (int j = 0; j < n; j++)
			if (adjMatrix[i][j] && colors[j] == white)
                topSortDFSvisit(j);
        	
		colors[i] = black;
        topSort[topSortIndex++] = v[i];
	}

	void topSortDFS() {
        if (isEmpty())
            return;
        
        resetColors();

		for (int i = 0; i < n; i++)
            if (colors[i] == white)
                topSortDFSvisit(i);
	}

    void _topologicalSort() {
        if (_getCycles() > 0) {
            cout << "\n<Impossible to do topological sort>\n";
            return;
        }

        topSortDFS();
        for (int i = n - 1; i >= 0; i--)
            cout<< topSort[i] <<" ";
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

		colors = new int[length];

        topSort = new int[length];
        topSortIndex = 0;
    }

    void addNode(H key) {   _addNode(key);  }
    void addEdge(H x, H y) {    _addEdge(x, y); }
    void removeNode(H key) {  _removeNode(key); }
    void removeEdge(H x, H y) { _removeEdge(x, y);  }
    int getCycles() {   return _getCycles();    }
    void transformIntoDAG() {   _transformIntoDAG(); }
    void topologicalSort() {    _topologicalSort(); }
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
    g.addEdge(7, 24);
    g.addEdge(18, 24);
    g.addEdge(18, 30);
    g.addEdge(24, 5);
    g.addEdge(24, 7);
    g.addEdge(24, 30);
    g.addEdge(30, 18);

    g.print();
    cout << endl << endl;

    cout << "Topological sort test:" << endl;
    g.topologicalSort();
    cout << endl;

    cout << "Number of cycles: ";
    cout << g.getCycles() << endl << endl;

    cout << "Deleting cycles test:" << endl;
    g.transformIntoDAG();
    g.print();
    cout << endl << endl;

    cout << "Number of cycles: ";
    cout << g.getCycles() << endl << endl;

    cout << "Topological sort test:" << endl;
    g.topologicalSort();
    cout << endl;    

    return 0;
}