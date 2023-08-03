#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void merge(int *v, int left, int mid, int right) {
    int size1 = mid - left + 1, size2 = right - mid;
    int *l = new int[size1], *r = new int[size2];

    for (int i = 0; i < size1; i++)
        l[i] = v[left + i];
    for (int i = 0; i < size2; i++)
        r[i] = v[mid + i + 1];

    int i = 0, j = 0, k = left;

    while (i < size1 && j < size2) {
        if (l[i] < r[j])
            v[k++] = l[i++];
        else
            v[k++] = r[j++];
    }

    while (i < size1)
        v[k++] = l[i++];
    while (j < size2)
        v[k++] = r[j++];
}

void mergesort(int *v, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergesort(v, left, mid);
        mergesort(v, mid + 1, right);
        merge(v, left, mid, right);
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

    mergesort(v, 0, n - 1);
    cout << "Sorted array:" << endl;
    printArray(v, n);

    return 0;
}
