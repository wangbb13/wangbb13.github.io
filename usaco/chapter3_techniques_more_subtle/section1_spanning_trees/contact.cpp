/*
ID: wangbb21
LANG: C++
TASK: contact
 */
// think forward or backward
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// int kmp(string& str, string& k) {
//     int length = k.size();
//     vector<int> comm(length + 1, 0);
//     for (int i = 2; i <= length; ++i) {
//         int rec = i - 1;
//         while (rec > 0 && k[i - 1] != k[comm[rec]]) {
//             rec = comm[rec];
//         }
//         if (rec == 0) {
//             comm[i] = 0;
//         } else {
//             comm[i] = comm[rec] + 1;
//         }
//     }
//     int ans = 0, str_length = str.size(), k_p = 0, p = 0;
//     while (p < str_length) {
//         for (; str[p] == k[k_p] && k_p < length && p < str_length; ++p, ++k_p);
//         if (k_p == length) {
//             ans++;
//         }
//         if (k_p == 0) {
//             p++;
//         }
//         k_p = comm[k_p];
//     }
//     return ans;
// }

int main() {
    ofstream fout("contact.out");
    ifstream fin("contact.in");
    int A, B, N;
    fin >> A >> B >> N;
    string info = "", str = "";
    while (getline(fin, str)) {
        info = info + str;
    }

    int length = info.size();
    vector<bool> transform(length, false);
    for (int i = 0; i < length; ++i) {
        if (info[i] == '1')
            transform[i] = true;
    }
    vector<int> storage(5000, 0);
    vector<string> results(200001);
    vector<int> count(200001, 0);
    for (int i = A; i <= B; ++i) {
        std::fill(storage.begin(), storage.end(), 0);
        for (int j = 0; j <= length - i; ++j) {
            int index = 0;
            for (int k = j; k < j + i; ++k) {
                index <<= 1;
                if (transform[k]) {
                    index |= 1;
                }
            }
            storage[index]++;
        }
        int k = 1 << i;
        for (int j = 0; j < k; ++j) {
            if (storage[j] == 0) {
                continue;
            }
            string pattern = "";
            for (int p = 0, r = 1; p < i; ++p, r <<= 1) {
                char ch = '0' + ((r & j) > 0);
                pattern = ch + pattern;
            }
            if (count[storage[j]] > 0) {
                if (count[storage[j]] % 6 == 0) {
                    results[storage[j]] += "\n";
                } else {
                    results[storage[j]] += " ";
                }
            }
            results[storage[j]] += pattern;
            count[storage[j]]++;
        }
    }

    // vector<string> results(200001);
    // for (int i = A; i <= B; ++i) {
    //     int k = (1 << i);
    //     for (int j = 0; j < k; ++j) {
    //         string pattern = "";
    //         for (int p = 0, r = 1; p < i; ++p, r <<= 1) {
    //             char ch = '0' + ((r & j) > 0);
    //             pattern = ch + pattern;
    //         }
    //         int freq = kmp(info, pattern);
    //         if (results[freq].size() == 0) {
    //             results[freq] = pattern;
    //         } else {
    //             pattern = " " + pattern;
    //             results[freq] += pattern;
    //         }
    //     }
    // }

    int j = 0;
    for (int i = 200000; i > 0; --i) {
        if (results[i].size()) {
            fout << i << endl << results[i] << endl;
            if (++j == N) {
                break;
            }
        }
    }
	fin.close();
	fout.close();
    return 0;
}
