//
// Created by Krisw on 2025/11/30.
//

/*
题目描述

存在一个mxn的二维数组，其成员取值范围为0或1，其中值为1的成员具备扩散性，每经过1S，将上下左右值为0的成员同化为1，
二维数组的成员初始值都为0，将第[i,j]和[k,l]两个个位置上元素修改成1后，求矩阵的所有，元素变为1需要多长时间

输入描述

输入数据中的前2个数字表示这是一个mxn的矩阵，m和n不会超过1024大小;

中间两个数字表示一个初始扩散点位置为I,j

最后2个数字表示另一个扩散点位置为k,l

输出描述

输出矩阵的所有元素变为1所需要秒数

示例1：

输入：

4,4,0,0,3,3

输出：

3

说明：

输入数据中的前2个数字表示这是一个4*4的矩阵；

中间两个数字表示一个初始扩散点位置为0,0；

最后2个数字表示另一个扩散点位置为3,3。

给出的样例是一个简单模型，初始点在对角线上，达到中间的位置分别为3次迭代，即3秒。所以输出为3。
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n, x1, y1, x2, y2;
    scanf("%d,%d,%d,%d,%d,%d", &m, &n, &x1, &y1, &x2, &y2);

    vector<vector<int>> matrix(m, vector<int>(n, 0));
    matrix[x1][y1] = 1;
    matrix[x2][y2] = 1;

    queue<pair<int, int>> q;
    q.push({x1, y1});
    q.push({x2, y2});

    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};

    int ans = -1;
    while (!q.empty()) {
        int sz = q.size();
        while (sz--) {
            auto [x, y] = q.front();
            q.pop();
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && matrix[nx][ny] == 0) {
                    matrix[nx][ny] = 1;
                    q.push({nx, ny});
                }
            }
        }
        ans++;
    }
    cout << ans << endl;
    return 0;
}