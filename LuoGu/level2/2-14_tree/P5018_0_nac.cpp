/**
 * Description: symmetric weight binary tree 
 * Input : a weight tree T
 * Output: the maximum number of nodes of a sub symmetric binary tree 
 * Time/Space Limit: 1s/128MB
 */
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <queue>	// queue, priority_queue
#include <algorithm>
using namespace std;

typedef pair<int, int> m_tuple;

typedef struct _tn {
	int w;
	int li, ri;
	int n, wn;
	bool left;
} tn;

m_tuple num_of_nodes(vector<tn>& tree, int i) {
	if (tree[i].n > 0) return make_pair(tree[i].n, tree[i].wn);
	int ans_n = 1;
	int ans_wn = tree[i].w;
	if (tree[i].li > 0) {
		m_tuple res = num_of_nodes(tree, tree[i].li);
		ans_n += res.first;
		ans_wn += res.second;
	}
	if (tree[i].ri > 0) {
		m_tuple res = num_of_nodes(tree, tree[i].ri);
		ans_n += res.first;
		ans_wn += res.second;
	}
	tree[i].n = ans_n;
	tree[i].wn = ans_wn;
	// cout << "node " << i << ": " << ans_n << endl;
	return make_pair(ans_n, ans_wn);
}

// L: -1; R: +1; M: 0
void __preorder(vector<tn>& tree, vector<int>& st, vector<int>& wt, vector<int>& id_map, int ni, int& si) {
	wt[si] = tree[ni].w;
	if (tree[ni].li == -1 && tree[ni].ri == -1)	{ // leaf node
		if (tree[ni].left)
			st[si] = -1;
		else
			st[si] = 1;
		id_map[ni] = si;
		si++;
		return;
	}
	id_map[ni] = si;
	// st[si] = 0;
	st[si] = (tree[ni].left) ? (-1) : (1);
	si++;
	if (tree[ni].li > 0) 
		__preorder(tree, st, wt, id_map, tree[ni].li, si);
	if (tree[ni].ri > 0) 
		__preorder(tree, st, wt, id_map, tree[ni].ri, si);
}

void preorder(vector<tn>& tree, vector<int>& st, vector<int>& wt, vector<int>& id_map) {
	int si = 0;
	__preorder(tree, st, wt, id_map, 1, si);
	// cout << "si = " << si << endl;
}

// L: -1; R: +1; M: 0
void __postorder(vector<tn>& tree, vector<int>& st, vector<int>& wt, vector<int>& id_map, int ni, int& si) {
	if (tree[ni].li > 0) 
		__postorder(tree, st, wt, id_map, tree[ni].li, si);
	if (tree[ni].ri > 0) 
		__postorder(tree, st, wt, id_map, tree[ni].ri, si);
	wt[si] = tree[ni].w;
	// cout << "node " << ni << ",";
	if (tree[ni].li == -1 && tree[ni].ri == -1)	{ // leaf node
		if (tree[ni].left)
			st[si] = -1;
		else
			st[si] = 1;
		id_map[ni] = si;
		si++;
		return;
	}
	// st[si] = 0;
	st[si] = (tree[ni].left) ? (-1) : (1);
	id_map[ni] = si;
	si++;
}

void postorder(vector<tn>& tree, vector<int>& st, vector<int>& wt, vector<int>& id_map) {
	int si = 0;
	__postorder(tree, st, wt, id_map, 1, si);
	// cout << "si = " << si << endl;
}

void show_vec(const vector<int>& nums) {
	for (size_t i = 0; i < nums.size(); ++i) 
		cout << nums[i] << " ";
	cout << endl;
}

struct compare {
	bool operator() (const m_tuple& lhs, const m_tuple& rhs) {
		return lhs.first > rhs.first;
	}
};

int main() {
    int n;
	cin >> n;
	vector<tn> tree(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> tree[i].w;
		tree[i].n = 0;
		tree[i].wn = 0;
		tree[i].left = true;	// default: left
	}
	for (int i = 1; i <= n; ++i) {
		cin >> tree[i].li >> tree[i].ri;
		if (tree[i].ri > 0) 
			tree[tree[i].ri].left = false;	// right node 
	}
	// # nodes of every non-leaf node
	num_of_nodes(tree, 1);
	vector<int> pre_st(n);
	vector<int> pre_wt(n);
	vector<int> pre_map(n + 1);		// node id => index
	vector<int> post_st(n);
	vector<int> post_wt(n);
	vector<int> post_map(n + 1);	// node id => index
	// preoder traversal
	preorder(tree, pre_st, pre_wt, pre_map);
	pre_st[0] = 0;
	// postorder traversal
	postorder(tree, post_st, post_wt, post_map);
	post_st[n - 1] = 0;
	
	// debug
	cout << "preorder structer: " << endl;
	show_vec(pre_st);
	show_vec(pre_wt);
	show_vec(pre_map);
	cout << "postorder structer: " << endl;
	show_vec(post_st);
	show_vec(post_wt);
	show_vec(post_map);
	
	// process
	int ans = 1;
	// priority_queue<m_tuple, vector<m_tuple>, compare> m_q;
	priority_queue<m_tuple> m_q;
	m_q.push(make_pair(tree[1].n, 1));
	int root_id, left_n, left_wn, right_n, right_wn;
	while (!m_q.empty()) {
		root_id = m_q.top().second;
		// cout << "Process root " << root_id << endl;
		m_q.pop();
		if (tree[root_id].li == -1 && tree[root_id].ri == -1) 
			continue;
		// # nodes
		left_n = 0;
		if (tree[root_id].li > 0) 
			left_n = tree[tree[root_id].li].n;
		right_n = 0;
		if (tree[root_id].ri > 0) 
			right_n = tree[tree[root_id].ri].n;
		// cout << "left n = " << left_n << ", right n = " << right_n << endl;
		if (left_n > right_n) {
			m_q.push(make_pair(tree[tree[root_id].li].n, tree[root_id].li));
			m_q.push(make_pair(tree[tree[root_id].ri].n, tree[root_id].ri));
			continue;
		} else if (left_n < right_n) {
			m_q.push(make_pair(tree[tree[root_id].ri].n, tree[root_id].ri));
			m_q.push(make_pair(tree[tree[root_id].li].n, tree[root_id].li));
			continue;
		}
		// sum of weight
		left_wn = 0;
		if (tree[root_id].li > 0) 
			left_wn = tree[tree[root_id].li].wn;
		right_wn = 0;
		if (tree[root_id].ri > 0) 
			right_wn = tree[tree[root_id].ri].wn;
		if (left_wn != right_wn) {
			m_q.push(make_pair(tree[tree[root_id].li].n, tree[root_id].li));
			m_q.push(make_pair(tree[tree[root_id].ri].n, tree[root_id].ri));
			continue;
		}
		// judge
		// cout << "Judge root " << root_id << " (" << left_n << ")" << endl;
		int pre_i = pre_map[root_id] + left_n;
		int post_i = post_map[root_id] - right_n;
		// cout << "Pre i = " << pre_i << ", Post i = " << post_i << endl;
		bool legit = true;
		for (int p = 0; p < left_n; ++p) {
			if (pre_st[pre_i] + post_st[post_i] != 0 || 
				pre_wt[pre_i] != post_wt[post_i]) {
				legit = false;
				break;
			}
			pre_i--;
			post_i++;
		}
		if (legit) {
			ans = tree[root_id].n;
			break;
		} else {
			m_q.push(make_pair(tree[tree[root_id].li].n, tree[root_id].li));
			m_q.push(make_pair(tree[tree[root_id].ri].n, tree[root_id].ri));
		}
	}
	cout << ans << endl;
    return 0;
}

