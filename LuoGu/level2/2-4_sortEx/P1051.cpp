#include <iostream>
#include <string>
using namespace std;

int main() {
    int n, avg, eval, cnt, sum = 0;
	char cadre, west;
	int max_bonus = -1, bonus;
	string name, max_name;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> name >> avg >> eval >> cadre >> west >> cnt;
		bonus = 0;
		if (avg > 80 && cnt > 0) 
			bonus += 8000;
		if (avg > 85 && eval > 80) 
			bonus += 4000;
		if (avg > 90) 
			bonus += 2000;
		if (avg > 85 && west == 'Y') 
			bonus += 1000;
		if (eval > 80 && cadre == 'Y') 
			bonus += 850;
		sum += bonus;
		if (bonus > max_bonus) {
			max_bonus = bonus;
			max_name = name;
		}
	}
	cout << max_name << endl << max_bonus << endl << sum << endl;
    return 0;
}

