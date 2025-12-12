//
// Created by Krisw on 2025/12/12.
//

/*
2XXX年，人类通过对火星的大气进行宜居改造分析，使得火星已在理论上具备人类宜居的条件，由于技术原因，无法一次性将火星大气全部改造，
只能通过局部处理形式，假设将火星待改造的区域为row * column的网格每个网格有3个值，宜居区、可改造区、死亡区，使用YES、NO、NA代替，
YES表示该网格已经完成大气改造，NO表示该网格未进行改造，后期可进行改造，NA表示死亡区，不作为判断是否改造完成的宜居，无法穿过
初始化下，该区域可能存在多个宜居区，并且每个宜居区能同时在每个太阳日单位向上下左右四个方向的相邻格子进行扩散，
自动将4个方向相邻的真空区改造成宜居区;请计算这个待改造区域的网格中，可改造区是否能全部变成宜居区，
如果可以，则返回改造的太阳日天数，不可以则返回-1。

输入描述:
输入row*column个网格数据，每个网格值枚举值如下: YES，NO，NA，样例:
YES YES NO
NO NO NO
NA NO YES
输出描述:
可改造区是否能全部变成宜居区，如果可以，则返回改造的太阳日天数，不可以则返回-1.
补充说明:
grid[i]只有3种情况，YES、NO、NA
row == grid.length, column == grid[i].length, 1 <= row, column <= 8

示例1
输入:
YES YES NO
NO NO NO
YES NO NO

输出:

2
说明:
经过2个太阳日，完成宜居改造.

示例2
输入:
YES NO NO NO
NO NO NO NO
NO NO NO NO
NO NO NO NO
输出:

6
说明:
经过6个太阳日，可完成改造


示例3
输入:

NO NA
输出:

-1

说明:
无改造初始条件，无法进行改造


示例4
输入:
YES NO NO YES

NO NO YES NO

NO YES NA NA

YES NO NA NO
输出:

-1
说明:

右下角的区域，被周边三个死亡区挡住，无法实现改造
 */
#include <bits/stdc++.h>
using namespace std;

int day = 0;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<vector<int> > graph;
    string line;

    map<string, int> keyMap = {
        {"YES", 0},
        {"NO", 1},
        {"NA", 2},
    };

    while (getline(cin, line)) {
        if (line.empty()) break;
        stringstream ss(line);
        string key;
        vector<int> v;
        while (ss >> key) {
            v.push_back(keyMap[key]);
        }
        graph.push_back(v);
    }

    int M = graph.size();
    int N = graph[0].size();

    queue<pair<int, int> > q;
    int need = 0;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (graph[i][j] == 0) {
                q.push(make_pair(i, j));
            } else if (graph[i][j] == 1) {
                need += 1;
            }
        }
    }


    if (need == 0) {
        cout << 0 << endl;
        return 0;
    }
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};

    int days = -1;
    while (!q.empty()) {
        int size = q.size();
        while (size--) {
            auto [x,y] = q.front();
            q.pop();
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (nx >= 0 && nx < M && ny >= 0 && ny < N && graph[nx][ny] == 1) {
                    q.push(make_pair(nx, ny));
                    graph[nx][ny] = 0;
                    need--;
                }
            }
        }
        days++;
    }

    cout << (need == 0 ? days : -1) << "\n";

    return 0;
}
