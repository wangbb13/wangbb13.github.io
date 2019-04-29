/**
 * Description: a simple problem 
 * Input : a sentence with six words.
 * Output: number 
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string num_str[] = { "one", "two", "three",
"four", "five", "six", "seven", "eight", "nine", 
"ten", "eleven", "twelve", "thirteen", "fourteen", 
"fifteen", "sixteen", "seventeen", "eighteen", 
"nineteen", "twenty" };
string non_str[] = { "a", "both", "another", "first", "second", "third" };
int map_str[] = { 1, 2, 1, 1, 2, 3 };

typedef long long int lli;

void permu(vector<int>& nums, int start, lli& ans) {
	if (start == nums.size()) {
		lli x = 0;
		for (int i = 0; i < nums.size(); ++i) {
			x = x * 100 + nums[i];
		}
		if (ans == -1) {
			ans = x;
		} else if (x < ans) {
			ans = x;
		}
		return;
	}
	for (int i = start; i < nums.size(); ++i) {
		int temp = nums[i];
		nums[i] = nums[start];
		nums[start] = temp;
		permu(nums, start + 1, ans);
		temp = nums[i];
		nums[i] = nums[start];
		nums[start] = temp;
	}
}

void to_lower(string& str) {
	char ch = 0x20;
	for (int i = 0; i < str.size(); ++i) {
		str[i] |= ch;
	}
}

int main() {
    string str;
	vector<int> nums;
	while (cin >> str) {
		to_lower(str);
		for (size_t i = 0; i < 20; ++i) {
			if (str == num_str[i]) {
				nums.push_back(i + 1);
			}
		}
		for (size_t i = 0; i < 6; ++i) {
			if (str == non_str[i]) {
				nums.push_back(map_str[i]);
			}
		}
	}
	if (nums.size() == 0) {
		cout << 0 << endl;
	} else {
		for (int i = 0; i < nums.size(); ++i) {
			nums[i] = (nums[i] * nums[i]) % 100;
		}
		lli ans = -1;
		permu(nums, 0, ans);
		cout << ans << endl;
	}
    return 0;
}

