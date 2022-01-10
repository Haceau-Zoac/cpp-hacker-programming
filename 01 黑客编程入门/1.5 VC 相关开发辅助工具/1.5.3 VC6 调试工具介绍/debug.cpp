#include <iostream>

int main(int argc, char* argv[]) {
  int* p{ nullptr };
  __int64* q{ nullptr };
  int* m{ nullptr };

  p = new int;
  if (p == nullptr) return -1;
  *p = 0x11223344;

  q = new __int64;
  if (q == nullptr) return -1;
  *q = 0x1122334455667788;

  m = new int;
  if (m == nullptr) return -1;
  *m = 0x11223344

  delete q;
  q = nullptr;
  delete m;
  m = nullptr;
  delete p;
  p = nullptr
}