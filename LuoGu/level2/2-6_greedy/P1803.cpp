/**
 * Description:	segment cover
 * Input : n \n ai bi ...
 * Output: maximum segments
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct _t_seg {
	int x, y;
} t_seg;

bool compare(t_seg a, t_seg b) {
	return ((a.x < b.x) || 
	(a.x == b.x && a.y < b.y));
}

int main() {
    int n;
	cin >> n;
	vector<t_seg> contest(n);
	for (int i = 0; i < n; ++i) {
		cin >> contest[i].x >> contest[i].y;
	}
	sort(contest.begin(), contest.end(), compare);
	vector<bool> select(n, true);
	for (int i = 0; i < n - 1; ++i) {
		int j = i + 1;
		while (j < n && contest[j].x <= contest[i].y) {
			if (contest[j].y <= contest[i].y) {
				select[i] = false;
				break;
			}
			j++;
		}
	}
	if (n == 0) {
		cout << 0 << endl;
		return 0;
	}
	int ans = 0, end = 0, i = 0;
	while (i < n && !select[i]) i++;
	if (i < n) {
		ans = 1;
		end = contest[i].y;
	}
	i++;
	while (i < n) {
		while (i < n) {
			if (select[i]) {
				if (contest[i].x < end) {
					i++;
				} else {
					break;
				}
			} else {
				i++;
			}
		}
		if (i < n) {
			ans++;
			end = contest[i].y;
		}
		i++;
	}
	cout << ans << endl;
    return 0;
}

