//
// Created by Krisw on 2025/12/21.
//

/*
输入N个互不相同的二维整数坐标，求这N个坐标可以构成的正方形数量。[内积为零的的两个向量垂直]

输入描述

第一行输入为N，N代表坐标数量，N为正整数。N <= 100

之后的 K 行输入为坐标x y以空格分隔，x，y为整数，-10<=x, y<=10

输出描述

输出可以构成的正方形数量。

示例 1 输入输出示例仅供调试，后台判题数据一般不包含示例

输入

3

1 3

2 4

3 1

输出

0 （3个点不足以构成正方形）

示例 2 输入输出示例仅供调试，后台判题数据一般不包含示例

输入

4

0 0

1 2

3 1

2 -1

输出

1
*/

#include <iostream>
#include <vector>
#include <unordered_set>
#include <cstdint>

using namespace std;

// 把 (x,y) 编码成一个 64-bit key，便于 unordered_set 查找
static inline long long key(int x, int y) {
    return ( (long long)x << 32 ) ^ (unsigned int)y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    if (n < 4) {
        cout << 0 << "\n";
        return 0;
    }

    vector<pair<int,int>> coords;
    coords.reserve(n);

    unordered_set<long long> st;
    st.reserve(n * 2);

    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        coords.push_back({x, y});
        st.insert(key(x, y));
    }

    long long cnt = 0;

    // 枚举无序点对 (i, j) 作为一条边
    for (int i = 0; i < n; i++) {
        int xi = coords[i].first, yi = coords[i].second;
        for (int j = i + 1; j < n; j++) {
            int xj = coords[j].first, yj = coords[j].second;

            int dx = xj - xi;
            int dy = yj - yi;

            // 旋转 +90°: (dx,dy) -> (-dy, dx)
            // 另外两点：A = Pi + (-dy, dx), B = Pj + (-dy, dx)
            int ax1 = xi - dy, ay1 = yi + dx;
            int bx1 = xj - dy, by1 = yj + dx;
            if (st.count(key(ax1, ay1)) && st.count(key(bx1, by1))) {
                cnt++;
            }

            // 旋转 -90°: (dx,dy) -> (dy, -dx)
            int ax2 = xi + dy, ay2 = yi - dx;
            int bx2 = xj + dy, by2 = yj - dx;
            if (st.count(key(ax2, ay2)) && st.count(key(bx2, by2))) {
                cnt++;
            }
        }
    }

    // 每个正方形会被 4 条边各计数一次
    cout << (cnt / 4) << "\n";
    return 0;
}
