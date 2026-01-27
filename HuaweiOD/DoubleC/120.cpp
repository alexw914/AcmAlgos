//
// Created by Krisw on 2026/1/18.
//

/*
某长方形停车场，每个车位上方都有对应监控器，当且仅当在当前车位或者前后左右四个方向任意一个车位范围停车时，监控器才需要打开:
给出某一时刻停车场的停车分布，请统计最少需要打开多少个监控器
输入描述
第一行输入m，n表示长宽，满足1 < m,n <= 20;
后面输入m行，每行有n个0或1的整数，整数间使用一个空格隔开，表示该行已停车情况，其中0表示空位，1表示已停:
输出描述
最少需要打开监控器的数量
示例1：

输入
3 3
0 0 0
0 1 0
0 0 0
输出
5
说明

中间1的位置上需要打开监视器，且其上下左右皆需要打开监视器，共5个。
*/

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int m, n;
vector<vector<int> > g;
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

void expand(vector<vector<int> > &need, int x, int y) {
    for (int i = 0; i < 4; i++) {
        auto nx = x + dx[i], ny = y + dy[i];
        if (nx >= 0 & nx < m && ny >= 0 && ny < m && !need[nx][ny]) {
            need[nx][ny] = 1;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m >> n;
    vector<vector<int> > g(m, vector<int>(n));
    vector<pair<int, int> > car_pos;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> g[i][j];
            if (g[i][j]) car_pos.push_back({i, j});
        }
    }

    for (auto &p: car_pos) {
        expand(g, p.first, p.second);
    }

    int cnt = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (g[i][j]) cnt++;
        }
    }
    cout << cnt << endl;
    return 0;
}
