//
// Created by 巫妖王 on 2026/5/18.
//

#include <cstdio>
#include <cstring>
#include <iterator>
int a[100];

template <typename T> T endian_swap(T val) {
  T ret = 0;
  for (size_t i = 0; i < sizeof(T); i++) {
    ret |= ((val >> (i * 8)) & 0xFF) << ((sizeof(T) - 1 - i) * 8);
  }
  return ret;
}

int main() {
  printf("%d\n", sizeof(a));
  printf("%d\n", sizeof(a[0]));
  memset(a, 1, sizeof(a));
  /*
  按字节设置
  |11111111|11111111|11111111|11111111|
   */
  printf("%d\n", a[0]);
  endian_swap(a[0]);
  printf("%d\n", a[0]);
  return 0;
}