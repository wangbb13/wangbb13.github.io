#include <iostream>
#include <cstring>
using namespace std;

int position[26];
int stack[26][26];
int n;

void stack_add(int si, int a) {
  int index = -1;
  while (stack[si][++index] != -1);
  stack[si][index] = a;
  position[a] = si;
}

// 在将a搬到b上之前，先将a和b上的积木放回原来的位置（例如：1就放回1的最开始位罝）
void move_onto(int a, int b) {
  int pos, index, content, temp;
  // deal with b
  pos = position[b];
  for (index = 0; index < n; index++) {
    if (stack[pos][index] == b) {
      break;
    }
  }
  temp = ++index;
  for ( ; stack[pos][index] != -1; index++) {
    content = stack[pos][index];
    stack[pos][index] = -1;
    stack_add(content, content);
  }
  stack[pos][temp] = a;
  // deal with a
  pos = position[a];
  position[a] = position[b];
  for (index = 0; index < n; index++) {
    if (stack[pos][index] == a) {
      break;
    }
  }
  stack[pos][index++] = -1;
  for ( ; stack[pos][index] != -1; index++) {
    content = stack[pos][index];
    stack[pos][index] = -1;
    stack_add(content, content);
  }
}

// 在将a搬到b所在的那堆积木之上之前，先将a上的积木放回原来的位罝（b所在的那堆积木不动）
void move_over(int a, int b) {
  int pos, index, content, temp;
  pos = position[a];
  stack_add(position[b], a);
  for (index = 0; index < n; index++) {
    if (stack[pos][index] == a) {
      break;
    }
  }
  stack[pos][index++] = -1;
  for ( ; stack[pos][index] != -1; index++) {
    content = stack[pos][index];
    stack[pos][index] = -1;
    stack_add(content, content);
  }
}

// 将a本身和其上的积木一起放到b上，在搬之前b上方的积木放回原位
void pile_onto(int a, int b) {
  int pos, index, content, temp, posb;
  pos = position[b];
  posb = pos;
  for (index = 0; index < n; index++) {
    if (stack[pos][index] == b) break;
  }
  temp = ++index;
  for ( ; stack[pos][index] != -1; index++) {
    content = stack[pos][index];
    stack[pos][index] = -1;
    stack_add(content, content);
  }
  // deal with a
  pos = position[a];
  for (index = 0; index < n; index++) {
    if (stack[pos][index] == a) break;
  }
  for (; stack[pos][index] != -1; index++) {
    content = stack[pos][index];
    stack[pos][index] = -1;
    stack[posb][temp++] = content;
    position[content] = posb;
  }
}

// 将a本身和其上的积木一起搬到到b所在的那堆积木之上
void pile_over(int a, int b) {
  int pos, index, content, temp, posb;
  pos = position[b];
  posb = pos;
  for (index = 0; index < n; index++) {
    if (stack[pos][index] == -1) break;
  }
  temp = index;
  // deal with a
  pos = position[a];
  for (index = 0; index < n; index++) {
    if (stack[pos][index] == a) break;
  }
  for ( ; stack[pos][index] != -1; index++) {
    content = stack[pos][index];
    stack[pos][index] = -1;
    position[content] = posb;
    stack[posb][temp++] = content;
  }
}

int main(int argc, char const *argv[])
{
  
  int i, j, a, b;
  char input[5];
  cin >> n;
  for (i = 0; i < n; i++) {
    stack[i][0] = i;
    position[i] = i;
    for (j = 1; j < n; j++) {
      stack[i][j] = -1;
    }
  }
  for ( ; ; ) {
    cin >> input;
    if (strncmp(input, "move", 4) == 0) {
      cin >> a >> input >> b;
      if (a == b || position[a] == position[b]) {
        continue;
      }
      if (strncmp(input, "onto", 4) == 0) {   // move a onto b; 
        move_onto(a, b);
      } else if (strncmp(input, "over", 4) == 0) {  // move a over b;
        move_over(a, b);
      }
    } else if (strncmp(input, "pile", 4) == 0) {
      cin >> a >> input >> b;
      if (a == b || position[a] == position[b]) {
        continue;
      }
      if (strncmp(input, "onto", 4) == 0) {   // pile a onto b;
        pile_onto(a, b);
      } else if (strncmp(input, "over", 4) == 0) {    // pile a over b;
        pile_over(a, b);
      }
    } else if (strncmp(input, "quit", 4) == 0) {
      break;
    }
  }
  
  for (i = 0; i < n; i++) {
    cout << i << ": ";
    j = -1;
    while (stack[i][++j] != -1) cout << stack[i][j] << " ";
    cout << endl;
  }
  system("pause");
  return 0;
}