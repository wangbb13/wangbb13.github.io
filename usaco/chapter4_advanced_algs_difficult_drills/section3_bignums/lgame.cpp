/*
ID: wangbb21
LANG: C++11
TASK: lgame
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

const int L = 26;
int values[L] = { 2, 5, 4, 4, 1, 6, 5, 5, 1, 7, 6, 3, 5, 2, 3, 5, 7, 2, 1, 2, 4, 6, 6, 7, 5, 7 };

typedef struct _node {
	struct _node* next[L];
	bool leaf;
	_node() {
		for (int i = 0; i < L; ++i) next[i] = nullptr;
		leaf = false;
	}
} node;

typedef struct _lword {
	string word;
	size_t split;
} lword;

node *root = new node;
int max_value = 0;
int max_index = 0;
int upp_value = 0;

void build(string word) {
	node *ptr = root;
	size_t i; int j;
	for (i = 0; i < word.size(); ++i) {
		j = (int)(word[i] - 'a');
		if (nullptr == ptr->next[j]) 
			ptr->next[j] = new node;
		ptr = ptr->next[j];
	}
	ptr->leaf = true;
}

bool search(string word) {	// true: in dict; false: not in dict
	if (word.size() == 0) return false;
	bool ans = true;
	node *ptr = root;
	for (size_t i = 0; i < word.size(); ++i) {
		int j = (int)(word[i] - 'a');
		if (nullptr == ptr->next[j]) {
			ans = false;
			break;
		}
		ptr = ptr->next[j];
	}
	return (ans && ptr->leaf);
}

bool cmp_str(const string& stra, const string& strb) {	// a > b ? 
	size_t up = min(stra.size(), strb.size());
	size_t i = 0;
	while (i < up) {
		if (stra[i] > strb[i]) return true;
		else if (stra[i] < strb[i]) return false;
		i++;
	}
	return (stra.size() > strb.size());
}

string num2str(vector<int>& nums, int l, int r) {	// [l, r)
	string ans = "";
	for (int i = l; i < r; ++i) 
		ans += (char)('a' + nums[i]);
	return ans;
}

int score(vector<int>& nums, int l, int r) {	// [l, r)
	int ans = 0;
	for (int i = l; i < r; ++i) 
		ans += values[nums[i]];
	return ans;
}

bool haslw(string str, int sp, vector<lword>& ans) {
	bool rtn = false;
	for (size_t i = 0; i < ans.size(); ++i) {
		if (ans[i].word == str && ans[i].split == sp) {
			rtn = true;
			break;
		}
	}
	return rtn;
}

void change(int val, string str, int sp, vector<lword>& ans) {
	if (val > max_value) {
		max_value = val;
		max_index = 0;
		if (ans.empty()) ans.resize(1);
		ans[0].word = str;
		ans[0].split = sp;
		max_index++;
	} else if (val == max_value && !haslw(str, sp, ans)) {
		if (ans.size() < max_index + 1) ans.resize(max_index + 1);
		ans[max_index].word = str;
		ans[max_index].split = sp;
		max_index++;
	}
}

void permu(vector<int>& nums, int si, vector<lword>& ans) {
	size_t len = nums.size();
	if (si == len) {
		for (int i = 0; i < len; ++i) {
			string str1 = num2str(nums, 0, i + 1);
			bool b1 = search(str1);
			int s1 = score(nums, 0, i + 1);
			if (i == len - 1 && b1) change(s1, str1, i + 1, ans);
			for (int j = 1; j < len - i; ++j) {
				string str2 = num2str(nums, i + 1, i + 1 + j);
				bool b2 = search(str2);
				int s2 = score(nums, i + 1, i + 1 + j);
				if (b1 && b2) {
					string str;
					int sp = 0;
					if (cmp_str(str1, str2)) { str = str2 + str1; sp = j; }
					else { str = str1 + str2; sp = i + 1; }
					change(s1 + s2, str, sp, ans);
				} else if (b1) {
					change(s1, str1, i + 1, ans);
				} else if (b2) {
					change(s2, str2, j, ans);
				}
			}
		}
	}
	for (size_t i = si; i < len; ++i) {
		int temp = nums[i];
		nums[i] = nums[si];
		nums[si] = temp;
		permu(nums, si + 1, ans);
		temp = nums[i];
		nums[i] = nums[si];
		nums[si] = temp;
	}
}

int main() {
    ofstream fout("lgame.out");
    ifstream fin("lgame.in");
	ifstream fdict("lgame.dict");
	string word;
	while (getline(fdict, word, '\n')) {
		if (word == ".") break;
		build(word);
	}
	fin >> word;
	vector<int> nums;
	for (size_t i = 0; i < word.size(); ++i) {
		char ch = word[i];
		int ci = (int)(ch - 'a');
		nums.push_back(ci);
		upp_value += values[ci];
	}
	vector<lword> ans;
	permu(nums, 0, ans);
	ans.resize(max_index);
	sort(ans.begin(), ans.end(), [](const lword& a, const lword& b) {
		return !cmp_str(a.word, b.word);
	});
	fout << max_value << endl;
	for (size_t i = 0; i < ans.size(); ++i) {
		if (ans[i].split == ans[i].word.size()) {
			fout << ans[i].word << endl;
		} else {
			fout << ans[i].word.substr(0, ans[i].split) << " " << ans[i].word.substr(ans[i].split) << endl;
		}
	}
    fin.close();
    fout.close();
	fdict.close();
    return 0;
}

