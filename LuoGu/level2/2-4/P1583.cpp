#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

typedef struct _photo {
	int id;
	int w;
} photo;

template<typename T>
void my_swap(T *a, T *b) {
	int tmp = a->id;
	a->id = b->id;
	b->id = tmp;
	tmp = a->w;
	a->w = b->w;
	b->w = tmp;
}

template<typename T>
bool compare(T *a, T *b) {
	return (((a->w) > (b->w)) || (a->w == b->w && a->id < b->id));
}

template<typename T>
void assign(T *a, T *b) { // a = b;
	a->id = b->id;
	a->w = b->w;
}

template<typename T>
void quick_sort(T *nums, int l, int r) { // [l, r]
	if (l < r) {
		int x = l + (rand() % (r - l + 1));
		my_swap<T>(nums + l, nums + x);
		int i = l, j = r;
		T key = nums[l];
		while (i < j) {
			while ((i < j) && (!compare<T>(nums + j, &key))) {
				j--;
			}
			if (i < j) {
				// assign<T>(nums + i, nums + j);
				*(nums + i) = *(nums + j);
				i++;
			}
			while ((i < j) && (compare<T>(nums + i, &key))) {
				i++;
			}
			if (i < j) {
				// assign<T>(nums + j, nums + i);
				*(nums + j) = *(nums + i);
				j--;
			}
		}
		// assign<T>(nums + i, &key);
		*(nums + i) = key;
		quick_sort(nums, l, i - 1);
		quick_sort(nums, i + 1, r);
	}
}

int main() {
    srand((unsigned)time(NULL));
	int n, k;
	cin >> n >> k;
	int e[10] = {0};
	for (int i = 0; i < 10; ++i) 
		cin >> e[i];
	photo *nums = new photo[n];
	for (int i = 1; i <= n; ++i) {
		nums[i - 1].id = i;
		cin >> nums[i - 1].w;
	}
	quick_sort<photo>(nums, 0, n - 1);
	for (int i = 0, j = 0; i < n; ++i, j = (j + 1) % 10) {
		nums[i].w += e[j];
	}
	quick_sort<photo>(nums, 0, n - 1);
	for (int i = 0; i < k; ++i) {
		cout << nums[i].id << " ";
	}
	cout << endl;
    return 0;
}

