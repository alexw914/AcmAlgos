//
// Created by 巫妖王 on 2026/5/22.
//

/*
小王在玩一款叫做直捣黄龙的小游戏，在该游戏中他需要从入口位置进入敌营，绕过哨兵的层层封锁，达到敌军司令部实施斩首行动。
敌军阵营是一个n*n的矩阵，入口在坐标(0,n/2)，敌军司令部在坐标(n-1,n/2)，每个哨兵警戒以自己为中心的9宫格，一旦被哨兵发现则行动失败。
同时穿越敌营耗时越长，被发现的概率越高，因此小王需要寻找到可以绕过警戒到达敌军司令部的最短路径。请你设计一个小程序，帮助小王统计这样的路径有多少条，以及路径长度。规则说明:
1.其中n为大于1的奇数且取值小于30，坐标x，y取值均从0开始，敌营左下角定义为(0,0),右上角定义为(n-1,n-1).
2.敌营入口在坐标(0,n/2)，敌军司令部在坐标(n-1，n/2)。
3.游戏角色的行动方向只包含上、下、左、右四个方向，即一次行动、y坐标不可同时变化。
4.在没有满足题目要求的可达路径时，需要返回(0，0)。
输入描述
参数1，敌军阵营的边长n。
参数2，哨兵位置列表Point(x，y），x表示行坐标，y表示列坐标。
输出描述
两个整数，第一个成员为最短路径条数，第二个成员为最短路径长度。
示例1

输入:

5
1
2 1

输出

1 6
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Point { int x, y; };

int n;
vector<vector<int>> maze;
vector<Point> guards;
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

int main() {

  cin >> n;
  int g;
  cin >> g; // 哨兵数量
  guards.resize(g);
  for(int i = 0; i < g; i++) { cin >> guards[i].x >> guards[i].y; }

  maze.resize(n, vector<int>(n, 0));

  // 标记哨兵的9宫格区域
  for(auto &p : guards) {
    for(int i = p.x - 1; i <= p.x + 1; i++) {
      for(int j = p.y - 1; j <= p.y + 1; j++) {
        if(i >= 0 && i < n && j >= 0 && j < n) maze[i][j] = 1;
      }
    }
  }

  // BFS 初始化
  vector<vector<int>> dist(n, vector<int>(n, -1));
  vector<vector<int>> cnt(n, vector<int>(n, 0));

  const int sx = 0, sy = n / 2;
  const int ex = n - 1, ey = n / 2;

  queue<pair<int,int>> q;
  dist[sx][sy] = 0;
  cnt[sx][sy] = 1;
  q.push({sx, sy});

  while(!q.empty()) {
    auto sz = q.size();
    for(int i = 0; i < sz; i++) {
      auto [x, y] = q.front(); q.pop();
      for(int d = 0; d < 4; d++) {
        auto nx = x + dx[d];
        auto ny = y + dy[d];
        if (nx >=0 && nx < n && ny >=0 && ny < n && maze[nx][ny] == 0) {
          if(dist[nx][ny] == -1) {
            // 第一次到达
            dist[nx][ny] = dist[x][y] + 1;
            cnt[nx][ny] = cnt[x][y];
            q.push({nx, ny});
          } else if(dist[nx][ny] == dist[x][y] + 1) {
            // 另一条最短路径到达
            cnt[nx][ny] += cnt[x][y];
          }
        }
      }
    }
  }

  if(dist[ex][ey] == -1) cout << "0 0" << endl;
  else cout << cnt[ex][ey] << " " << dist[ex][ey] << endl;

  return 0;
}