//
// Created by Krisw on 2025/12/12.
//

/*
绘图机器的绘图笔初始位置在原点(0,0)机器启动后按照以下规则来进行绘制直线。

1. 尝试沿着横线坐标正向绘制直线直到给定的终点E

2. 期间可以通过指令在纵坐标轴方向进行偏移，offsetY为正数表示正向偏移,为负数表示负向偏移

给定的横坐标终点值E 以及若干条绘制指令，

请计算绘制的直线和横坐标轴以及x=E的直线组成的图形面积。

输入描述

首行为两个整数 N 和 E
表示有N条指令,机器运行的横坐标终点值E
接下来N行 每行两个整数表示一条绘制指令x offsetY
用例保证横坐标x以递增排序的方式出现
且不会出现相同横坐标x
取值范围

0<N<=10000
0<=x<=E<=20000
-10000<=offsetY<=10000
输出描述

一个整数表示计算得到的面积 用例保证结果范围在0到4294967295之内。
示例1   输入输出示例仅供调试，后台判题数据一般不包含示例

输入

4 10

1 1

2 1

3 1

4 -2

输出

12

示例2   输入输出示例仅供调试，后台判题数据一般不包含示例

输入

2 4

0 1

2 -2

输出

4
*/

#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, E;
    cin >> N >> E;
    vector<pair<int, int> > coords;

    coords.push_back({0, 0});
    int y = 0;
    while (N--) {
        int x, offsetY;
        cin >> x >> offsetY;
        y += offsetY;
        coords.push_back({x, y});
    }
    coords.push_back(make_pair(E, y)); // 开头和末尾各加一个进行计算

    LL area = 0;
    int n = coords.size();
    for (int i = 0; i < n; i++) {
        int height = coords[i].second;
        int width = coords[i + 1].first - coords[i].first;
        if (width > 0) area += 1LL * llabs(height) * width; // 强制转换成long long计算
    }

    cout << area << "\n";

    return 0;
}

/*
int main() {
    // 读取输入的 N 和 E
    int N, E;
    cin >> N >> E;

    // 初始化图形总面积
    long long totalArea = 0;
    // 绘图笔位置 (x, y)
    int x = 0, y = 0;

    // 读取命令并存储在数组中
    for (int i = 0; i < N; i++) {
        int curX, offsetY;
        cin >> curX >> offsetY;

        // 累计当前边和前一条边组成的面积
        totalArea += 1LL * (curX - x) * abs(y);

        // 更新绘图笔位置
        x = curX;
        y += offsetY;
    }

    // 计算最后一条边组成的面积
    totalArea += 1LL * (E - x) * abs(y);

    // 输出结果
    cout << totalArea << endl;

    return 0;
}
*/