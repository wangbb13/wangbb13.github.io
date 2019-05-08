/**
 * Description: water intaking in a queue
 * Input : n \n ti (time for water intaking)
 * Output: find a ``sequence`` to minimum 
 *         ``the total time`` for water intaking
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>		// std::fixed
#include <vector>
#include <algorithm>
#include <iomanip>		// std::setprecision
using namespace std;

typedef struct _water {
	int id, time;
} water;

bool compare(water& a, water& b) {
	return ((a.time < b.time) || 
	((a.time == b.time) && (a.id < b.id)));
}

int main() {
    int n;
	cin >> n;
	vector<water> nums(n);
	for (int i = 0; i < n; ++i) {
		cin >> nums[i].time;
		nums[i].id = i + 1;
	}
	sort(nums.begin(), nums.end(), compare);
	double avg = 0.0;
	for (int i = 0; i < n - 1; ++i) {
		avg += nums[i].time * (n - 1 - i);
		cout << nums[i].id << " ";
	}
	cout << nums[n - 1].id << endl;
	if (n > 0) {
		avg /= n;
	}
	cout << std::fixed;
	cout << std::setprecision(2) << avg << endl;
    return 0;
}

