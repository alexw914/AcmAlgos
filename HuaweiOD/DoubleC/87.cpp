//
// Created by 巫妖王 on 2026/1/13.
//

/*
假设你是大型科技公司的数据分析师，负责分析公司内部员工的社交网络。你需要编写一个函数来计算每个员工的影响力分数。
影响力分数定义为该员工直接和间接影响的员工数量。
输入描述
n:员工总数。
employess:一个二维列表，表示员工的社交网络关系。例如employeestl是一个包含员工i直接影响的员工ID的列表。
备注
employees列表中，*表示没有直接影响到的员工;员工总数小于20;自身不算分数。
输出描述
influenceScores，一个整数数组，表示每个员工的影响力分数。

示例1：

输入：

4
1
2
3
*

输出：

3 2 1 0


示例2：

输入：

5
1 2
3
4
*
*


输出：

4 1 1 0 0

示例3：

输入：

6
1 2
3
4
5
0
*


输出：

5 2 5 1 5 0
*/

#include <iostream>
#include <numeric>
#include <queue>
#include <sstream>
#include <vector>
using namespace std;

int n;
vector<vector<int> > g;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    cin.ignore();
    g.resize(n);

    for (int i = 0; i < n; i++) {
        string line;
        getline(cin, line);
        if (line == "*") continue;
        stringstream ss(line);
        int x;
        while (ss >> x) { g[i].push_back(x); }
    }

    vector<int> scores;
    for (int i = 0; i < n; i++) {
        queue<int> q;
        q.push(i);
        vector<int> vis(n, false);
        vis[i] = true;
        while (!q.empty()) {
            auto u = q.front();
            q.pop();
            for (auto v: g[u]) {
                if (!vis[v]) {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
        scores.push_back(accumulate(vis.begin(), vis.end(), 0) - 1);
    }
    for (int i = 0; i < scores.size(); i++) {
        cout << scores[i];
        if (i != scores.size() - 1) cout << " ";
    }
    cout << endl;

    return 0;
}
