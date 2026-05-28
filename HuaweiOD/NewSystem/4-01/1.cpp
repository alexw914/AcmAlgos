//
// Created by 巫妖王 on 2026/5/21.
//

/*
1、输入M、N两个数，则按照以下规则形成一个数列;
2、数列的前M个元素的值为1到M;
3、从M+1个元素开始，计算的逻辑为:
如果其前面的M个元素中，存在值相同的元素，则该位置上的数值等于前面M个数中最大的数值与最小的数值之如果其前面的M个元素中，不存在值相同的元素，则该位置上的数值等于前面M个数中最大的数值与最小的数值之差;
请计算该数列第N个位置上的数值
补充说明
M取值范围:3<=M<=10
N取值范围:1<=N<=50

输入描述

两个整数，用逗号分割，分别表示M和N

输出描述

一个整数，表示数列第N个位置上的数值
示例1
输入

5,1

输出

1
 */

#include <iostream>
#include <map>
#include <sstream>
#include <set>
#include <algorithm>
using namespace std;

class Solution {
public:
  int getNthValue(int M, int N) {
    vector<int> arr;
    for (int i = 1; i <= M; i++) arr.push_back(i);
    if (N < M) return arr[N-1];
    int k = 0;
    while(arr.size() < N) {
      int max_num = INT_MIN, min_num = INT_MAX;
      bool has_same = false;
      set<int> st;
      for (int i = k; i < k + M; i++) {
        max_num = max(max_num, arr[i]);
        min_num = min(min_num, arr[i]);
        if (st.count(arr[i])) { has_same = true; }
        else { st.insert(arr[i]);};
      }
      if (has_same) {
        arr.push_back(max_num + min_num);
      } else {arr.push_back(max_num - min_num);};
      k++;
    }
    cout << endl;
    return arr[N-1];
  }
};


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  auto solution = Solution();
  cout << solution.getNthValue(5, 8) << endl;
  return 0;
}
