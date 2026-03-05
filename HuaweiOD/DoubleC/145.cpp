//
// Created by Krisw on 2026/3/5.
//

/*
题目描述：
有一个N个整数的数组，和一个长度为M的窗口，窗口从数组内的第一个数开始滑动直到窗口不能滑动为止， 每次窗口滑动产生一个窗口和（窗口内所有数的和），求窗口滑动产生的所有窗口和的最大值。

输入描述：
第一行输入一个正整数N，表示整数个数。（0<N<100000）
第二行输入N个整数，整数的取值范围为[-100,100]。
第三行输入一个正整数M，M代表窗口的大小，M<=100000，且M<=N。
输出描述：
窗口滑动产生所有窗口和的最大值。
示例 1 输入输出示例仅供调试，后台判题数据一般不包含示例

输入
6
12 10 20 30 15 23
3
输出
68
 */
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N;

    vector<int> array(N);
    for (int i = 0; i < N; i++) cin >> array[i];

    cin >> M;

    vector<int> prefix(N + 1, 0);

    for (int i = 1; i <= N; i++)
        prefix[i] = prefix[i - 1] + array[i - 1];

    int ans = 0;

    for (int i = M; i <= N; i++)
        ans = max(ans, prefix[i] - prefix[i - M]);

    cout << ans << endl;
}
