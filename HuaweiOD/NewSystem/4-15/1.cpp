//
// Created by 巫妖王 on 2026/5/28.
//

/*

 */

#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

class Solution {
  int transInt(char c) {
    if (c >= '0' && c <= '9') {
      return c - '0';
    }
    else if (c >= 'a' && c <= 'z') {
      return c - 'a' + 10;
    }
    return 0;
  }


public:
  vector<vector<int>> countKeys(string s) {
    vector<vector<int>> ans;
    const int N = s.length();
    int i = 0;
    string s_raw;
    map<int, int> mp;
    while(i < N) {
      if (i < N - 1 && (s[i] == 'u' || s[i] == 't') && s[i] == s[i+1] ) {
        if (s[i] == 'u') {
          s_raw.push_back('j');
        } else if (s[i] == 't') {
          s_raw.push_back('b');
        }
        i = i + 2;
      }
      else {
        s_raw.push_back(s[i]);
        i =  i + 1;
      }
      mp[transInt(s[i])]++;
    }

    for (auto& [k, v] : mp) {
      ans.push_back({k, v});
    }
    sort(ans.begin(), ans.end(), [](vector<int>&a, vector<int>& b){
      if (a[1] != b[1]) { return a[1] > b[1]; }             // 次数降序
      return a[0] < b[0];             // key升序
    });

    return ans;
  }
};

int main() {
  auto solution = new Solution();
  solution->countKeys("abcd");
  for (auto& row : solution->countKeys("abcd")) {
    cout << "[";
    for (auto& val : row) {
      cout << val << ",";
    }
    cout << "],";
  }
  return 0;
}
