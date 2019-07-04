/**
 * Description: intermediate & postorder => preorder
 * Input : ... 
 * Output: ... 
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>
#include <string>
using namespace std;

string process(string im, string post) {
	size_t len = im.size();
	string ans = post.substr(len - 1);
	char last = post[len - 1];
	size_t i = 0;
	for (; i < len; ++i) 
		if (im[i] == last) 
			break;
	string left = "", right = "";
	if (i > 0) 
		left = process(im.substr(0, i), post.substr(0, i));
	if (i + 1 < len) 
		right = process(im.substr(i + 1), post.substr(i, len - 1 - i));
	return ans + left + right;
}

int main() {
    string im, post;
	cin >> im >> post;
	cout << process(im, post) << endl;
    return 0;
}

