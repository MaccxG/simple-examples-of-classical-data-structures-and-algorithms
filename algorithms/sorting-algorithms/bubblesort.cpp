#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void bubblesort(int *v, int n) {
    for (int i = 1; i < n ; i++)
        for (int j = 0; j < n - 1; j++)
            if (v[i] < v[j])
                swap(v[i], v[j]);
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

    bubblesort(v, n);
    cout << "Sorted array:" << endl;
    printArray(v, n);

    return 0;
}