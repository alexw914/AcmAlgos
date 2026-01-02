//
// Created by Krisw on 2025/12/11.
//
/*
一个有N个选手参加比赛，选手编号为1~N（3<=N<=100），有M（3<=M<=10）个评委对选手进行打分。
打分规则为每个评委对选手打分，最高分10分，最低分1分。
请计算得分最多的3位选手的编号。
如果得分相同，则得分高分值最多的选手排名靠前
(10分数量相同，则比较9分的数量，以此类推，用例中不会出现多个选手得分完全相同的情况)。
输入描述:

第一行为半角逗号分割的两个正整数，第一个数字表示M（3<=M<=10）个评委，第二个数字表示N（3<=N<=100）个选手。
第2到M+1行是半角逗号分割的整数序列，表示评委为每个选手的打分，0号下标数字表示1号选手分数，1号下标数字表示2号选手分数，依次类推。
输出描述:

选手前3名的编号。
注：若输入为异常，输出-1，如M、N、打分不在范围内。
示例1   输入输出示例仅供调试，后台判题数据一般不包含示例

输入

4,5
10,6,9,7,6
9,10,6,7,5
8,10,6,5,10
9,10,8,4,9

输出

2,1,5

说明

第一行代表有4个评委，5个选手参加比赛

矩阵代表是4*5，每个数字是选手的编号，每一行代表一个评委对选手的打分排序，

2号选手得分36分排第1，1号选手36分排第2，5号选手30分(2号10分值有3个，1号10分值只有1个，所以2号排第一)

示例2   输入输出示例仅供调试，后台判题数据一般不包含示例

输入

2,5
7,3,5,4,2
8,5,4,4,3

输出

-1

说明

只有2个评委，要求最少为3个评委
示例3   输入输出示例仅供调试，后台判题数据一般不包含示例

输入

4,2
8,5
5,6
10,4
8,9

输出

-1

说明

只有2名选手参加，要求最少为3名

示例4   输入输出示例仅供调试，后台判题数据一般不包含示例

输入

4,5
11,6,9,7,8
9,10,6,7,8
8,10,6,9,7
9,10,8,6,7

输出

-1

说明

第一个评委给第一个选手打分11，无效分数
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    int M, N;
    scanf("%d,%d", &M, &N);
    struct Info {
        vector<int> scores;
        int all_score;
        int idx;
    };

    if (M < 3 || M > 10 || N < 3 || N > 10) {
        std::cout << -1 << std::endl;
    }
    std::vector<Info> infos(N);
    for (int i = 0; i < N; i++) {
        infos[i].idx = i + 1;
        infos[i].scores.reserve(M);
    }

    string line;
    int judgeRead = 0;
    while (judgeRead < M) {
        if (!getline(cin, line)) {
            cout << -1 << '\n';
            return 0;
        }

        // 跳过空行（题目示例里就有）
        // 如果你担心有空格，也可以先 trim 一下，这里简单点：
        if (line.empty())
            continue;

        stringstream row(line);
        string item;
        int cnt = 0;

        while (getline(row, item, ',')) {
            if (item.empty()) {  // 出现空字段
                cout << -1 << '\n';
                return 0;
            }

            int score;
            try {
                score = stoi(item);
            } catch (...) {
                cout << -1 << '\n';
                return 0;
            }

            // 分数必须是 1~10
            if (score < 1 || score > 10) {
                cout << -1 << '\n';
                return 0;
            }

            if (cnt >= N) {  // 这一行分数太多
                cout << -1 << '\n';
                return 0;
            }

            infos[cnt].all_score += score;
            infos[cnt].scores.push_back(score);
            ++cnt;
        }

        // 这一行分数太少
        if (cnt != N) {
            cout << -1 << '\n';
            return 0;
        }

        ++judgeRead;
    }

    std::sort(infos.begin(), infos.end(), [](Info &a, Info &b) {
        if (a.all_score != b.all_score) { return a.all_score > b.all_score; } else {
            for (auto i = 10; i > 0; i--) {
                int cnt_a = std::count(a.scores.begin(), a.scores.end(), i);
                int cnt_b = std::count(b.scores.begin(), b.scores.end(), i);
                if (cnt_a != cnt_b) { return cnt_a > cnt_b; }
            }
        }
        return a.idx < b.idx;
    });

    cout << infos[0].idx << "," << infos[1].idx << "," << infos[2].idx << endl;

    return 0;
}
