//
// Created by Krisw on 2026/4/11.
//

#include <iostream>
using namespace std;

class Base {
public:
    virtual void show() {
        cout << "Base class show" << endl;
    }
};

class Derived : public Base {
public:
    void show() override {
        cout << "Derived class show" << endl;
    }
};

class Base2 {
public:
    void show() {
        cout << "Base2 class show" << endl;
    }
    short a;
    int b;
};

int main() {
    Base* b = new Derived();
    b->show(); // 输出：Derived class show
    delete b;
    Base2 b2;
    printf("%d\n", sizeof(Base2));
    printf("%d\n", sizeof(short));
    printf("%d\n", sizeof(b2));
    printf("%d\n", b2);
    return 0;
}