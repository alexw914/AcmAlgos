//
// Created by Krisw on 2026/1/2.
//

/*
在图像处理中，坏点(异常值)会影响后续分析，需进行矫正。本题要求对3x3矩阵的中心元素进行坏点检测与矫正，规则如下

1.坏点判断依据：

计算中心元素（位置1，1）与周围8个元素的均值的差值绝对值 diff = |中心元素 - 周围均值|。

2.矫正规则:

若diff>50:用周围均值(周围8个元素的平均值,四舍五入取整数）替代中心元素

若30<=diff<=50:用3x3矩阵的整体均值(9个元素的平均取整数)替代中心元素;值，四舍五入取整数)替代中心元素;

若diff<30:中心元素不变。

3.输出:矫正后的3x3矩阵(每行元素用空格分隔)。

输入描述：

输入共3行，每行3个整数(取值范围0-255)，表示3x3矩阵(每行元素用空格分隔)。

输入描述

输入共3行，表示矫正后的3x3矩阵(每行元素用空格分隔)

示例1

输入：

10 10 10
10 200 10
10 10 10

输出：

10 10 10
10 10 10
10 10 10

示例2

输入：

100 100 100
100 140 100
100 100 100

输出：

100 100 100
100 104 100
100 100 100
*/

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);


    vector<vector<int> > grid(3, vector<int>(3, 0));
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> grid[i][j];
            if (!(i == 1 && j == 1)) {
                sum += grid[i][j];
            }
        }
    }
    // 满足四舍五入需要除以float,整型会直接截断
    int diff = abs(grid[1][1] - round(sum / 8.0));
    if (diff >= 30 && diff <= 50) grid[1][1] = round((sum + grid[1][1]) / 9.0);
    if (diff > 50) grid[1][1] = round(sum / 8.0);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << grid[i][j];
            if (j != 2 ) cout << " ";
        }
        cout << endl;
    }

    return 0;
}