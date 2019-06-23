/**
 * Description: cross river 
 * Input : L \n S T M \n pos
 *         L: the length of birdge 
 *         [S, T]: jump interval
 *         M: # stones
 * Output: the minimum number of stones on which the frog must jump
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;

int main() {
    int L, S, T, M;
	cin >> L >> S >> T >> M;
	vector<int> stones(M + 2);
	for (int i = 1; i <= M; ++i) 
		cin >> stones[i];
	stones[0] = 0;
	stones[M + 1] = L;
	M += 2;
	sort(stones.begin(), stones.end());
	int stone_p = 0;
	while (stone_p < M && stones[stone_p] < S) stone_p++;
	vector<int> minsteps(T, M + 1);
	for (int i = S; i <= T; ++i) {
		minsteps[i - 1] = 0;
		if (stone_p < M && stones[stone_p] == i) {
			minsteps[i - 1] = 1;
			stone_p++;
		}
	}
	int step_size = T - S + 1;
	int start_p = 0;
	int stop_p = T - 1;
	int ptr = 0;
	// to accelerate
	vector<int> shadow(T);
	std::copy(minsteps.begin(), minsteps.end(), shadow.begin());
	int counter = 0;
	int min_gap = 2 * T;
	for (int i = T + 1; i < L; ) {
		int min_val = M + 1;
		ptr = start_p;
		for (int j = 0; j < step_size; ++j) {
			min_val = min(min_val, minsteps[ptr]);
			ptr = (ptr + 1) % T;
		}
		stop_p = start_p;
		start_p = (start_p + 1) % T;
		int extra = 0;
		if (stone_p < M && i == stones[stone_p]) {
			stone_p++;
			extra++;
		}
		if (min_val >= M + 1) {
			minsteps[stop_p] = M + 1;
		} else {
			minsteps[stop_p] = min_val + extra;
		}
		// cout << i << " " << min_val << " " << extra << " " << minsteps[stop_p] << endl;
		counter++;
		if (counter == T) {
			if (stones[stone_p] - stones[stone_p - 1] > min_gap && 
			    i - stones[stone_p - 1] > min_gap) {
				bool flag = true;
				for (int x = 0; x < T; ++x) {
					if (shadow[x] != minsteps[x]) {
						flag = false;
						break;
					}
				}
				if (flag) {
					// cout << "Jump from " << i;
					i += T * ((stones[stone_p] - 1 - i) / T) + 1;
					// cout << " to " << i << endl;
				} else {
					++i;
				}
			} else {
				++i;
			}
			counter = 0;
			std::copy(minsteps.begin(), minsteps.end(), shadow.begin());
		} else {
			++i;
		}
	}
	int ans = M + 1;
	for (int i = 0; i < T; ++i) 
		ans = min(ans, minsteps[i]);
	cout << ans << endl;
    return 0;
}

