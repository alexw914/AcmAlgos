//
// Created by 巫妖王 on 2026/5/22.
//

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
  int equalDistanceBinary(int n) {
    vector<int> idxs;
    int idx = 0;
    while (n) {
      if (n & 1) {
        idxs.push_back(idx);
      }
      idx++;
      n >>= 1;
    }
    if (idxs.size() < 3)
      return -1;
    int dist = idxs[1] - idxs[0] - 1;
    for (int i = 2; i < idxs.size(); i++) {
      if (dist != idxs[i] - idxs[i - 1] - 1)
        return -1;
    }
    return dist;
  }
};

int main() {
  auto solution = Solution();
  vector<int> samples = {21, 60, 146, 2};
  for (auto sample : samples) {
    cout << solution.equalDistanceBinary(sample) << " ";
  }
  cout << endl;
  return 0;
}
