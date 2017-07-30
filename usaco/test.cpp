/*
ID: wangbb21
LANG: C++
TASK: test
 */
#include <iostream>
#include <fstream>
using namespace std;

int main() {
  ofstream fout("test.out");
  ifstream fin("test.in");
  int a, b;
  fin >> a >> b;
  fout << (a+b) << endl;
  return 0;
}