//
// Created by Krisw on 2026/3/20.
//

#include <iostream>
#include <sstream>
using namespace std;

// 结构体内存对齐问题

struct __tt__ {
    char a;
    int b;
    long c;
    short d;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    __tt__ t;
    __tt__* p = 0;

    printf("%d\n", sizeof(long));
    printf("%d\n", sizeof(t));
    printf("%d\n", sizeof(p));

    p += 1;
    printf("%d\n", p);

    return 0;
}