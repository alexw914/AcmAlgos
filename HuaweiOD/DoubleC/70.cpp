//
// Created by Krisw on 2025/12/26.
//

/*
一只贪吃的猴子，来到一个果园，发现许多串香蕉排成一行，每串香蕉上有若干根香蕉。每串香蕉的根数由数组numbers给出。猴子获取香蕉，每次都只能从行的开头或者未尾获取，并且只能获取N次，求猴子最多能获取多少根香蕉。
输入描述
第一行为数组numbers的长度
第二行为数组numbers的值每个数字通过空格分开
第三行输入为N，表示获取的次数
输出描述
按照题目要求能获取的最大数值


示例1
输入
7
1 2 2 7 3 6 1

3
输出
10

示例2

输入
3
1 2 3
3

输出
6

说明
全部获取所有的香蕉，因此最终根数为1+2+3 = 6

示例3：

输入
4
4 2 2 3
2

输出
7

说明
第一次获取香蕉为行的开头，第二次获取为行的末尾，因此最终根数为4+3 =7
*/

#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

int ans = -1;
int N;

// void dfs(const vector<int>& array, int i, int j, int k, int sum) {
//     if ( k == N) {
//         ans = max(sum, ans);
//         return;
//     }
//
//     dfs(array, i, j-1, k+1, sum+array[j]);
//     dfs(array, i+1, j, k+1,  sum+array[i]);
// }

int main() {
    int M;
    cin >> M;
    vector<int> array(M, 0);
    int arraySum = 0;
    for (int i = 0; i < M; i++) {
        cin >> array[i];
        arraySum += array[i];
    }
    cin >> N;
    if (N >= M) {
        ans = arraySum;
    }
    else {
        int s = accumulate(array.end() - N, array.end(), 0);
        for (int i = 0; i < N; i++) {
            s += array[i];
            s -= array[M - N + i];
            ans = max(ans, s);
        }
    }
    cout << ans << endl;
    return 0;
}
