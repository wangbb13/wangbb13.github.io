/**
 * Description: USACO 06 FEB the triangle of numbers
 * Input : n, sum
 * Output: a number sequence ([1, n])
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void get_coeff(vector<int>& coeff, int n) {
	coeff.resize(n);
	vector<int> temp(n, 0);
	temp[0] = 1;
	coeff[0] = 1;
	int curr_i = 1;
	while (curr_i < n) {
		coeff[0] = 1;
		for (int i = 1; i < curr_i; ++i) 
			coeff[i] = temp[i] + temp[i - 1];
		coeff[curr_i] = 1;
		std::copy(coeff.begin(), coeff.end(), temp.begin());
		curr_i++;
	}
}

bool flag = false;
bool find_res = false;
vector<int> ans;
int slns = 0;

void my_swap(vector<int>& nums, int i, int j) {
	int temp = nums[i];
	nums[i] = nums[j];
	nums[j] = temp;
}

void run(vector<int>& nums, vector<int>& coeff, size_t pi, int n) {
	if (flag) 
		return;
	if (pi >= nums.size() - 1) {
		int ss = 0;
		int i, j;
		for (i = 0, j = 0; (j + 2) <= nums.size(); ++i, j += 2) 
			ss += coeff[i] * (nums[j] + nums[j + 1]);
		if (j < nums.size()) 
			ss += coeff[i] * nums[j];
		if (ss == n) {
			find_res = true;
			vector<int> temp(nums.size());
			int l = 0, r = nums.size() - 1;
			for (i = 0; (i + 2) <= nums.size(); i += 2) {
				temp[l] = std::min(nums[i], nums[i + 1]);
				temp[r] = std::max(nums[i], nums[i + 1]);
				l++; r--;
			}
			if (i < nums.size()) 
				temp[l] = nums[i];
			if (slns == 0) {
				std::copy(temp.begin(), temp.end(), ans.begin());
			} else {
				bool bc = false;
				for (i = 0; i < nums.size(); ++i) {
					if (temp[i] > ans[i]) break;
					else if (temp[i] < ans[i]) {
						bc = true;
						break;
					}
				}
				if (bc) 
					std::copy(temp.begin(), temp.end(), ans.begin());
			}
			if (++slns > 10)
				flag = true;
		}
		return; 
	}
	for (size_t i = pi; i < nums.size(); ++i) {
		my_swap(nums, pi, i);
		for (size_t j = i + 1; j < nums.size(); ++j) { 
			my_swap(nums, pi + 1, j);
			run(nums, coeff, pi + 2, n);
			if (flag) 
				return;
			my_swap(nums, pi + 1, j);
		}
		my_swap(nums, pi, i);
	}
}

int main() {
    int n, sum;
	cin >> n >> sum;
	vector<int> coeff;
	get_coeff(coeff, n);
	vector<int> nums(n);
	for (size_t i = 0; i < n; ++i) 
		nums[i] = i + 1;
	ans.resize(n);
	run(nums, coeff, 0, sum);
	if (find_res) {
		for (int i = 0; i < nums.size(); ++i) 
			cout << ans[i] << " ";
		cout << endl;
	}
    return 0;
}

