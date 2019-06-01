/**
 * Description: totem
 * Input : n 
 * Output: a totem 
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef vector<string> totem;
totem first(2);
vector<totem> mem;

void show(vector<string>& totem) {
	for (size_t i = 0; i < totem.size(); ++i) 
		cout << totem[i] << endl;
}

void next(vector<string>& cur, vector<string>& nxt) {
	size_t height = cur.size();
	size_t width = cur[height - 1].size();
	size_t margin = width / 2;
	string one = "";
	for (size_t i = 0; i < margin; ++i) 
		one += " ";
	for (size_t i = 0; i < height; ++i) 
		nxt.push_back(one + cur[i]);
	margin--;
	for (size_t i = 0; i < height; ++i) {
		string elem = cur[i];
		for (size_t j = 0; j < margin; ++j) 
			elem += " ";
		elem += cur[i];
		nxt.push_back(elem);
		margin--;
	}
}

int main() {
    first[0] = " /\\";
	first[1] = "/__\\";
	mem.push_back(first);
	int n;
	cin >> n;
	for (int i = 1; i < n; ++i) {
		vector<string> temp;
		next(mem[i - 1], temp);
		mem.push_back(temp);
	}
	show(mem[n - 1]);
    return 0;
}

