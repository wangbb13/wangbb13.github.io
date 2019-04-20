#include <iostream>
using namespace std;

typedef struct _score {
	int id, tot;
	int zh, math, en;
} score;

bool compare(score *a, score *b) {
	if (a->tot > b->tot) {
		return true;
	} else if (a->tot == b->tot) {
		if (a->zh > b->zh) {
			return true;
		} else if (a->zh == b->zh) {
			if (a->id < b->id) {
				return true;
			}
		}
	}
	return false;
}

void quick_sort(score *nums, int l, int r) {
	if (l >= r) 
		return;
	int i = l, j = r;
	score key = nums[l];
	while (i < j) {
		while ((i < j) && (!compare(nums + j, &key))) {
			j--;
		}
		if (i < j) {
			nums[i] = nums[j];
			i++;
		}
		while ((i < j) && (compare(nums + i, &key))) {
			i++;
		}
		if (i < j) {
			nums[j] = nums[i];
			j--;
		}
	}
	nums[i] = key;
	quick_sort(nums, l, i - 1);
	quick_sort(nums, i + 1, r);
}

int main() {
    int n;
	cin >> n;
	score *nums = new score[n];
	for (int i = 0; i < n; ++i) {
		cin >> nums[i].zh >> nums[i].math >> nums[i].en;
		nums[i].id = i + 1;
		nums[i].tot = nums[i].zh + nums[i].math + nums[i].en;
	}
	quick_sort(nums, 0, n - 1);
	n = (n > 5) ? 5 : n;
	for (int i = 0; i < n; ++i) {
		cout << nums[i].id << " " << nums[i].tot << endl;
	}
    return 0;
}

