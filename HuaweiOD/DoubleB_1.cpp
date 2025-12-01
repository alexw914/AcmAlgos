//
// Created by Krisw on 2025/11/29.
//

/*
题目描述:
给定一个 m xn 的矩阵，由若干字符  和0构成，X表示该处已被占据，0"表示该处空闲，请找到最大的单入口空闲区域.
解释:
空闲区域是由连通的O组成的区域，位于边界的0可以构成入口，单入口空闲区域即有目只有一个位于边界的0作为入口的由
连通的'O"组成的区域。如果两个元素在水平或垂直方向相邻，则称它们是“连通”的。

输入描述:
第一行输入为两个数字，第一个数字为行数m，第二个数字列数n，两个数字以空格分隔，1 <= m,n <= 200,剩余各行为矩
阵各行元素，元素为'X' 或O，各元素间以空格分隔。
输出描述
若有唯一符合要求的最大单入口空闲区域，输出三个数字，第一个数字为入口行坐标(范围为0-行数-1)，第二个数字为入口列坐标(范围为0~列数-1)，
第三个数字为区域大小，三个数字以空格分隔;若有多个符合要求的最大单入口空闲区域，输出一个数字，代表区域的大小;若没有，输出NULL。

示例1
输入:
4 4
X X X X
X O O X
X O O X
X O X X
输出:
3 15
说明:
存在最大单入口区域，入口行坐标3，列坐标1，区域大小5

示例2
输入:
4 5
X X X X X
O O O O X
X O O O X
X O X X O
输出:
3 4 1
说明:
存在最大单入口区域，入口行坐标3，列坐标4，区域大小1

示例3
输入:

输出:
NULL
说明:
不存在最大单入口区域

示例4
输入:
5 4
X X X X
X O O O
X X X X
X O O O
X X X X
输出:
3
说明:
存在两个大小为3的最大单入口区域，两个入口横纵坐标分别为1,3和3,3
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N;
    if (!(cin >> M >> N)) return 0;

    vector<vector<char>> matrix(M, vector<char>(N));
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            cin >> matrix[i][j];
        }
    }

    struct Info {
        int in_x, in_y;
        int area;
    };

    vector<vector<bool>> vis(M, vector<bool>(N, false));
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};

    std::vector<Info> infos;
    int maxArea = 0;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (matrix[i][j] == 'O' && !vis[i][j]) {
                queue<pair<int, int>> q;
                q.push({i, j});
                vis[i][j] = true;
                int sub_area = 0;
                int entranceIn_x, entranceIn_y;
                int entranceNum = 0;
                while (!q.empty()) {
                    auto [x, y] = q.front();
                    q.pop();
                    sub_area++;
                    if (x == 0 || x == M - 1 || y == 0 || y == N - 1) {
                        entranceNum++;
                        if (entranceNum == 1) {
                            entranceIn_x = x;
                            entranceIn_y = y;
                        }
                    }
                    for (int k = 0; k < 4; k++) {
                        int nx = x + dx[k];
                        int ny = y + dy[k];
                        if (nx >= 0 && nx < M && ny >= 0 && ny < N && matrix[nx][ny] == 'O' && !vis[nx][ny]) {
                            vis[nx][ny] = true;
                            q.push({nx, ny});
                        }
                    }
                }
                if (entranceNum == 1) {
                    infos.push_back({entranceIn_x, entranceIn_y, sub_area});
                    if (sub_area > maxArea) { maxArea = sub_area; }
                }
            }
        }
    }
    if (infos.empty()) {
        cout << "NULL" << endl;
        return 0;
    }

    int maxNum = 0;
    Info best = {0, 0 , 0};
    for (auto& info : infos) {
        if (info.area == maxArea) {
            maxNum++;
            best = info;
        }
    }

    if (maxNum == 1) {
        cout << best.in_x << " " << best.in_y << " " << best.area << "\n";
    } else {
        cout << maxNum << "\n";
    }

    return 0;
}