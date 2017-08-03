#include <iostream>
using namespace std;

typedef struct stack {
  int array[1003];
  int top;
} Stack;

void pop(Stack& s) {
  if (s.top > -1) {
    s.top--;
  }
}

int get_pop(Stack& s) {
  if (s.top > -1) {
    return s.array[s.top];
  }
  return 9999;
}

void push(Stack& s, int a) {
  s.array[++s.top] = a;
}

Stack stack1 = {{0}, -1};
Stack stack2 = {{0}, -1};
int n, input[1003] = {0};
char operate[2003] = {0};
char result[2003]  = {0};
bool lock = true;
int counter = 0;

void solution(int i, int in, int io) {
  if (i == n) {
    counter++;
    if (lock) {
      for (int j = 0; j < io; j++) {
        result[j] = operate[j];
      }
      lock = false;
    }
    return;
  }
  if (input[i] == in) {
    operate[io++] = 'a';
    operate[io++] = 'b';
    in++;
    while (true) {
      if (get_pop(stack1) == in) {
        operate[io++] = 'b';
        pop(stack1);
      } else if (get_pop(stack2) == in) {
        operate[io++] = 'd';
        pop(stack2);
      } else {
        break;
      }
      in++;
    }
    solution(i+1, in, io);
  } else {
    if (input[i] < get_pop(stack1) && input[i] >= get_pop(stack2)) {
      push(stack1, input[i]);
      operate[io++] = 'a';
      solution(i+1, in, io);
    } else if (input[i] < get_pop(stack2) && input[i] >= get_pop(stack1)) {
      push(stack2, input[i]);
      operate[io++] = 'c';
      solution(i+1, in, io);
    } else if (input[i] < get_pop(stack2) && input[i] < get_pop(stack1)) {
      push(stack1, input[i]);
      operate[io++] = 'a';
      solution(i+1, in, io);
      io--;
      pop(stack1);
      push(stack2, input[i]);
      operate[io++] = 'c';
      solution(i+1, in, io);
    } else {
      return;
    }
  }
}

int main() {
  int i;
  cin >> n;
  if (n == 0) {
    cout << 0 << endl;
    return 0;
  }
  for (i = 0; i < n; i++) {
    cin >> input[i];
  }
  solution(0, 1, 0);
  if (counter > 0) {
    for (i = 0; i < 2*n; i++) {
      cout << result[i] << " ";
    }
    cout << endl;
  } else {
    cout << 0 << endl;
  }
  return 0;
}