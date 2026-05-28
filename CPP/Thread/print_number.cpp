//
// Created by Krisw on 2026/4/14.
//

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <vector>

int g_current = 0; // 当前要打印的数字
int g_max_num = 100; // 最大打印值
int g_thread_cnt = 3; // 线程数

std::mutex g_mutex;
std::condition_variable g_cv;

void print_task(int thread_id) {
    while (true) {
        std::unique_lock<std::mutex> lock(g_mutex);

        g_cv.wait(lock, [thread_id]() {
            return g_current > g_max_num ||
                   (g_current % g_thread_cnt == thread_id);
        });

        if (g_current > g_max_num) {
            g_cv.notify_all();
            return;
        }

        std::cout << "thread " << thread_id << " print: " << g_current << std::endl;

        ++g_current;
        g_cv.notify_all();
    }
}

int main() {

    std::vector<std::thread> threads;
    for (int i = 0; i < g_thread_cnt; ++i) {
        threads.emplace_back(print_task, i);
    }

    for (auto &t: threads) {
        t.join();
    }

    return 0;
}
