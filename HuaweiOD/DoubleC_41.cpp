//
// Created by Krisw on 2025/12/21.
//

/*
题目描述
现在有n个容器服务，服务的启动可能有一定的依赖性(有些服务启动没有依赖)，其次服务自身启动加载会消耗些时间。
给你一个nxn 的二维矩阵 useTime，其中 useTime[i][i]=10 表示服务i自身启动加载需要消耗10s，useTime[i][j]=1
表示服务i 启动依赖服务j 启动完成，useTime[i][k]=0，表示服务i 启动不依赖服务 k其实 0<= i,j，k< n。
服务之间启动没有循环依赖(不会出现环)，若想对任意一个服务i进行集成测试(服务追身也需要加载)，求最少需要等待多少时间。
输入描述
第一行输入服务总量 n.

之后的 n 行表示服务启动的依赖关系以及自身启动加载耗时

最后输入 k 表示计算需要等待多少时间后可以对服务 k 进行集成测试

其中 1 <= k <=n. 1<=n<=100
输出描述
最少需要等待多少时间(s)后可以对服务 k 进行集成测试

示例1

输入:

3

5 0 0

1 5 0

0 1 5

3
输出:
15
*/

#include <bits/stdc++.h>
using namespace std;

int N;
vector<vector<int>> useTime;
vector<int> memory;
vector<int> vis;

int dfs(int k) {
    if (vis[k]) return memory[k];
    vis[k] = 1;

    int bestDep = 0; // 多个依赖可并行，取最慢的那条链
    for (int j = 0; j < N; j++) {
        if (j != k && useTime[k][j] == 1) {
            bestDep = max(bestDep, dfs(j));
        }
    }

    memory[k] = useTime[k][k] + bestDep;
    return memory[k];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    useTime.assign(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) cin >> useTime[i][j];
    }

    int k;
    cin >> k; // 1 <= k <= n
    k -= 1;

    memory.assign(N, 0);
    vis.assign(N, 0);

    cout << dfs(k) << "\n";
    return 0;
}