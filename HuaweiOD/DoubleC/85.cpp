//
// Created by Krisw on 2026/1/12.
//

/*
有一个局部互联区域内的n台设备，每台设备都有一定数量的空闲资源，这些资源可以池化共享。用户会发起两种操作
1.申请资源:输入 1 x，表示本次申请需要x个资源。系统要返回当前资源池中能满足此申请且剩余资源最少的设备ID;
如果有多台设备满足条件，返回设备 ID 最小的;如果没有任何设备能满足，返回 0 并不做任何分配。

2.释放资源:输入 2 y，表示将第y次申请(不一定是成功分配的那一次)释放回原设备。释放时，资源立即归还,
且空闲资源自动连续，无需考虑空洞，
给定n(1≤n≤ 1000)、操作次数 m(1≤m≤10^5)，以及初始时每台设备的空闲资源数 d[1]...d[n](1≤d≤1000)，以及接下来 m 行操作，输出每次“申请”操作的返回值。
输入描述
第一行，输入n和 m
第二行输入n台设备的初始空闲资源数
接下来m行，输出要执行的操作，
输出描述
输出每次“申请”操作的返回值。

示例1：

输入：

2 2
100 500
1 40
1 450


输出：

1 2

*/

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Info {
    int resource = 0;
    int res = 0;
};

int apply(vector<int> &v, int x) {
    vector<int> idxs;
    int min_rs = 0x3f3f3f;
    for (int i = 1; i < v.size(); i++) {
        auto vi = v[i];
        if (vi >= x) {
            if (vi < min_rs) {
                idxs.clear();
                idxs.push_back(i);
                min_rs = vi;
            } else if (vi == min_rs) {
                idxs.push_back(i);
            }
        }
    }
    if (idxs.empty()) return 0;
    sort(idxs.begin(), idxs.end(), [](int a, int b) {return a < b;});
    v[idxs[0]] -= x;
    return idxs[0];
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> v(n + 1, 0);
    for (int i = 1; i <= n; i++) { cin >> v[i]; }

    vector<Info> ops(m + 1);
    for (int i = 1; i < m + 1; i++) {
        int op;
        cin >> op;
        if (op == 1) {
            int x;
            cin >> x;
            int res = apply(v, x);
            cout << res << " ";
            ops[i] = {x, res};
        } else if (op == 2) {
            int y;
            cin >> y;
            if (ops[y].res != 0) {
                v[ops[y].res] += ops[y].resource;
            }
        }
    }

    return 0;
}
