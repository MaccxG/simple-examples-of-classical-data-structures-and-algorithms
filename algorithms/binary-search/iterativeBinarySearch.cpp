#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <set>

using namespace std;

int binarySearch(int *v, int n, int x) {
    int left = 0, right = n - 1, mid;
    while (left <= right) {
        mid = (left + right) / 2;
        if (x == v[mid])
            return mid;
        if (x < v[mid])
            right = mid - 1;
        else
            left = mid + 1;
    }
    return -1;
}

int main() {
    srand(time(NULL));

    const int n = 10;
    int v[n];

    // unique random integers from 1 to 20
    set<int> uniqueNumbers;
    int rValue;
    for (int i = 0; i < n; i++) {
        do
            rValue = rand() % 20 + 1;
        while (uniqueNumbers.count(rValue) > 0);
        v[i] = rValue;
        uniqueNumbers.insert(rValue);
    }

    cout << "Init sorted array: " << endl;
    sort(v, v + n);
    for (int i = 0; i < n; i++)
        cout << v[i] << " ";
    cout << endl;

    int x = rand() % 20 + 1; // generate element to search
    int position = binarySearch(v, n, x);
    if (position >= 0)
        cout << "Element " << x << " is at index " << position << endl;
    else
        cout << "Element " << x << " is not in the array" << endl;

    return 0;
}
