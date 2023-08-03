#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void selectionsort(int *v, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++)
            if (v[j] < v[min])
                min = j;
        swap(v[i], v[min]);
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

    selectionsort(v, n);
    cout << "Sorted array:" << endl;
    printArray(v, n);

    return 0;
}