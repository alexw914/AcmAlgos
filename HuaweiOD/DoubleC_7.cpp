//
// Created by Krisw on 2025/12/8.
//

/*
竖直四子棋的棋盘是竖立起来的，双方轮流选择棋盘的一列下子，棋子因重力落到棋盘底部或者其他棋子之上，当一列的棋子放满时，无法再在这列上下子。

一方的4个棋子横、竖或者斜方向连成一线时获胜。

现给定一个棋盘和红蓝对弈双方的下子步骤，判断红方或蓝方是否在某一步获胜。

下面以一个6×5的棋盘图示说明落子过程：

输入描述

输入为2行，第一行指定棋盘的宽和高，为空格分隔的两个数字；

第二行依次间隔指定红蓝双方的落子步骤，第1步为红方的落子，第2步为蓝方的落子，第3步为红方的落子，以此类推。

步骤由空格分隔的一组数字表示，每个数字为落子的列的编号（最左边的列编号为1，往右递增）。用例保证数字均为32位有符号数。

输出描述

如果落子过程中红方获胜，输出 N,red ；

如果落子过程中蓝方获胜，输出 N,blue ；

如果出现非法的落子步骤，输出 N,error。

N为落子步骤的序号，从1开始。如果双方都没有获胜，输出 0,draw 。

非法落子步骤有两种，一是列的编号超过棋盘范围，二是在一个已经落满子的列上落子。

N和单词red、blue、draw、error之间是英文逗号连接。

示例1   输入输出示例仅供调试，后台判题数据一般不包含示例

输入

5 5
1 1 2 2 3 3 4 4

输出

7,red

说明

在第7步，红方在第4列落下一子后，红方的四个子在第一行连成一线，故红方获胜，输出 7,red。

示例2  输入输出示例仅供调试，后台判题数据一般不包含示例

输入

5 5
0 1 2 2 3 3 4 4

输出

1,error

说明

第1步的列序号为0，超出有效列编号的范围，故输出 1,error。

 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int W, H;
    cin >> W >> H;

    vector<vector<int>> board(H, vector<int>(W, 0));
    // 0: empty, 1: red, 2: blue

    vector<long long> steps;
    long long x;
    while (cin >> x) steps.push_back(x);

    auto place = [&](int col, int player) {
        // return row index, -1 if full
        for (int r = 0; r < H; r++) {
            if (board[r][col] == 0) {
                board[r][col] = player;
                return r;
            }
        }
        return -1;
    };

    auto countDir = [&](int r, int c, int player, int dr, int dc) {
        int cnt = 0;
        int nr = r + dr, nc = c + dc;
        while (nr >= 0 && nr < H && nc >= 0 && nc < W && board[nr][nc] == player) {
            cnt++;
            nr += dr;
            nc += dc;
        }
        return cnt;
    };

    auto checkWin = [&](int r, int c, int player) {
        int dirs[4][2] = {
            {1, 0},   // 横向
            {0, 1},   // 竖向
            {1, 1},   // 主对角
            {1, -1}   // 副对角
        };

        for (auto &d : dirs) {
            int dx = d[0], dy = d[1];
            int count = 1;
            count += countDir(r, c, player, dx, dy);
            count += countDir(r, c, player, -dx, -dy);
            if (count >= 4) return true;
        }
        return false;
    };

    for (int i = 0; i < (int)steps.size(); i++) {
        long long colInput = steps[i];
        int stepNum = i + 1;

        int player = (stepNum % 2 == 1 ? 1 : 2);  // red = 1, blue = 2

        // 列越界
        if (colInput < 1 || colInput > W) {
            cout << stepNum << ",error\n";
            return 0;
        }

        int col = (int)colInput - 1;

        // 落子
        int row = place(col, player);
        if (row == -1) {  // 该列满
            cout << stepNum << ",error\n";
            return 0;
        }

        // 判断胜利
        if (checkWin(row, col, player)) {
            if (player == 1)
                cout << stepNum << ",red\n";
            else
                cout << stepNum << ",blue\n";
            return 0;
        }
    }

    // 没有胜负
    cout << "0,draw\n";
    return 0;
}
