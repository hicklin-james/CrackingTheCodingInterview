#include <iostream>

using namespace std;

void solveTowersOfHanoi(int disks, int src, int dest, int tmp) {
	if (disks == 1) {
		std::cout << src << " -> " << dest << "\n";
	}
	else {
		solveTowersOfHanoi(disks-1, src, tmp, dest);
		std::cout << src << " -> " << dest << "\n";
		solveTowersOfHanoi(disks-1, tmp, dest, src);
	}
}

int main()
{
    int x;
    cout << "Enter number of disks: ";
    cin >> x;
    solveTowersOfHanoi(x, 1, 3, 2);
    return 0;
}