#include <iostream>
using namespace std;

bool map[10] = {false};

bool legal(int a) {
	while (a) {
		int x = a % 10;
		if (x == 0)
			return false;
		if (map[x]) {
			return false;
		} else {
			map[x] = true;
		}
		a /= 10;
	}
	return true;
}

int main() {
	for (int i = 1; i < 4; ++i) {
		for (int j = 1; j < 10; ++j) {
			for (int k = 1; k < 10; ++k) {
				if (!(i == j || j == k || i == k)) {
					map[i] = map[j] = map[k] = true;
					int x = i * 100 + j * 10 + k;
					int y = x * 2;
					if (legal(y)) {
						int z = x * 3;
						if (legal(z)) {
							cout << x << " " << y << " " << z << endl;
						}
					}
					std::fill(map, map + 10, false);
				}
			}
		}
	}
	return 0;
}
