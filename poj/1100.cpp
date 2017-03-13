#include <iostream>
using namespace std;

int notationPos[20], mid[100];
int stack1[100], stack2[100];
int result, instances;
bool lock;

int toOp(int n) {
  if (n == 2) {
    return -5;
  } else if (n == 1) {
    return -4;
  } else {
    return -3;
  }
}

// -3: +  -4: - -5: *
void showExpr(int midIndex) {
  for (int i = 0; i < midIndex; i++) {
    if (mid[i] == -3) {
      cout << "+";
    } else if (mid[i] == -4) {
      cout << "-";
    } else if (mid[i] == -5) {
      cout << "*";
    } else if (mid[i] == -1) {
      cout << "(";
    } else if (mid[i] == -2) {
      cout << ")";
    } else {
      cout << mid[i];
    }
  }
  cout << endl;
}

void dispose(int notationCount, int midIndex) {
  int n = 1, i, j, l, s1, s2, t;
  for (i = 0; i < notationCount; i++) {
    n *= 3;
  }
  for (l = 0; l < n; l++) {
    t = l;
    for (j = notationCount-1; j >= 0; j--) {
      mid[notationPos[j]] = toOp(t%3);
      t /= 3;
    }
    // for (int m = 0; m < midIndex; m++) {
    //   cout << mid[m] << " ";
    // }
    // cout << endl;
    s1 = 0;
    s2 = 0;
    for (i = 0; i < midIndex; i++) {
      if (mid[i] == -1) {
        stack2[s2++] = -1;
      } else if (mid[i] == -2) {
        while (stack2[--s2] != -1) {
          stack1[s1++] = stack2[s2];
        }
      } else if (mid[i] < 0) {
        if (s2 == 0) {
          stack2[s2++] = mid[i];
          continue;
        }
        while (stack2[--s2] < -2 && s2 >= 0) {
          stack1[s1++] = stack2[s2];
        }
        stack2[++s2] = mid[i];
        s2++;
      } else {
        stack1[s1++] = mid[i];
      }
    }
    while (s2 > 0) {
      stack1[s1++] = stack2[--s2];
    }
    s2 = 0;
    for (i = 0; i < s1; i++) {
      if (stack1[i] > 0) {
        stack2[s2++] = stack1[i];
      } else {
        if (stack1[i] == -3) {
          stack2[s2-2] += stack2[s2-1];
        } else if (stack1[i] == -4) {
          stack2[s2-2] -= stack2[s2-1];
        } else if (stack1[i] == -5) {
          stack2[s2-2] *= stack2[s2-1];
        }
        s2--;
      }
    }
    if (result == stack2[0]) {
      cout << "Equation #" << (++instances) << ":" << endl;
      cout << result << "=";
      showExpr(midIndex);
      cout << endl;
      lock = true;
      return;
    }
  }
}

int main(int argc, char const *argv[])
{
  int len, notationCount, midIndex;
  char ch;
  char right[100] = {0};
  instances = 0;
  while (true) {
    cin >> result;
    if (result == 0) {
      break;
    }
    while ((ch = cin.get()) != '=');
    len = 0;
    while ((ch = cin.get()) == ' ');
    right[len++] = ch;
    while (true) {
      ch = cin.get();
      if (ch == '\n') {
        right[len] = 0;
        break;
      }
      right[len++] = ch;
    }
    notationCount = 0;
    midIndex = 0;
    for (int i = 0; i < len; i++) {   // -1 -> ( -2 -> )
      if (right[i] == '(') {
        mid[midIndex++] = -1;
      } else if (right[i] == ')') {
        mid[midIndex++] = -2;
        if (right[i+1] == '(' || (right[i+1] >= '0' && right[i+1] <= '9')) {
          notationPos[notationCount++] = midIndex;
          mid[midIndex++] = -3;
        }
      } else if (right[i] == ' ') {
        while (right[i] == ' ') { i++; }
        if (mid[midIndex-1] != -1 && 
          (right[i] == '(' || (right[i] >= '0' && right[i] <= '9'))) {
          notationPos[notationCount++] = midIndex;
          mid[midIndex++] = -3;
        }
        i--;
      } else {
        int n = right[i] - '0';
        while (right[++i] >= '0' && right[i] <= '9') {
          n = n*10 + (right[i] - '0');
        }
        mid[midIndex++] = n;
        i--;
        if (right[i+1] == '(') {
          notationPos[notationCount++] = midIndex;
          mid[midIndex++] = -3;
        }
      }
    }
    lock = false;
    dispose(notationCount, midIndex);
    if (!lock) {
      cout << "Equation #" << (++instances) << ":" << endl;
      cout << "Impossible" << endl;
      cout << endl;
    }
  }
  system("pause");
  return 0;
}

    // for (int i = 0; i < notationCount; i++) {
    //   cout << notationPos[i] << " ";
    // }
    // cout << endl;
    // for (int i = 0; i < midIndex; i++) {
    //   cout << mid[i] << " ";
    // }
    // cout << endl;

// void dispose(int n, int notationCount, int midIndex) {
//   if (lock) {
//     return;
//   }
//   if (notationCount == n) {
//     Head* infix = new Head;
//     Head* postfix = new Head;
//     initHead(infix);
//     initHead(postfix);
//     int i = 0, j;
//     for (j = 0; j < notationCount; j++) {
//       for (; i < notationPos[j]; i++) {
//         Node* nd = new Node;
//         if (mid[i] == -1) {
//           nd->isNumberOrChar = false;
//           nd->ch = '(';
//         } else if (mid[i] == -2) {
//           nd->isNumberOrChar = false;
//           nd->ch = ')';
//         } else {
//           nd->isNumberOrChar = true;
//           nd->number = mid[i];
//         }
//         nd->next = NULL;
//         push(infix, nd);
//       }
//       Node* nd = new Node;
//       nd->isNumberOrChar = false;
//       nd->ch = notation[j];
//       nd->next = NULL;
//       push(infix, nd);
//     }
//     for (; i < midIndex; i++) {
//       Node* nd = new Node;
//       if (mid[i] == -1) {
//         nd->isNumberOrChar = false;
//         nd->ch = '(';
//       } else if (mid[i] == -2) {
//         nd->isNumberOrChar = false;
//         nd->ch = ')';
//       } else {
//         nd->isNumberOrChar = true;
//         nd->number = mid[i];
//       }
//       nd->next = NULL;
//       push(infix, nd);
//     }
//     infixToPostfix(infix, postfix);
//     if (result == computeFromPostfix(postfix)) {
//       cout << "Equation #" << (++instances) << ":" << endl;
//       cout << result << "=";
//       showStack(infix);
//       lock = true;
//     }
//   } else {
//     notation[n] = '+';
//     dispose(n+1, notationCount, midIndex);
//     notation[n] = '-';
//     dispose(n+1, notationCount, midIndex);
//     notation[n] = '*';
//     dispose(n+1, notationCount, midIndex);
//   }
// }

/*
typedef struct node {
  bool isNumberOrChar;
  int number;
  char ch;
  struct node* next;
  ~node() {
    next = NULL;
  }
} Node;

typedef struct head {
  int count;
  Node* first;
  Node* tail;
  ~head() {
    first = NULL;
    tail = NULL;
  }
} Head;

Node* pop(Head* h) {
  if (h->count == 0) {
    return NULL;
  }
  Node* f = h->first;
  Node* t = h->tail;
  Node* temp = f;
  if (f == t) {
    h->first = NULL;
    h->tail = NULL;
    h->count = 0;
    return f;
  }
  while (temp->next) {
    if (temp->next == t) {
      temp->next = NULL;
      h->tail = temp;
      h->count -= 1;
      return t;
    }
    temp = temp->next;
  }
}

void push(Head* h, Node* n) {
  h->count++;
  if (h->first == NULL) {
    h->first = n;
    h->tail = n;
  } else {
    h->tail->next = n;
    h->tail = n;
  }
}

void destroy(Head* h) {
  Node* index = h->first;
  while (index) {
    Node* t = index;
    index = index->next;
    delete t;
  }
  delete h;
}

void clear(Head* h) {
  Node* index = h->first;
  while (index) {
    Node* t = index;
    index = index->next;
    delete t;
  }
  h->first = NULL;
  h->tail = NULL;
  h->count = 0;
}

void showStack(Head* h) {
  Node* temp = h->first;
  if (temp == NULL) {
    cout << "stack is NULL" << endl;
    return;
  }
  while (temp) {
    if (temp->isNumberOrChar) {
      cout << temp->number;
    } else {
      cout << temp->ch;
    }
    temp = temp->next;
  }
  cout << endl;
}

void initHead(Head* h) {
  h->first = NULL;
  h->tail = NULL;
  h->count = 0;
}

// b = a
void copy(Node* a, Node* b) {
  b->isNumberOrChar = a->isNumberOrChar;
  b->number = a->number;
  b->ch = a->ch;
  b->next = NULL;
}

bool insertDirectly(Head* h, Node* n) {
  Node* temp = h->tail;
  if (n->ch == ')') {
    return false;
  } else if (temp == NULL || n->ch == '(' || temp->ch == '(') {
    return true;
  } else {
    return false;
  }
}

// from left to right scan infix (from first to tail)
void infixToPostfix(Head* infix, Head* postfix) {
  Head* inter = new Head;
  initHead(inter);
  Node* index = infix->first;
  while (index) {
    if (index->isNumberOrChar) {
      Node* nd = new Node;
      copy(index, nd);
      push(postfix, nd);
    } else {
      if (insertDirectly(inter, index)) {
        Node* nd = new Node;
        copy(index, nd);
        push(inter, nd);
      } else if (index->ch == ')') {
        Node* temp = pop(inter);
        while (temp->ch != '(') {
          push(postfix, temp);
          temp = pop(inter);
        }
      } else {
        Node* temp;
        while (true) {
          temp = pop(inter);
          push(postfix, temp);
          if (insertDirectly(inter, index)) {
            break;
          }
        }
        Node* nd = new Node;
        copy(index, nd);
        push(inter, nd);
      }
    }
    index = index->next;
  }
  Node* temp = pop(inter);
  while (temp != NULL) {
    push(postfix, temp);
    temp = pop(inter);
  }
  destroy(inter);
}

int computeAOpB(int a, int b, char op) {
  switch (op) {
    case '+':
      return (a + b);
    case '-':
      return (a - b);
    case '*':
      return (a * b);
    case '/':
      if (b == 0) {
        return 0;
      } else {
        return (a / b);
      }
    default:
      cout << "op is not in scope" << endl;
      return -1;
  }
}

int computeFromPostfix(Head* postfix) {
  Head* inter = new Head;
  initHead(inter);
  Node* index = postfix->first;
  Node* temp;
  while (index) {
    if (index->isNumberOrChar) {
      Node* nd = new Node;
      copy(index, nd);
      push(inter, nd);
    } else {
      char op = index->ch;
      int a, b;
      Node* nd = new Node;
      temp = pop(inter);
      b = temp->number;
      temp = pop(inter);
      a = temp->number;
      nd->isNumberOrChar = true;
      nd->number = computeAOpB(a, b, op);
      nd->next = NULL;
      push(inter, nd);
    }
    index = index->next;
  }
  temp = inter->first;
  if (temp == NULL || temp->isNumberOrChar == false) {
    cout << "something wrong in postfix" << endl;
    showStack(postfix);
    return -1;
  } else {
    return temp->number;
  }
  destroy(inter);
}

char toOp(int n) {
  if (n == 2) {
    return '*';
  } else if (n == 1) {
    return '-';
  } else {
    return '+';
  }
}

void dispose(int notationCount, int midIndex) {
  int n = 1, i, j, l, t;
  Head* infix = new Head;
  Head* postfix = new Head;
  initHead(infix);
  initHead(postfix);
  for (i = 0; i < notationCount; i++) {
    n *= 3;
  }
  for (l = 0; l < n; l++) {
    t = l;
    for (j = notationCount-1; j >= 0; j--) {
      notation[j] = toOp(t%3);
      t /= 3;
    }
    i = 0;
    for (j = 0; j < notationCount; j++) {
      for (; i < notationPos[j]; i++) {
        Node* nd = new Node;
        if (mid[i] == -1) {
          nd->isNumberOrChar = false;
          nd->ch = '(';
        } else if (mid[i] == -2) {
          nd->isNumberOrChar = false;
          nd->ch = ')';
        } else {
          nd->isNumberOrChar = true;
          nd->number = mid[i];
        }
        nd->next = NULL;
        push(infix, nd);
      }
      Node* nd = new Node;
      nd->isNumberOrChar = false;
      nd->ch = notation[j];
      nd->next = NULL;
      push(infix, nd);
    }
    for (; i < midIndex; i++) {
      Node* nd = new Node;
      if (mid[i] == -1) {
        nd->isNumberOrChar = false;
        nd->ch = '(';
      } else if (mid[i] == -2) {
        nd->isNumberOrChar = false;
        nd->ch = ')';
      } else {
        nd->isNumberOrChar = true;
        nd->number = mid[i];
      }
      nd->next = NULL;
      push(infix, nd);
    }
    infixToPostfix(infix, postfix);
    if (result == computeFromPostfix(postfix)) {
      cout << "Equation #" << (++instances) << ":" << endl;
      cout << result << "=";
      showStack(infix);
      lock = true;
      destroy(infix);
      destroy(postfix);
      return;
    }
    clear(infix);
    clear(postfix);
  }
}
 */