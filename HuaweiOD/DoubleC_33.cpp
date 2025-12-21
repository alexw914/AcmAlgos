//
// Created by Krisw on 2025/12/21.
//

/*
模拟AP安装，将AP的位置投影到二维坐标系中，给出每个AP的WIFI信号强度，信号强度会随着距离的增加而减弱。给定: 第一行是2个整数N,D(N<=100,D<=100)，
其中N表示AP数量，D表示AP能够的信号能够覆盖的最大距离。接下来的N行里，每行包含3个整数x,y,s，表示这个AP在坐标系的位置为(x,y)，x,y>0，信号强度为s。
所有坐标点是在X-Y坐标系内的整数坐标。
为了简化计算，两个坐标之间的距离用切比雪夫距离表示(在二维空间内，两个点之间的切比雪夫距离为它们横坐标之差的绝对值与纵坐标之差的绝对值的最大值)
需要你计算WIFI信号最好的坐标，
信号衰减计算方式: 如果第i个AP能到达(x,y)，那么该AP在此处的信号为 [s/(1+d)」(向下取整)，d表示这个AP跟此坐标的切比雪夫距离。
一个坐标的信号强度是所有能到达该坐标的AP的信号强度之和。
输入描述
第一行是2个整数N,D(N<=100,D<=100)，其中N表示AP数量，D表示AP能够的信号能够覆盖的最大距离 接下来N行，每行包含3个整数x,y,s，
表示这个AP在坐标系的位置为(x,y)，x,y>0，信号强度为s
输出描述
WIFI信号最好的坐标，如果存在多个信号一致的坐标，输出字典序最小的非负坐标 坐标(x1,y1)字典序比另一个坐标(x2,y2)小，需满足以下条件之一:
要么 x1<x2, 要么x1==x2 目y1<y2

示例1：

输入：

3 2
1 2 3
2 1 3
3 1 3

输出：

1 2

说明：

坐标[1,2]处的wifi信号最好
*/

#include <bits/stdc++.h>
using namespace std;

struct AP { int x, y, s; };

// (x,y) -> key
static inline long long packKey(int x, int y) {
    return ( (long long)x << 32 ) | (unsigned int)y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, D;
    cin >> N >> D;
    vector<AP> aps(N);
    for (int i = 0; i < N; i++) cin >> aps[i].x >> aps[i].y >> aps[i].s;

    // 累加每个点的总信号
    unordered_map<long long, long long> sum;
    sum.reserve((size_t)N * (2 * D + 1) * (2 * D + 1));

    long long bestSignal = -1;
    int bestX = 0, bestY = 0;

    for (const auto& ap : aps) {
        int x0 = ap.x, y0 = ap.y, s = ap.s;

        int xl = max(0, x0 - D), xr = x0 + D;
        int yl = max(0, y0 - D), yr = y0 + D;

        for (int x = xl; x <= xr; x++) {
            int dx = abs(x - x0);
            for (int y = yl; y <= yr; y++) {
                int dy = abs(y - y0);
                int dist = max(dx, dy);

                // dist 一定 <= D（因为就在正方形里），但写上也无妨
                if (dist > D) continue;

                long long add = s / (1 + dist); // 向下取整
                long long key = packKey(x, y);
                long long cur = (sum[key] += add);

                // 更新最优：信号更大优先；相同则字典序更小优先
                if (cur > bestSignal ||
                    (cur == bestSignal && (x < bestX || (x == bestX && y < bestY)))) {
                    bestSignal = cur;
                    bestX = x;
                    bestY = y;
                    }
            }
        }
    }

    // 注意：如果所有点信号都是 0，那么字典序最小非负坐标应为 (0,0)
    // 上面的遍历只会扫到被覆盖的点，可能没有 (0,0)。
    // 所以这里补一下：若 bestSignal <= 0，则答案就是 (0,0)。
    if (bestSignal <= 0) cout << "0 0\n";
    else cout << bestX << " " << bestY << "\n";

    return 0;
}
