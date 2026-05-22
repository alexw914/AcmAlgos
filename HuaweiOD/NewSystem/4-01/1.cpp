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

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int M, N;
  char choma;
  cin >> M >> choma >> N;

  vector<int> array(M, 0);
  for (int i = 0; i < M; i++) {
    array[i] = i+1;
  }

  while (array.size() < N) {
    int start = array.size() - M;
    int maxVal = *max_element(array.begin() + start, array.end());
    int minVal = *min_element(array.begin() + start, array.end());
    // 判断前M个元素中是否存在值相同的元素
    set<int> unique(array.begin() + start, array.end());
    if (unique.size() < M) {
      array.push_back(maxVal + minVal);
    } else {
      array.push_back(maxVal - minVal);
    }
  }

  cout << array[N -1] << endl;
  return 0;
}
