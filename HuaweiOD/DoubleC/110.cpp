//
// Created by Krisw on 2026/1/16.
//

/*
小明在玩连连看游戏，目标是消除相同的数字，游戏规定：

两个位置必须数字相同才能消除
连接路径只能经过空格
连接路径最多只能有两次拐弯
连接线路可以走地图的边界
消除后位置变为空格("")
第一行输入一个数组代表连连看的地图矩阵，形式类似于: [[4,5,4] [5,4,5]] ，第一行输入n，表示操作步骤数，
接下来r行，每行输入四个数字 y1 x1 y2 x2 代表此次操作的两个位置。题目要求判断按照操作步骤执行，是否每一步都能进行消除，可以的话输出 OK,否则输出 NO。
输入描述
第一行输入 一个字符串，代表 连连看的地图。
第二行输出一个 n，代表操作步骤数
接下来的n行，每一行输入y1 x1 y2 x2 代表此次操作的两个表格位置
备注
不必考虑输入不合法的情况
输出描述
输入步骤能全部正常消除则输出 OK 。否则输出 NO

示例1：

输入：

[[4,5,4],[5,4,5]]
2
0 0 2 0
1 0 0 1

输出：

OK

说明：

位置（0，0）到位置（0，2）上，都是4，可以消除

位置（0，1）到位置（1，0）上，都是5，可以消除
*/

#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

struct State {
    int r, c;      // 行列
    int dir;       // 0~3
    int turns;     // 已拐弯次数
};

static const int dr[4] = {-1, 1, 0, 0};
static const int dc[4] = {0, 0, -1, 1};

// 解析形如 [[4,5,4],[5,4,5]] 的矩阵为 vector<vector<string>>
// 空格不出现于输入；数字为正整数（按题意）。消除后我们用 "" 表示空格。
vector<vector<string>> parseGrid(const string& s) {
    vector<vector<string>> grid;
    vector<string> row;
    string num;
    bool inNum = false;
    for (char ch : s) {
        if (isdigit((unsigned char)ch)) {
            num.push_back(ch);
            inNum = true;
        } else {
            if (inNum) {
                row.push_back(num);
                num.clear();
                inNum = false;
            }
            if (ch == ']') {
                if (!row.empty()) {
                    grid.push_back(row);
                    row.clear();
                }
            }
        }
    }
    return grid;
}

bool canEliminate(const vector<vector<string>>& g0, int y1, int x1, int y2, int x2) {
    int H = g0.size();
    int W = g0[0].size();

    // 四周加一圈空格，允许走边界外侧
    vector<vector<string>> g(H + 2, vector<string>(W + 2, ""));
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            g[i + 1][j + 1] = g0[i][j];

    // 坐标平移到新棋盘
    y1++; x1++; y2++; x2++;

    // visited[r][c][dir][turns]
    static bool vis[55][55][4][3] = {};

    queue<State> q;

    // 从起点出发：可以朝任意方向开始，拐弯次数为0
    for (int d = 0; d < 4; d++) {
        vis[y1][x1][d][0] = true;
        q.push({y1, x1, d, 0});
    }

    while (!q.empty()) {
        auto cur = q.front(); q.pop();

        int nr = cur.r + dr[cur.dir];
        int nc = cur.c + dc[cur.dir];

        if (nr < 0 || nr >= H + 2 || nc < 0 || nc >= W + 2) continue;

        // 只能经过空格；终点允许不是空格（因为终点是目标数字）
        if (!(nr == y2 && nc == x2) && g[nr][nc] != "") continue;

        // 到达终点
        if (nr == y2 && nc == x2) return true;

        // 在(nr,nc)这个空格处，可以继续选择方向（直走不加拐弯，换向+1）
        for (int nd = 0; nd < 4; nd++) {
            int nt = cur.turns + (nd != cur.dir);
            if (nt > 2) continue;
            if (!vis[nr][nc][nd][nt]) {
                vis[nr][nc][nd][nt] = true;
                q.push({nr, nc, nd, nt});
            }
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    getline(cin, line);
    auto grid = parseGrid(line);

    int n;
    cin >> n;

    for (int k = 0; k < n; k++) {
        int y1, x1, y2, x2;
        cin >> y1 >> x1 >> y2 >> x2;
        
        if (grid[y1][x1] != grid[y2][x2]) {
            cout << "NO\n";
            return 0;
        }

        if (!canEliminate(grid, y1, x1, y2, x2)) {
            cout << "NO\n";
            return 0;
        }

        // 消除
        grid[y1][x1].clear();
        grid[y2][x2].clear();
    }

    cout << "OK\n";
    return 0;
}
