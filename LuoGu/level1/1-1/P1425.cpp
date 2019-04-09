#include <iostream>
using namespace std;

int main() {
	int a, b, c, d;
	cin >> a >> b >> c >> d;
	cout << (c - a) - (int)(b > d) << " " << (d - b + 60) % 60 << endl;
	return 0;
}
