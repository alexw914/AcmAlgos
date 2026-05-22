//
// Created by 巫妖王 on 2026/5/21.
//

#include <atomic>
#include <iostream>
#include <shared_mutex>
#include <thread>

std::atomic cnt = 0;
int cnt_normal = 0;
int cnt_other = 0;
std::mutex m;

int main() {

  auto worker = [&]() {
    for (int i = 0; i < 1000; i++) {
      cnt++;
      cnt_normal++;
    }
  };

  auto worker2 = [&]() {
    for (int i = 0; i < 1000; i++) {
      std::lock_guard lock(m);
      cnt_other++;
    }
  };

  std::vector<std::thread> threads;
  for (int i = 0; i < 3; ++i) {
    threads.emplace_back(worker);
    threads.emplace_back(worker2);
  }

  for (auto &t : threads)
    t.join();

  std::cout << cnt << std::endl;
  std::cout << cnt_normal << std::endl;

  std::cout << cnt_other << std::endl;

  return 0;
}