#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

template<typename T>
string my_to_string(T n) {
	string ans;
	stringstream ss;
	ss << n;
	ss >> ans;
	return ans;
}

void permuation(vector<int>& nums, size_t s, int a, int b, int c, vector<string>& ans) {
	if (nums.size() == s) {
		int x, y, z;
		x = nums[0] * 100 + nums[1] * 10 + nums[2];
		y = nums[3] * 100 + nums[4] * 10 + nums[5];
		z = nums[6] * 100 + nums[7] * 10 + nums[8];
		if ((x * b == y * a) && (x * c == z * a)) {
			ans.push_back(my_to_string(x) + " " + my_to_string(y) + " " + my_to_string(z));
		}
		return;
	}
	for (size_t i = s; i < nums.size(); ++i) {
		int temp = nums[i];
		nums[i] = nums[s];
		nums[s] = temp;
		permuation(nums, s + 1, a, b, c, ans);
		temp = nums[i];
		nums[i] = nums[s];
		nums[s] = temp;
	}
}

int main() {
	int a, b, c;
	cin >> a >> b >> c;
	vector<int> nums(9);
	vector<string> ans;
	for (int i = 0; i < 9; ++i)
		nums[i] = i + 1;
	permuation(nums, 0, a, b, c, ans);
	if (ans.size() == 0) {
		cout << "No!!!" << endl;
	} else {
		for (size_t i = 0; i < ans.size(); ++i) {
			cout << ans[i] << endl;
		}
	}
	return 0;
}
