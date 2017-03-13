/*
* edit distance
* simliraty of two strings
* algorithm: dp
* operation: delete insert substitute
* recursion relations:
* d_ij express string a (strlen(a) = i)
* convert to string b(strlen(b) = j) 
* needs d_ij steps
* d_i0 = sigma w_del a_k
* d_0j = sigma w_sub b_k
* d_ij = if a_i == b_j then d_(i-1)(j-1)
         else min{ d_(i-1)j + w_del(a_i), 
                   d_i(j-1) + w_ins(b_j),
                   d_(i-1)(j-1) + w_sub(a_i, b_j) }
*/
#include <iostream>
#include <cstring>
using namespace std;

int main(int argc, char const *argv[])
{
	char str1[101];
	char str2[101];
	int dp[101][101];
	int str1_len, str2_len;
	int i, j;
	cin >> str1 >> str2;
	str1_len = strlen(str1);
	str2_len = strlen(str2);
	for (i = 1; i <= str1_len; i++) {
		dp[i][0] = i;
	}
	for (i = 1; i <= str2_len; i++) {
		dp[0][i] = i;
	}
	dp[0][0] = 0;
	for (i = 1; i <= str1_len; i++) {
		for (j = 1; j <= str2_len; j++) {
			if (str1[i-1] == str2[j-1]) {
				dp[i][j] = dp[i-1][j-1];
			} else {
				dp[i][j] = min((dp[i-1][j] + 1), (dp[i][j-1] + 1));
				dp[i][j] = min((dp[i][j]), (dp[i-1][j-1] + 1));
			}
		}
	}
	i = str1_len;
	j = str2_len;
	while (1) {
		if (i == 0 || j == 0) {
			break;
		}
		if (dp[i][j] == dp[i-1][j-1] && str1[i-1] == str2[j-1]) {
			cout << str1[i-1] << " = " << str2[j-1] << endl;
			i--;
			j--;
		} else if (dp[i][j] == (dp[i-1][j-1] + 1)) {
			cout << "substitute " << str1[i-1] << " and " << str2[j-1] << endl;
			i--;
			j--;
		} else if (dp[i][j] == (dp[i-1][j] + 1)) {
			cout << "delete " << str1[i-1] << endl;
			i--;
		} else if (dp[i][j] == (dp[i][j-1] + 1)) {
			cout << "insert " << str2[j-1] << endl;
			j--;
		}
	}
	while ((i--) >= 1) {
		cout << "delete " << str1[i] << endl;
	}
	while ((j--) >= 1) {
		cout << "insert " << str2[j] << endl;
	}
	cout << (dp[str1_len][str2_len]) << endl;
	getchar();
	getchar();
	return 0;
}
