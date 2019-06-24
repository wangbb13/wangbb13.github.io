/**
 * Description: Spam trap 
 * Input : the depth of a well D; # of spams G; G pairs: (t, h, f)
 * Output: the earliest time to escape; or the longest survivial time 
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef struct _spam {
	int t, f, h;
} spam;

typedef struct _hf {
	int h, f;
	_hf(int a, int b) : h(a), f(b) {}
} hf;

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
	int time = 0;
	int longest = 10;
	int earliest = 0;
	int cumu = 10;
	queue<hf> *cur = new queue<hf>();
	queue<hf> *nxt = new queue<hf>();
	queue<hf> *temp;
	cur->push({0, 10});
	bool flag1 = false;
	for (int i = 0; i < G; ++i) {
		if (kamen[i].t - time <= longest) {
			longest = longest + kamen[i].f - (kamen[i].t - time);
			cumu += kamen[i].f;
		} else {
			break;
		}
		while (!cur->empty()) {
			hf get = cur->front();
			if (get.f >= kamen[i].t - time) {
				nxt->push({get.h, get.f + kamen[i].f - (kamen[i].t - time)});
				if (get.h + kamen[i].h >= D) {
					earliest = kamen[i].t;
					flag1 = true;
					break;
				}
				nxt->push({get.h + kamen[i].h, get.f - (kamen[i].t - time)});
			}
			cur->pop();
		}
		if (flag1) break;
		time = kamen[i].t;
		temp = cur;
		cur = nxt;
		nxt = temp;
	}
	if (flag1) cout << earliest << endl;
	else cout << cumu << endl;
    return 0;
}

