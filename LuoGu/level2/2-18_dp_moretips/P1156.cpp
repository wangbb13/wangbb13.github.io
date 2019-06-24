/**
 * Description: Spam trap 
 * Input : the depth of a well D; # of spams G; G pairs: (t, h, f)
 * Output: the earliest time to escape; or the longest survivial time 
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct _spam {
	int t, f, h;
} spam;

bool compare(const spam& a, const spam& b) {
	return a.t < b.t;
}

int main() {
    int D, G;
	cin >> D >> G;
	vector<spam> kamen(G);
	for (int i = 0; i < G; ++i) 
		cin >> kamen[i].t >> kamen[i].f >> kamen[i].h;
	sort(kamen.begin(), kamen.end(), compare);
	vector<int> *cur = new vector<int>(101, -1);
	vector<int> *nxt = new vector<int>(101, -1);
	(*cur)[0] = 10;
	int time = 0;
	bool flag = false;
	int earliest = 0;
	int longest = 10;
	int cumu = 10;
	for (int i = 0; i < G; ++i) {
		if (kamen[i].t - time <= longest) {
			longest = longest + kamen[i].f - (kamen[i].t - time);
			cumu += kamen[i].f;
		} else {
			break;
		}
		std::fill((*nxt).begin(), (*nxt).end(), -1);
		for (int d = 0; d <= D; ++d) {
			if ((*cur)[d] >= 0) {
				if (kamen[i].t - time <= (*cur)[d]) {
					// 1. eat
					(*nxt)[d] = max((*cur)[d] + kamen[i].f - (kamen[i].t - time), (*nxt)[d]);
					// 2. use 
					int depth = d + kamen[i].h;
					if (depth >= D) {
						earliest = kamen[i].t;
						flag = true;
						break;
					}
					(*nxt)[depth] = max((*cur)[d] - (kamen[i].t - time), (*nxt)[depth]);
				}
			}
		}
		if (flag) break;
		time = kamen[i].t;
		vector<int>* temp = cur;
		cur = nxt;
		nxt = temp;
	}
	if (flag) cout << earliest << endl;
	else cout << cumu << endl;
    return 0;
}

