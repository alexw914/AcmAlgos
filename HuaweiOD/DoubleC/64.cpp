//
// Created by Krisw on 2026/1/2.
//

/*
现有一个机器人，可放置于M×N的网格中任意位置，
每个网格包含一个非负整数编号，
当相邻网格的数字编号差值的绝对值小于等于1时，机器人可以在网格间移动
问题：求机器人可活动的最大范围对应的网格点数目。说明：
.网格左上角坐标为(0,0),右下角坐标为(m−1,n−1)
.机器人只能在相邻网格间上下左右移动
输入描述
第1行输入为M和N，M表示网格的行数N表示网格的列数之后M行表示网格数值，每行N个数值（数值大小用k表示），
数值间用单个空格分隔，行首行尾无多余空格M、N、k均为整数，且1≤M,N≤150，0≤k≤50
输出描述
输出1行，包含1个数字，表示最大活动区域的网格点数目行首行尾无多余空格
示例一
输入

4 4
1 2 5 2
2 4 4 5
3 5 7 1
4 6 2 4
输出

6

示例二
输入

2 3
1 3 5
4 1 3
输出

1
*/

#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

int m, n;
vector<vector<int> > grid;

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

int dfs(vector<vector<int>>& vis, int x, int y) {
    vis[x][y] = 1;
    int cnt = 1; // 当前格子也算一个
    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < m && ny >= 0 && ny < n &&
            !vis[nx][ny] && abs(grid[nx][ny] - grid[x][y]) <= 1) {
            cnt += dfs(vis, nx, ny);
            }
    }
    return cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m >> n;

    grid.assign(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    int ans = 1;
    vector<vector<int> > vis(m, vector<int>(n, 0));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!vis[i][j]) {
                int area = dfs(vis, i, j);
                ans = max(ans, area);
            }
        }
    }
    cout << ans << endl;

    return 0;
}
