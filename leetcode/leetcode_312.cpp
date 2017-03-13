#include <iostream>
#include <vector>
using namespace std;

#define max(a, b) ((a) > (b) ? (a) : (b))

typedef struct node {
  int val;
  struct node* left;
  struct node* right;
} Node;

Node* root;

Node* newNode() {
  Node* nd = new Node;
  nd->val = -1;
  nd->left = NULL;
  nd->right = NULL;
  return nd;
}

int maxVal(int* array, int n, int remain) {
  int rtn = 0;
  bool hasSave = true;
  Node* nd = root;
  for (int i = 0; i < n; i++) {
    if (array[i] >= 0) {
      nd = nd->right;
    } else {
      nd = nd->left;
    }
    if (nd == NULL) {
      hasSave = false;
      break;
    }
  }
  if (hasSave) {
    return nd->val;
  }
  if (remain == 1) {
    int i;
    Node* probe = root;
    for (i = 0; i < n; i++) {
      if (array[i] >= 0) {
        if (probe->right == NULL) {
          probe->right = newNode();
        }
        probe = probe->right;
        rtn = array[i];
      } else {
        if (probe->left == NULL) {
          probe->left = newNode();
        }
        probe = probe->left;
      }
    }
    probe->val = rtn;
  } else {
    for (int i = 0; i < n; i++) {
      if (array[i] >= 0) {
        int r = array[i], temp = array[i];
        int a = 1, b = 1, k = i, mv;
        Node* probe = root;
        while (--k >= 0 && array[k] < 0);
        if (array[k] >= 0 && k >= 0) { a = array[k]; }
        k = i;
        while (++k < n && array[k] < 0);
        if (array[k] >= 0 && k < n) { b = array[k]; }
        r = a * r * b;
        array[i] = -1;
        mv = maxVal(array, n, remain-1);
        for (int l = 0; l < n; l++) {
          if (array[l] < 0) {
            if (probe->left == NULL) {
              probe->left = newNode();
            }
            probe = probe->left;
          } else {
            if (probe->right == NULL) {
              probe->right = newNode();
            }
            probe = probe->right;
          }
        }
        probe->val = mv;
        r += mv;
        rtn = max(rtn, r);
        array[i] = temp;
      }
    }
  }
  return rtn;
}

int main(int argc, char const *argv[])
{
  int n, array[500];
  root = newNode();
  cin >> n;
  for (int i = 0; i < n; i++) {
    array[i] = 0;
  }
  for (int i = 0; i < n; i++) {
    cin >> array[i];
  }
  cout << maxVal(array, n, n) << endl;
  system("pause");
  return 0;
}