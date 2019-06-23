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
	vector<int> stones(M, 0);
	for (int i = 0; i < M; ++i) 
		cin >> stones[i];
	sort(stones.begin(), stones.end());
	int window_size = T;
	vector<bool> access(window_size, false);
	vector<int> minsteps(window_size, 0);
	int begin_p = 0;
	int end_p = T - 1;
	int stone_p = 0;
	for (int i = 1; i < S; ++i) {
		if (stone_p < M && stones[stone_p] == i) {
			stone_p++;
		}
	}
	for (int i = S; i <= T; ++i) {
		access[i - 1] = true;
		if (stone_p < M && stones[stone_p] == i) {
			minsteps[i - 1] = 1;
			stone_p++;
		}
	}
	int step_size = T - S + 1;
	for (int i = T + 1; i < L; ++i) {
		int ptr = begin_p;
		int min_val = M + 1;
		for (int j = 0; j < step_size; ++j) {
			if (access[ptr]) { 
				min_val = min(min_val, minsteps[ptr]);
			}
			ptr = (ptr + 1) % window_size;
		}
		int extra = 0;
		if (stone_p < M && stones[stone_p] == i) {
			extra = 1;
			stone_p++;
		}
		if (min_val == M + 1) {
			end_p = begin_p;
			begin_p = (begin_p + 1) % window_size;
			access[end_p] = false;
		} else {
			end_p = begin_p;
			begin_p = (begin_p + 1) % window_size;
			access[end_p] = true;
			minsteps[end_p] = min_val + extra;
		}
	}
	int ans = M + 1;
	int ptr = begin_p;
	for (int j = 0; j < window_size; ++j) {
		if (access[ptr]) {
			ans = min(ans, minsteps[ptr]);
		}
		ptr = (ptr + 1) % window_size;
	}
	cout << ans << endl;
    return 0;
}

