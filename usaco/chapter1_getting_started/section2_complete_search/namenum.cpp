/*
ID: wangbb21
LANG: C++
TASK: namenum
 */
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string str2num(string str) {
  char ch;
  string rtn = "";
  for (int i = 0; i < str.size(); i++) {
    if (str[i] == 'A' || str[i] == 'B' || str[i] == 'C') {
      rtn = rtn + "2";
    } else if (str[i] == 'D' || str[i] == 'E' || str[i] == 'F') {
      rtn = rtn + "3";
    } else if (str[i] == 'G' || str[i] == 'H' || str[i] == 'I') {
      rtn = rtn + "4";
    } else if (str[i] == 'J' || str[i] == 'K' || str[i] == 'L') {
      rtn = rtn + "5";
    } else if (str[i] == 'M' || str[i] == 'N' || str[i] == 'O') {
      rtn = rtn + "6";
    } else if (str[i] == 'P' || str[i] == 'R' || str[i] == 'S') {
      rtn = rtn + "7";
    } else if (str[i] == 'T' || str[i] == 'U' || str[i] == 'V') {
      rtn = rtn + "8";
    } else if (str[i] == 'W' || str[i] == 'X' || str[i] == 'Y') {
      rtn = rtn + "9";
    }
  }
  return rtn;
}

int main() {
  ofstream fout("namenum.out");
  ifstream fin("namenum.in");
  ifstream fdic("dict.txt");
  string str, num;
  bool nfind = true;
  fin >> num;
  while (fdic >> str) {
    if (num.size() == str.size() && num == str2num(str)) {
      fout << str << endl;
      nfind = false;
    }
  }
  if (nfind) {
    fout << "NONE" << endl;
  }
  return 0;
}
