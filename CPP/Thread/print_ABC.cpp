//
// Created by Krisw on 2026/4/14.
//

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

int g_turn = 0;                // 0 -> A, 1 -> B, 2 -> C
int g_step = 0;                // 已打印多少次字符
int g_loop_time = 10;          // 打印多少轮 ABC
int g_total_step = 3 * g_loop_time;

std::mutex g_mutex;
std::condition_variable g_cv;

void print_task(int my_turn, const char* str) {
    while (true) {
        std::unique_lock<std::mutex> lock(g_mutex);

        g_cv.wait(lock, [my_turn]() {
            return g_turn == my_turn || g_step >= g_total_step;
        });

        if (g_step >= g_total_step) {
            g_cv.notify_all();
            return;
        }

        std::cout << str;

        ++g_step;
        g_turn = (g_turn + 1) % 3;

        g_cv.notify_all();
    }
}

int main() {
    std::thread t1(print_task, 0, "A");
    std::thread t2(print_task, 1, "B");
    std::thread t3(print_task, 2, "C");

    t1.join();
    t2.join();
    t3.join();

    std::cout << std::endl;
    return 0;
}