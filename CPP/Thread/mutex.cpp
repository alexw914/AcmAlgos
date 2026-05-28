//
// Created by 巫妖王 on 2026/5/21.
//

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <shared_mutex>
#include <atomic>
#include <chrono>
#include <vector>

using namespace std;

// 共享资源
int shared_data = 0;

// 互斥锁
std::mutex mtx;

// 读写锁（C++17）
std::shared_mutex rwlock;

// 自旋锁
std::atomic_flag spinlock = ATOMIC_FLAG_INIT;

// 模拟耗时读操作
void read_data_mutex(int id) {
    std::lock_guard<std::mutex> lock(mtx); // 普通互斥锁
    cout << "[Mutex] Reader " << id << " reads: " << shared_data << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

void write_data_mutex(int id) {
    std::lock_guard<std::mutex> lock(mtx); // 普通互斥锁
    shared_data += 1;
    cout << "[Mutex] Writer " << id << " writes: " << shared_data << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

// 使用读写锁
void read_data_rwlock(int id) {
    std::shared_lock<std::shared_mutex> lock(rwlock); // 共享锁（读）
    cout << "[RWLock] Reader " << id << " reads: " << shared_data << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

void write_data_rwlock(int id) {
    std::unique_lock<std::shared_mutex> lock(rwlock); // 独占锁（写）
    shared_data += 1;
    cout << "[RWLock] Writer " << id << " writes: " << shared_data << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

// 使用自旋锁，atomic变量实现
void read_data_spin(int id) {
    while (spinlock.test_and_set(std::memory_order_acquire)) { /* busy wait */ }
    cout << "[Spinlock] Reader " << id << " reads: " << shared_data << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    spinlock.clear(std::memory_order_release);
}

void write_data_spin(int id) {
    while (spinlock.test_and_set(std::memory_order_acquire)) { /* busy wait */ }
    shared_data += 1;
    cout << "[Spinlock] Writer " << id << " writes: " << shared_data << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    spinlock.clear(std::memory_order_release);
}

int main() {
    cout << "=== Mutex Example ===" << endl;
    shared_data = 0;
    vector<thread> threads;

    for (int i = 0; i < 3; ++i)
        threads.emplace_back(read_data_mutex, i);
    for (int i = 0; i < 2; ++i)
        threads.emplace_back(write_data_mutex, i);
    for (auto& t : threads) t.join();

    cout << "\n=== RWLock Example ===" << endl;
    threads.clear();
    shared_data = 0;

    for (int i = 0; i < 3; ++i)
        threads.emplace_back(read_data_rwlock, i);
    for (int i = 0; i < 2; ++i)
        threads.emplace_back(write_data_rwlock, i);
    for (auto& t : threads) t.join();

    cout << "\n=== Spinlock Example ===" << endl;
    threads.clear();
    shared_data = 0;
    spinlock.clear(); // 确保锁初始为释放状态

    for (int i = 0; i < 3; ++i)
        threads.emplace_back(read_data_spin, i);
    for (int i = 0; i < 2; ++i)
        threads.emplace_back(write_data_spin, i);
    for (auto& t : threads) t.join();

    return 0;
}