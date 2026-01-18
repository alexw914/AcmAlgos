//
// Created by Krisw on 2026/1/15.
//

/*
在做物理实验时，为了计算物体移动的速率，通过相机等工具周期性的采样物体移动能离。由于工具故障，采样数据存在误差甚至相误的情况。
需要通过一个算法过滤掉不正确的采样值，不同工具的故意模式存在差异，算法的各关门限会根据工具类型做相应的调整，请实现一个算法，计算出给定一组采样值中正常值的最长连续周期。


判断第1个周期的采样数据s0是否正确的规则如下(假定物体移动速率不超过10个单元前一个采样周期S[i-1]):

S[i]<=0，即为错误值
S[i]<S[i-1]，即为错误值
S[i]-S[i-1]>=10，即为错误值·其它情况为正常值
判断工具是否故障的规则如下:

在M个周期内，采样数据为错误值的次数为T(次数可以不连续)，则工具故障
判断故障恢复的条件如下:

产生故障后的P个周期内，采样数据一直为正常值，则故障恢复
错误采样数据的处理方式

检测到故障后，丢弃从故障开始到故障恢复的采样数据
在检测到工具故障之前，错误的采样数据，则由最近一个正常值代替;如果前面没有正常的采样值，则丢弃此采样数据
给定一段周期的采样数据列表S，计算正常值的最长连续周期。


输入描述:
故障确认周期数和故障次数门限分别为M和T，故障恢复周期数为P。第i个周期，检测点的状态为S[i]

输入为两行，格式如下:

M T F
s1 s2 s3 ...
M、t 和 e的取值范围为[1100000]
s1取值范围为[0，100000]，从0开始编号
输出描述
一行，输出正常值的最长连续周期

示例：

输入：

10 6 3

-1 1 2 3 100 10 13 9 10

输出：

8
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, T, P;
    cin >> M >> T >> P;

    vector<int> S;
    int x;
    while (cin >> x) S.push_back(x);

    deque<int> errWin;
    int errCnt = 0;

    bool inFault = false;
    int recoverCnt = 0;

    bool hasLast = false;
    int lastValid = 0;

    int curLen = 0, maxLen = 0;

    for (int i = 0; i < (int)S.size(); ++i) {
        bool isErr = false;

        if (i == 0) {
            if (S[i] <= 0) isErr = true;
        } else {
            if (S[i] <= 0 || S[i] < S[i-1] || S[i] - S[i-1] >= 10)
                isErr = true;
        }

        // 更新错误窗口
        errWin.push_back(isErr);
        if (isErr) errCnt++;
        if ((int)errWin.size() > M) {
            if (errWin.front()) errCnt--;
            errWin.pop_front();
        }

        // 故障检测
        if (!inFault && errCnt >= T) {
            inFault = true;
            recoverCnt = 0;
        }

        // 故障状态处理
        if (inFault) {
            if (!isErr)
                recoverCnt++;
            else
                recoverCnt = 0;

            if (recoverCnt >= P) {
                inFault = false;
                recoverCnt = 0;
            }

            curLen = 0;
            continue;
        }

        // 非故障期
        int val;
        bool valid = true;

        if (isErr) {
            if (hasLast) {
                val = lastValid;
            } else {
                valid = false;
            }
        } else {
            val = S[i];
            lastValid = val;
            hasLast = true;
        }

        if (valid) {
            curLen++;
            maxLen = max(maxLen, curLen);
        } else {
            curLen = 0;
        }
    }

    cout << maxLen << "\n";
    return 0;
}
