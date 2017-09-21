/*
* directed graph
* find a point a where 
* a = argmin (max(min(a, b)))
* input format:
* n_0 (number of points, default indexes: 1, 2, ... ,n, n <- [1, 100])
* pairs to_0 cost_0 ... to_i cost_i ...  (cost_i <- [1, 10])
* ...
* 0 (indicates end. )
*/
#include <iostream>
using namespace std;

typedef struct queue {
	char value;	// value <- [1, 100]
	struct queue* next;
} Q;

Q* create_node(char value) {
	Q* r = new Q;
	r->value = value;
	r->next = NULL;
	return r;
}

void insert(Q* head, char value) {
	Q* t = head;
	while (t->next) {
		t = t->next;
	}
	t->next = create_node(value);
}

Q* dequeue(Q* head) {
	Q* t = head;
	Q* r = t->next;
	if (t->next) {
		t->next = t->next->next;
	}
	return r;
}

int main(int argc, char const *argv[])
{
	Q* root = create_node();
	char instance[101] = {0};
	char graph[101][101] = {0};
	int n, i, j, degree, b, w, min_point = 0, min_cost = INT_MAX;
	while (1) {
		cin >> n;
		if (n == 0) {
			break;
		}
		for (i = 1; i <= n; i++) {
			cin >> degree;
			for (j = 1; j <= degree; j++) {
				cin >> b >> w;
				graph[i][b] = w;
			}
		}
		for (i = 1; i <= n; i++) {
			int max_min_cost = INT_MIN;
			instance[i] = ;
			if (min_cost > instance[i]) {
				min_point = i;
				min_cost = instance[i];
			}
		}
		cout << min_point << " " << min_cost << endl;
	}
	return 0;
}