//
// Created by Krisw on 2025/12/21.
//

/*
给定一个含有N个正整数的数组, 求出有多少个连续区间（包括单个正整数）, 它们的和大于等于x。

输入描述

第一行两个整数N x（0 < N <= 100000, 0 <= x <= 10000000)

第二行有N个正整数（每个正整数小于等于100)。

输出描述

输出一个整数，表示所求的个数。

注意：此题对效率有要求，暴力解法通过率不高，请考虑高效的实现方式。

示例1 输入输出示例仅供调试，后台判题数据一般不包含示例

输入

3 7

3 4 7

输出

4

样例解释

第一行的3表示第二行数组输入3个数，第一行的7是比较数，用于判断连续数组是否大于该数；

组合为 3 + 4; 3 + 4 + 7; 4 + 7; 7; 都大于等于指定的7；所以共四组。

示例2 输入输出示例仅供调试，后台判题数据一般不包含示例

10 10000

1 2 3 4 5 6 7 8 9 10

样例解释

所有元素的和小于10000，所以返回0。
*/

#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N, x;
    cin >> N >> x;
    vector<int> a(N+1, 0);
    for (int i = 1; i <= N; i++ ) {
        cin >> a[i];
    }

    vector<int> prefix(N+1, 0);
    for (int i = 1; i <= N; i++) {
        prefix[i] = prefix[i-1] + a[i];
    }

    // x == 0：所有非空连续区间都满足
    if (x == 0) {
        long long total = 1LL * N * (N + 1) / 2;
        cout << total << "\n";
        return 0;
    }

    long long ans = 0;
    int r = 1; // r 从 1..N
    for (int l = 0; l <= N - 1; l++) {
        if (r < l + 1) r = l + 1;
        while (r <= N && prefix[r] - prefix[l] < x) r++;
        if (r <= N) ans += (N - r + 1); // r..N 都满足
    }

    cout << ans << endl;

    return 0;
}