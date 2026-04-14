//
// Created by Krisw on 2026/3/22.
//

#include <iostream>

// 饿汉模式->类外定义
class HungrySingleton
{
public:
    // 禁用拷贝构造和移动构造
    HungrySingleton(const HungrySingleton& t) = delete;
    HungrySingleton& operator=(const HungrySingleton& t) = delete;
    static HungrySingleton* getInstance() { return m_instance; };
    void print() { std::cout << "This is a hungry singlelaton instance." << std::endl; }

private:
    // 构造函数私有
    HungrySingleton() = default;
    // 只能通过类名访问静态属性或方法,类外定义静态成员
    static HungrySingleton* m_instance;
};
HungrySingleton* HungrySingleton::m_instance = new HungrySingleton;

// 懒汉模式->静态局部对象,C++11特性
class LazySingleton
{
public:
    LazySingleton(const LazySingleton& t) = delete;
    LazySingleton& operator=(const LazySingleton& t) = delete;
    static LazySingleton* getInstance() {
        static LazySingleton ins;
        return &ins;
    }
    void print() { std::cout << "This is a lazy singlelaton instance." << std::endl; }

private:
    LazySingleton() = default;
};


int main() {
    auto hungry_singleton = HungrySingleton::getInstance();
    hungry_singleton->print();
    auto lazy_singleton = LazySingleton::getInstance();
    lazy_singleton->print();
    return 0;
}