//
// Created by Krisw on 2026/1/19.
//

/*
贪吃蛇是一个经典游戏，蛇的身体由若干方格连接而成，身体随蛇头移动。蛇头触碰到食物时，蛇的长度会增加一格。

蛇头和身体的任一方格或者游戏版图边界碰撞时，游戏结束。

下面让我们来完成贪吃蛇游戏的模拟。

给定一个N*M的数组arr，代表N*M个方格组成的版图，贪吃蛇每次移动一个方格。

若arr[i][j] == ‘H’，表示该方格为贪吃蛇的起始位置；

若arr[i][j] == ‘F’，表示该方格为食物，

若arr[i][j] == ‘E’，表示该方格为空格。

贪吃蛇初始长度为1，初始移动方向为向左。

为给定一系列贪吃蛇的移动操作，返回操作后蛇的长度，如果在操作执行完之前已经游戏结束，返回游戏结束时蛇的长度。

贪吃蛇移动、吃食物和碰撞处理的细节见下面图示：

图1：截取了贪吃蛇移动的一个中间状态，H表示蛇头，F表示食物，数字为蛇身体各节的编号，蛇为向左移动，此时蛇头和食物已经相邻

图2：蛇头向左移动一格，蛇头和食物重叠，注意此时食物的格子成为了新的蛇头，第1节身体移动到蛇头位置，第2节身体移动到第1节身体位置，以此类推，

最后添加第4节身体到原来第3节身体的位置。

图3：蛇头继续向左移动一格，身体的各节按上述规则移动，此时蛇头已经和边界相邻，但还未碰撞。

图4：蛇头继续向左移动一格，此时蛇头已经超过边界，发生碰撞，游戏结束。

图5和图6给出一个蛇头和身体碰撞的例子，蛇为向上移动。

图5时蛇头和第7节身体相邻，但还未碰撞；

图6蛇头向上移动一格，此时蛇头和第8节身体都移动到了原来第7节身体的位置，发生碰撞，游戏结束。



输入描述

输入第一行为空格分隔的字母，代表贪吃蛇的移动操作。
字母取值为U、D、L、R和G，
U、D、L、R分别表示贪吃蛇往上、下、左、右和转向，转向时贪吃蛇不移动 ，G表示贪吃蛇按当前的方向移动一格。
用例保证输入的操作正确。
第二行为空格分隔的两个数，指定N和M，为数组的行和列数。
余下N行每行是空格分隔的M个字母。字母取值为H、F和E，H表示贪吃蛇的起始位置，F表示食物，E表示该方格为空。
用例保证有且只有一个H，而F和E会有多个。
输出描述

输出一个数字，为蛇的长度。
示例 1 输入输出示例仅供调试，后台判题数据一般不包含示例

输入

D G G

3 3

F F F

F F H

E F E

输出

1

地图表示为：

蛇头 H(Head)

食物 F(Food)

E表示该方格为空

四个方向分别表示为：

向上 U(up)

向下 D(down)

向左 L(Left)

向右 R(Right)
*/

#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <unordered_set>
using namespace std;

static inline long long id(int r, int c, int M) {
    return 1LL * r * M + c;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 读操作行（例如: "D G G"）
    string opsLine;
    if (!getline(cin, opsLine)) return 0;
    while (!opsLine.empty() && (opsLine.back() == '\r' || opsLine.back() == '\n')) opsLine.pop_back();
    stringstream ssOps(opsLine);
    vector<char> ops;
    string tok;
    while (ssOps >> tok) {
        ops.push_back(tok[0]); // U/D/L/R/G
    }

    int N, M;
    cin >> N >> M;

    vector<vector<char>> grid(N, vector<char>(M));
    vector<vector<char>> food(N, vector<char>(M, 0));
    int hr = -1, hc = -1;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            string s;
            cin >> s;              // "H" / "F" / "E"
            grid[i][j] = s[0];
            if (grid[i][j] == 'H') {
                hr = i; hc = j;
            } else if (grid[i][j] == 'F') {
                food[i][j] = 1;
            }
        }
    }

    // 初始：长度1，方向向左
    int dr = 0, dc = -1;

    deque<pair<int,int>> snake;
    snake.push_front({hr, hc});

    unordered_set<long long> occ;
    occ.reserve((size_t)N * M * 2);
    occ.insert(id(hr, hc, M));

    auto setDir = [&](char d) {
        if (d == 'U') { dr = -1; dc = 0; }
        else if (d == 'D') { dr = 1; dc = 0; }
        else if (d == 'L') { dr = 0; dc = -1; }
        else if (d == 'R') { dr = 0; dc = 1; }
    };

    bool gameOver = false;

    for (char op : ops) {
        if (op == 'U' || op == 'D' || op == 'L' || op == 'R') {
            setDir(op);            // 转向不移动
            continue;
        }

        // op == 'G'：移动一格
        int nr = snake.front().first + dr;
        int nc = snake.front().second + dc;

        // 1) 撞墙
        if (nr < 0 || nr >= N || nc < 0 || nc >= M) {
            gameOver = true;
            break;
        }

        bool grow = (food[nr][nc] == 1);
        long long nid = id(nr, nc, M);

        if (!grow) {
            // 本步不增长：尾巴会释放，所以先把尾巴从占用集合里移除再判碰撞
            auto tail = snake.back();
            long long tid = id(tail.first, tail.second, M);
            occ.erase(tid);

            if (occ.count(nid)) { // 撞身体（不含原尾巴，因为已释放）
                gameOver = true;
                break;
            }

            // 头进
            snake.push_front({nr, nc});
            occ.insert(nid);
            // 尾出（deque里也要弹出）
            snake.pop_back();
        } else {
            // 本步增长：尾巴不释放，直接判碰撞
            if (occ.count(nid)) {
                gameOver = true;
                break;
            }
            snake.push_front({nr, nc});
            occ.insert(nid);
            food[nr][nc] = 0; // 吃掉
        }
    }

    cout << snake.size() << "\n";
    return 0;
}
