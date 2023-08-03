#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int partition(int *v, int n) {
    int pivot = v[0], i = -1, j = n;

    do {
        do
            i++;
        while (v[i] < pivot);
        do
            j--;
        while (v[j] > pivot);
        if (i < j)
            swap(v[i], v[j]);
    } while (i < j);

    return j;
}

void quicksort(int *v, int n) {
    if (n <= 1)
        return;
    int center = partition(v, n);
    quicksort(v, center + 1);
    quicksort(v + center + 1, n - (center + 1));
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

    quicksort(v, n);
    cout << "Sorted array:" << endl;
    printArray(v, n);

    return 0;
}