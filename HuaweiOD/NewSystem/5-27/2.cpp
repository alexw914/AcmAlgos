#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
  int longestValidSkillChain(vector<int> &type) {
    if (type.empty())
      return 0; // 不写某个测试案例会崩溃,提交错误
    const int N = type.size();
    vector<int> dp(N, 0);
    int maxLen = 0;
    if (type[0] == 0) {
      dp[0] = 1;
      maxLen = 1;
    }
    for (int i = 1; i < N; i++) {
      if (type[i] == 0) {
        dp[i] = dp[i - 1] + 1;
      } else if (type[i] == 1) {
        if (type[i - 1] == 0) {
          dp[i] = dp[i - 1] + 1;
        } else {
          dp[i] = 0;
        }
      } else if (type[i] == 2) {
        if (i >= 2 && type[i - 1] == 0 && type[i - 2] == 0) {
          dp[i] = dp[i - 1] + 1;
        } else {
          dp[i] = 0;
        }
      }
      maxLen = max(maxLen, dp[i]);
    }
    return maxLen;
  }
};

int main() {
  auto solution = Solution();
  vector<int> type = {0, 1, 0, 0, 2};
  cout << solution.longestValidSkillChain(type) << endl;
}