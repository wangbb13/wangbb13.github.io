/**
 * Description: 
 * Input : 
 * Output: 
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>
#include <cmath>
#include <vector>
#include <type_traits>
#include <algorithm>
#include <chrono>
#include <queue>
#include <iomanip>
using namespace std;

#define PI 3.14159265

template <typename T>
typename std::enable_if<std::is_integral<T>::value, bool>::type
is_odd (T i) { return bool(i % 2); }

template <typename T, 
		  typename = typename std::enable_if<std::is_integral<T>::value>::type>
bool is_even(T i) { return !bool(i % 2); }

int main() {
	// int a = 10;
	// double b = 0.1;
	// char c = 'A';
	// cout << std::boolalpha;
	// cout << "a is odd: " << is_odd(a) << endl;
	// cout << "a is even: " << is_even(a) << endl;

	// cout << "b is odd: " << is_odd(b) << endl;
	// cout << "b is even: " << is_even(b) << endl;
    
	// cout << "c is odd: " << is_odd(c) << endl;
	// cout << "c is even: " << is_even(c) << endl;
	auto start = std::chrono::high_resolution_clock::now();
	int len = 1000;
	int *a = new int[len];
	int *b = new int[len];
	int *c = new int[len];
	std::fill(a, a + len, 1);
	std::fill(b, b + len, 1);
	for (int i = 0; i < len; ++i) 
		c[i] = a[i] + b[i];
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
	cout << std::fixed;
	cout << std::setprecision(5);
	cout << "Elapsed time: " << duration.count() << endl;

	queue<int> *myQ = new queue<int>();
	(*myQ).push(10);

	return 0;
}

