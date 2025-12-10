//
// Created by Krisw on 2025/12/3.
//

/*
公元2919年，人类终于发现了一颗宜居星球——X星。
现想在X星一片连绵起伏的山脉间建一个天热蓄水库，如何选取水库边界，使蓄水量最大？

要求：
    山脉用正整数数组s表示，每个元素代表山脉的高度。
    选取山脉上两个点作为蓄水库的边界，则边界内的区域可以蓄水，蓄水量需排除山脉占用的空间
    蓄水量的高度为两边界的最小值。
    如果出现多个满足条件的边界，应选取距离最近的一组边界。
输出边界下标（从0开始）和最大蓄水量；如果无法蓄水，则返回0，此时不返回边界。
例如，当山脉为s=[3,1,2]时，则选取s[0]和s[2]作为水库边界，则蓄水量为1，此时输出：0 2:1
当山脉s=[3,2,1]时，不存在合理的边界，此时输出：0。

给定一个长度为 n 的整数数组 height 。数组的元素表示山的高度，选择两个元素作为水库的边界，
求蓄水量的最大值并输出蓄水量最大时的边界下标（蓄水量相同时输出下标较近的）。

输入描述：

输入一行数字，空格分隔。

输出描述：

输出蓄水量的最大值及输出蓄水量最大时的边界下标

示例1：

输入：

1 8 6 2 5 4 8 3 7

输出：

1 6:15

说明：蓄水量的最大值为 15

蓄水量最大时的边界下标为1 和 6
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> height;
    string line;
    if (std::getline(cin, line)) {
        std::istringstream iss(line);
        int x;
        while (iss >> x) {
            height.push_back(x);
        }
    }

    const int N = height.size();
    if (N < 3) {
        cout << 0 << endl;
        return 0;
    }

    vector<int> leftMax(N, 0);
    vector<int> rightMax(N, 0);

    leftMax[0] = height[0];
    for (int i = 1; i < N; i++) {
        leftMax[i] = max(leftMax[i-1], height[i]);
    }
    rightMax[N-1] = height[N-1];
    for (int i = N-2; i >= 0; i--) {
        rightMax[i] = max(rightMax[i+1], height[i]);
    }

    // // water[i]：标准接雨水里的“水深”（可能为负，这里先算出来）
    // vector<int> water(N, 0);
    // for (int i = 0; i < N; i++) {
    //     water[i] = min(leftMax[i], rightMax[i]) - height[i];
    // }

    // waterLevel[i]：该位置“水面高度”，真正的水位高度（山 + 水）
    vector<int> waterLevel(N, 0);
    for (int i = 0; i < N; i++) {
        waterLevel[i] = min(leftMax[i], rightMax[i]);
    }

    int bestCapacity = 0;
    int bestL = -1, bestR = -1;

    for (int i = 0; i < N; ++i) {
        for (int j = i + 2; j < N; ++j) {

            int H = min(height[i], height[j]); // 这个水库的水位上限（边界高度）

            int curCapacity = 0;
            // 枚举区间内部，利用 waterLevel（水面高度）
            for (int k = i + 1; k <= j - 1; ++k) {
                int level = min(waterLevel[k], H);  // 这个位置真正能达到的水面高度
                if (level > height[k]) {
                    curCapacity += (level - height[k]); // 水深 = 水面高度 - 山高度
                }
            }

            if (curCapacity > bestCapacity) {
                bestCapacity = curCapacity;
                bestL = i, bestR = j;
            } else if (curCapacity == bestCapacity && curCapacity > 0) {                 // 蓄水量相同，选距离最近的
                if ((j - i) < (bestR - bestL)) {
                    bestL = i, bestR = j;
                }
            }
        }
    }

    if (bestCapacity <= 0) {
        cout << 0 << endl;
    } else {
        cout << bestL << " " << bestR << ":" << bestCapacity << endl;
    }

    return 0;
}
