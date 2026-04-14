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

int main() {
    Base* b = new Derived();
    b->show(); // 输出：Derived class show
    delete b;
    return 0;
}