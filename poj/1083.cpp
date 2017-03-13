/*
* description:
* move a table from room s to room t.
* the cost time of every moving is 10min.
* several room tuples: (s0, t0), (s1, t1) ...
* if (si, ti) ^ (sj, tj) = NULL
* then it can be moved parallelly.
* otherwise can't.
* input:
* T: number of test cases
* for every T:
* N: tables (N <- [1, 200])
* (s0, t0) .... (sn-1, tn-1) 
* (si or ti <- [1, 400], all of them appear only once)
* output:
* for every T: cost minutes
* algorithm:
* ...nothing
*/
#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
	int cases;
	cin >> cases;
	for (int i = 0; i < cases; i++) {
		int n, s, t, max = 0;
		int room[401] = {0};
		int j, k;
		cin >> n;
		for (j = 0; j < n; j++) {
			cin >> s >> t;
			if (s < t) {
				s -= (s % 2 == 0);
				t += (t % 2 == 1);
			} else {
				s += (s % 2 == 1);
				t -= (t % 2 == 0);
				int sp = s;
				s = t;
				t = sp;
			}
			for (k = s; k <= t; k++) {
				room[k]++;
			}
		}
		for (j = 1; j <= 400; j++) {
			if (room[j] > max) {
				max = room[j];
			}
		}
		cout << (max * 10) << endl;
	}
	return 0;
}

