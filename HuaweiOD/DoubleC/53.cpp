//
// Created by Krisw on 2025/12/28.
//

/*
游戏前可以挑选x颗宝石，将这些宝石的属性值相乘组成玩家的属性值。游戏玩家需要y点属性值，请帮助游戏玩家计算有多少种计算方式
输入描述
第一行:三个整数n,x,y
第一个整数n(0<n<20)表示宝石总数量。
第二个整数x(0<x<=n)，表示可以选择宝石个数
第三个整数y，表示通过游戏需要的属性值


第二行:n个整数，a1,a2....an(-100<ai<100)，表示每个宝石的属性值。


输出描述
输出一个整数，表示玩家可以通过游戏的挑选方式的数量

示例1

输入：

4 2 8
2 -3 4 5

输出：

3
*/


#include <bits/stdc++.h>
using namespace std;
using LL = long long;
int n, x;
LL y;
vector<int> w;

int cnt;
void backtracking(int k, LL curVaule, int startIdx) {
    if (k > x) return;
    if (k == x && curVaule >= y) {
        cnt++;
        return;
    }
    for (int i = startIdx; i < n; i++) {
        backtracking(k+1, curVaule*w[i], i+1); //注意这里传i+1
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> x >> y;
    w.resize(n);
    for (int i = 0; i < n; i++) { cin >> w[i]; }

    backtracking(0, 1, 0);
    cout << cnt << endl;
    return 0;
}



