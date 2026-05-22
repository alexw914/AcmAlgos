//
// Created by 巫妖王 on 2026/5/21.
//

/*
请你在给定的数字地形图中寻找登山路径，数字代表当前位置的海拔高度，要求从最低海拔出发，不断攀登，最终到达最高山峰。你需要寻找所有满足条件的登山路径。地图已经保证最低海拔和最高山峰都只有一个。
路径条件
登山规则:路径上的海拔必须严格递增
移动限制:可以向上下左右4个方向移动
路径限制:路径必须从最低海拔开始，到最高海拔结束
访问控制:每个地点只能走一次
高度差限制:每一步的攀登高度差必须大于0，小于等于指定值
输入格式
输入一个二维数组表示的海拔图，维度为nXm(2≤n,m≤10)，每个元素都是一个整数2输入一个整数参数表示单步最大允许的高度差
输出格式
输出满足条件的登山路径的数量
示例1
输入：

4 4 5
7 6 4 5
9 5 1 1
2 4 1 4
1 3 2 0

输出：

2
*/

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class Solution {
private:
  vector<vector<int>> visited;
  long long cnt = 0;
  int M, N, diff;
  int sx, sy, ex, ey;
  int maxHeight, minHeight;
  int dx[4] = {-1, 0, 1, 0};
  int dy[4] = {0, 1, 0, -1};
  void dfs(vector<vector<int>> &grid, vector<vector<int>> &visited, int x, int y) {
    if (x == ex && y == ey) {
      cnt++;
      return;
    }
    for (int i = 0; i < 4; i++) {
      auto nx = x + dx[i];
      auto ny = y + dy[i];
      if (nx >= 0 && nx < M && ny >= 0 && ny < N && visited[nx][ny] == 0 &&
          grid[x][y] < grid[nx][ny] && grid[nx][ny] - grid[x][y] <= diff) {
        visited[nx][ny] = 1;
        dfs(grid, visited, nx, ny);
        visited[nx][ny] = 0;
      }
    }
  }

public:
  long long countHikingPaths(vector<vector<int>> &grid, int maxDiff) {
    M = grid.size(), N = grid[0].size(), diff = maxDiff;
    visited.resize(M, vector<int>(N, 0));
    maxHeight = INT_MIN, minHeight = INT_MAX;
    for (int i = 0; i < M; i++) {
      for (int j = 0; j < N; j++) {
        if (grid[i][j] < minHeight) {
          minHeight = grid[i][j];
          sx = i, sy = j;
        }
        if (grid[i][j] > maxHeight) {
          maxHeight = grid[i][j];
          ex = i, ey = j;
        }
      }
    }
    visited[sx][sy] = 1;
    dfs(grid, visited, sx, sy);
    return cnt;
  }
};

int main() {

  vector<vector<int>> grid = {{7,6,4,5},{9,5,1,1},{2,4,1,4},{1,3,2,0}};
  auto solution = Solution();
  cout << solution.countHikingPaths(grid, 5) << endl;
  return 0;
}
