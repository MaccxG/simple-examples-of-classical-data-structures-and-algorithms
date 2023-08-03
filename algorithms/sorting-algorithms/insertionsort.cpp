#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void insertionsort(int *v, int n) {
    for (int i = 1; i < n; i++) {
        int j = i;
        while (j > 0 && v[j - 1] > v[j]) {
            swap(v[j - 1], v[j]);
            j--;
        }
    }
}

void initArray(int *v, int n) {
    for (int i = 0; i < n; i++)
        v[i] = rand() % 99 + 1;
}

void printArray(int *v, int n) {
    for (int i = 0; i < n; i++)
        cout << v[i] << " ";
}

int main() {
    srand(time(NULL));

    const int n = 10;
    int v[n];

    cout << "Init array:" << endl;
    initArray(v, n);
    printArray(v, n);
    cout << endl;

    insertionsort(v, n);
    cout << "Sorted array:" << endl;
    printArray(v, n);

    return 0;
}