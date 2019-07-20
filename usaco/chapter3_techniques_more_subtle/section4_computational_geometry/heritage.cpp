/*
ID: wangbb21
LANG: C++
TASK: heritage
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string build(string& in, string& pre) {
	string ans = "";
	char root = pre[0];
	size_t i;
	for (i = 0; i < in.size(); ++i) 
		if (in[i] == root) 
			break;
	string in_left = in.substr(0, i);
	string in_right = in.substr(i + 1);
	string pre_left = pre.substr(1, i);
	string pre_right = pre.substr(i + 1);
	if (in_left.size() > 0 && pre_left.size() > 0) ans = ans + build(in_left, pre_left);
	if (in_right.size() > 0 && pre_right.size() > 0) ans = ans + build(in_right, pre_right);
	ans = ans + root;
	return ans;
}

int main() {
    ofstream fout("heritage.out");
    ifstream fin("heritage.in");
    string in_order, pre_order;
	fin >> in_order >> pre_order;
	fout << build(in_order, pre_order) << endl;
    fin.close();
    fout.close();
    return 0;
}

