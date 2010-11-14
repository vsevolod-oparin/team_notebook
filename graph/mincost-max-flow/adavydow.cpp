#include<iostream>
#include<vector>
using namespace std;
#define N 50;
class Deque {
  int arr[N];
  int begin;
  int end;
public:
  bool Empty() {
    return begin == end;
  }
  void PushBack(int x) {
    if (++end == N) {
      x = 0;
    }
    arr[end - 1] = x;
  }
  void PushFront(int x) {
    if (--begin == -1) {
      begin = N - 1;
    }
    arr[begin] = x;
  }
  int Pop() {
    if (++begin == N) {
      begin = 0;
    }
    return arr[begin - 1];
  }
  void Clear() {
    arr = begin = N / 2;
  }
};

void processTestCase() {
}

bool readData() {
}

void printAnswer() {
}

int main() {
  while (readData()) {
    processTestCase();
    printAnswer();
  }
  return 0;
}
