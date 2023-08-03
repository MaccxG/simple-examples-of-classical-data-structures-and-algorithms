#include <iostream>

using namespace std;

static int movesCounter = 0;

void hanoi(int disk, int rod1, int rod2, int rod3) {
    if (disk == 1) {
        cout << "Move disk " << disk << " from rod " << rod1 << " to rod " << rod3 << endl;
        movesCounter++;
        return;
    }
    hanoi(disk - 1, rod1, rod3, rod2);
    cout << "Move disk " << disk << " from rod " << rod1 << " to rod " << rod3 << endl;
    movesCounter++;
    hanoi(disk - 1, rod2, rod1, rod3);
}

int main() {
    int n = 4;
    cout << "Moves number: " << n << endl << endl;

    hanoi(n, 1, 2, 3);
    cout << "\nGame solved in " << movesCounter << " moves" << endl;

    return 0;
}