//
// Created by Krisw on 2026/1/13.
//

/*
部门准备举办一场王者荣耀表演赛，有 10 名游戏爱好者参与，分为两队，每队 5 人。每位参与者都有一个评分，代表着他的游戏水平。
为了表演赛尽可能精彩，我们需要把 10 名参赛者分为示例尽量相近的两队。
队的实力可以表示为这一队 5 名队员的评分总和。
现在给你 10 名参与者的游戏水平评分，请你根据上述要求分队，最后输出这两组的实力差绝对值.
例: 10名参赛者的评分分别为: 5 1 8 3 4 6 7 10 9 2，分为(1 3 5 8 10)和(2 4 6 7 9)，两组实力差最小，差值为1。有多种分法，但是实力差的绝对值最小为1。


输入描述:

10个队员的战斗力(整数，范围[1,10000]),战斗力之间用空格分隔，如:10987654321

不需要考虑异常输入的场景。

输出描述:

最小的战斗力差值，如:1

示例1  输入输出示例仅供调试，后台判题数据一般不包含示例

输入

10 9 8 7 6 5 4 3 2 1

输出

1

说明：
1 2 5 9 10分为一队，3 4 6 7 8分为一队，两队战斗力之差最小，输出差值1。
备注：球员分队方案不唯一，但最小战斗力差值固定是1。
*/

// #include <iostream>
// #include <numeric>
// #include <vector>
// using namespace std;
//
// vector<int> v(10, 0);
// vector<vector<int>> result;
// vector<int> path;
//
// void backtracking(int startIdx) {
//     if (path.size() == 5) {
//         result.push_back(path);
//         return;
//     }
//
//     for (int i = startIdx; i < 10; i++) {
//         path.push_back(v[i]);
//         backtracking(i+1);
//         path.pop_back();
//     }
// }
//
// int main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(nullptr);
//
//     int sum = 0;
//     for (int i = 0; i < 10; i ++) {
//         cin >> v[i];
//         sum += v[i];
//     }
//
//     backtracking(0);
//     int diff_min = 0x3f3f3f;
//     for (auto res: result) {
//         int select_sum = accumulate(res.begin(), res.end(), 0);
//         int remain_sum = sum - select_sum;
//         diff_min = min(diff_min, abs(select_sum - remain_sum));
//     }
//
//     cout << diff_min << endl;
//     return 0;
// }


#include <iostream>
#include <numeric>
#include <vector>
#include <climits>
using namespace std;

vector<int> v(10);
int totalSum = 0;
int best = INT_MAX;

void dfs(int idx, int cnt, int curSum) {
    if (cnt == 5) {
        int other = totalSum - curSum;
        best = min(best, abs(curSum - other));
        return;
    }
    if (idx == 10) return;

    dfs(idx + 1, cnt + 1, curSum + v[idx]);     // 选
    dfs(idx + 1, cnt, curSum);     // 不选
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 0; i < 10; i++) {
        cin >> v[i];
        totalSum += v[i];
    }

    dfs(0, 0, 0);

    cout << best << "\n";
    return 0;
}
