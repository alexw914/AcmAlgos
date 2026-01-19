//
// Created by Krisw on 2026/1/15.
//

/*
评估一个网络的 信号质量，其中一个做法是将网络划分为栅格，然后对每个栅格的信号质量计算。路测的时候，希望选择一条信号最好的路线(彼此相连的栅格集合)进行演示。
现给出 R行 C 列的整数数组 Cov 。每个单元格的数值 S 即为该栅格的信号质量(已归一化，无单位,值越大信号越好)。要求从[0,0]到[R - 1,C - 1] 。设计一条最优路测路线。返回该路线得分
规则:
1.路测路线可以 上下左右四个方向，不能对角
2.路线的评分是以路线上信号最差的栅格为准的。例如路径 8 -> 4 -> 5 -> 9 的值为 4，该线路评分为 4。线路最优表示该条线路的评分最高。


输入描述
第一行表示栅格的行数 R;
第二行表示栅格的列数 C:
第三行开始，每一行表示栅格地图一行的信号值，每个单元格的数值为 S
1< R, C < 20
1 < S < 65535
输出描述
最优路线的得分


示例1：

输入：

3
3
5 4 5
1 2 6
7 4 6

输出：

4

说明：

路线为: 5->4->5->6->6。


示例2：

输入：

6
5
3 4 6 3 4
0 2 1 1 7
8 8 3 2 7
3 2 4 9 8
4 1 2 0 0
4 6 5 4 3

输出：

3

说明：

路线为: 3->4->6->3->4->7->7->8->9->4->3->8->8->3->4->4->6->5->4->3
*/

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int R, C;
    cin >> R >> C;

    vector<vector<int>> cov(R, vector<int>(C));
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            cin >> cov[i][j];

    vector<vector<int>> best(R, vector<int>(C, -1));

    // 最大堆: (路径评分, r, c)
    priority_queue<tuple<int,int,int>> pq;

    best[0][0] = cov[0][0];
    pq.push({best[0][0], 0, 0});

    int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

    while (!pq.empty()) {
        auto [score, x, y] = pq.top();
        pq.pop();

        // 剪枝
        if (score < best[x][y]) continue;

        if (x == R-1 && y == C-1) {
            cout << score << "\n";
            return 0;
        }

        for (auto &d : dirs) {
            int nx = x + d[0];
            int ny = y + d[1];

            if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue;

            int candidate = min(score, cov[nx][ny]);

            if (candidate > best[nx][ny]) {
                best[nx][ny] = candidate;
                pq.push({candidate, nx, ny});
            }
        }
    }

    // 理论上一定能到达
    cout << best[R-1][C-1] << "\n";
    return 0;
}
